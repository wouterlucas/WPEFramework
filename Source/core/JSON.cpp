#include "JSON.h"

namespace WPEFramework {
namespace Core {
    namespace JSON {

        bool ContainsNull(const string& value)
        {

            static TCHAR constexpr NullKeyword[] = _T("null");

            if (value.length() == (sizeof(NullKeyword) - 1)) {

                uint8_t index = 0;
                while ((::tolower(value[index]) == NullKeyword[index]) && (index < (sizeof(NullKeyword) - 1))) {
                    index++;
                }

                return (index == (sizeof(NullKeyword) - 1));
            }
            return (false);
        }

        uint16_t IElement::Serializer::Serialize(uint8_t stream[], const uint16_t maxLength)
        {
            uint16_t result = 0;

            _adminLock.Lock();

            if (_state == STATE_REPORT) {
                // We only want to "report" a serialized if it is really gone, if
                // we are requested to pass out some new info, but did not yet do it...
                IElement* handledElement = _root;
                _root = nullptr;

                ASSERT(handledElement != nullptr);

                // The fact that we closed one, might lead to the opening of a new one.
                _state = STATE_PREFIX;

                // Time to report a finished streaming,
                // Clear the root first, so the callback can set a new one.
                Serialized(*handledElement);
            }

            if (_root != nullptr) {
                IIterator* current;

                if (_handleStack.empty() == false) {
                    current = _handleStack.front();
                } else {
                    current = nullptr;
                }

                // Is there still space to write ?
                while ((result < maxLength) && (_state != STATE_REPORT)) {
                    switch (_state) {
                    case STATE_PREFIX: {
                        if (_offset == 0) {
                            stream[result++] = '\"';
                            _offset++;
                        }
                        while ((result < maxLength) && (_prefix[_offset - 1] != '\0')) {
                            stream[result++] = _prefix[_offset - 1];
                            _offset++;
                        }
                        if (result < maxLength) {
                            if (_prefix[0] != '\0') {
                                stream[result++] = '\"';
                                stream[result++] = ':';
                            }
                            _state = STATE_OPEN;
                            _offset = 0;
                        }
                        break;
                    }
                    case STATE_OPEN: {
                        bool container = (dynamic_cast<ILabelIterator*>(current) != nullptr);

                        stream[result++] = (container ? '{' : '[');

                        bool serialize;

                        // Move on to the first item..
                        while (((serialize = current->Next()) == true) && (current->Element()->IsSet() == false)) {
                            // Intentionally left empty !!!
                        }

                        if (serialize == false) {
                            _state = STATE_CLOSE;
                        } else if (container == true) {
                            _state = STATE_LABEL;
                        } else if (current->Element()->Type() != PARSE_CONTAINER) {
                            _state = STATE_VALUE;
                        } else {
                            // Oops it is a container, dump container
                            current = current->Element()->ElementIterator();
                            _handleStack.push_front(current);
                        }

                        _offset = 0;
                        break;
                    }
                    case STATE_LABEL: {

                        if (_offset == 0) {
                            stream[result++] = '\"';
                            _offset++;
                        }

                        const char* label = static_cast<ILabelIterator*>(current)->Label();

                        while ((result < maxLength) && (label[_offset - 1] != '\0')) {
                            stream[result++] = label[_offset - 1];
                            _offset++;
                        }

                        if ((result < maxLength) && (label[_offset - 1] == '\0')) {
                            stream[result++] = '\"';
                            _state = STATE_DELIMITER;
                            _offset = 0;
                        }
                        break;
                    }
                    case STATE_DELIMITER: {
                        stream[result++] = ':';
                        _state = STATE_VALUE;
                        break;
                    }
                    case STATE_VALUE: {
                        if (current->Element()->Type() == PARSE_BUFFERED) {
                            if (_offset == 0) {
                                current->Element()->BufferParser()->Serialize(_buffer);
                            }

                            uint16_t write = ((maxLength - result) > (static_cast<uint16_t>(_buffer.length()) - _offset) ? (static_cast<uint16_t>(_buffer.length()) - _offset) : (maxLength - result));

                            ::memcpy(&stream[result], &(_buffer.data()[_offset]), (write * sizeof(char)));

                            _offset += write;
                            result += write;
                            if (_offset == _buffer.length()) {
                                _offset = 0;
                                _state = STATE_CLOSE;
                            }
                        } else if (current->Element()->Type() == PARSE_DIRECT) {
                            result += current->Element()->DirectParser()->Serialize(reinterpret_cast<char*>(&stream[result]), (maxLength - result), _offset);

                            // If the offset == 0, it means we are done with this one..
                            _state = (_offset == 0 ? STATE_CLOSE : STATE_VALUE);
                        } else {
                            // Oops it is another container.. reiterate..
                            _handleStack.push_front(current->Element()->ElementIterator());
                            current = current->Element()->ElementIterator();
                            _state = STATE_OPEN;
                        }
                        break;
                    }
                    case STATE_CLOSE: {
                        bool serialize;
                        bool container = (dynamic_cast<ILabelIterator*>(current) != nullptr);

                        _offset = 0;

                        // Move on to the first item..
                        while (((serialize = current->Next()) == true) && (current->Element()->IsSet() == false)) {
                            // Intentionally left empty !!!
                        }

                        if (serialize == true) {
                            // Seems we have another element to serialize
                            stream[result++] = ',';
                            _state = (container == true ? STATE_LABEL : STATE_VALUE);
                        } else {
                            stream[result++] = (container == true ? '}' : ']');

                            _handleStack.pop_front();
                            if (_handleStack.empty() == false) {
                                current = _handleStack.front();
                            } else {
                                _state = STATE_REPORT;
                            }
                        }
                        break;
                    }
                    case STATE_REPORT: {
                        // we shoulc never end up here.
                        ASSERT(FALSE);
                        break;
                    }
                    default: {
                        ASSERT(FALSE);
                        break;
                    }
                    }
                }
            }

            _adminLock.Unlock();

            return (result);
        }

        uint16_t IElement::Deserializer::Deserialize(const uint8_t stream[], const uint16_t maxLength)
        {
            uint16_t result = 0;

            _adminLock.Lock();
            IIterator* current = nullptr;

            if (_state == STATE_HANDLED) {
                _state = STATE_PREFIX;
            }

            if (_handleStack.size() > 0) {
                current = _handleStack.front();
            }

            // Is there still space to write ?
            while ((result < maxLength) && (_state != STATE_HANDLED)) {
                switch (_state) {
                case STATE_PREFIX: {
                    if (_buffer.length() == 0) {
                        // Skip all whitespace
                        while ((result < maxLength) && (isspace(stream[result]))) {
                            result++;
                        }
                    }

                    if (result < maxLength) {
                        while ((result < maxLength) && (_state == STATE_PREFIX)) {
                            if ((stream[result] == '{') || (stream[result] == '[')) {
                                _handlingName = Core::ToString(_buffer.c_str());
                                // Seems like we ended up on an element.
                                _handling = Element(_handlingName);

                                _buffer.clear();
                                _offset = 0;

                                if (_handling == nullptr) {
                                    _state = STATE_SKIP;
                                } else {
                                    current = _handling->ElementIterator();
                                    _handleStack.push_front(current);
                                    _state = STATE_OPEN;
                                }
                            } else if ((isspace(stream[result])) || (stream[result] == ':')) {
                                ASSERT(_buffer.length() != 0);

                                result++;

                                _handlingName = Core::ToString(_buffer.c_str());
                                _handling = Element(_handlingName);
                                _buffer.clear();
                                _offset = 0;

                                // Seems like we completed a word, See if it is an identifier we are looking for
                                if (_handling == nullptr) {
                                    _state = STATE_SKIP;
                                } else {
                                    // We found an entry, lock and load..
                                    current = _handling->ElementIterator();
                                    _handleStack.push_front(current);
                                    _state = STATE_OPEN;
                                }
                            } else {
                                _buffer += stream[result++];
                            }
                        }
                    }
                    break;
                }
                case STATE_OPEN: {
                    IArrayIterator* elementList = dynamic_cast<IArrayIterator*>(current);

                    int character = (elementList == nullptr ? '{' : '[');
                    // See if we find an opening bracket in this part
                    while ((result < maxLength) && (stream[result] != character) && (stream[result] != ',') && (stream[result] != ']')&& (stream[result] != '}')) {
                        result++;
                    }

                    if (result < maxLength) {
                        if (stream[result] != character) {
                            _state = STATE_CLOSE;
                            _handleStack.pop_front();

                            if (_handleStack.empty() == false) {
                                current = _handleStack.front();
                            } else {
                                current = nullptr;
                            }
                        } else {
                            if (elementList == nullptr) {
                                _state = STATE_LABEL;
                            } else {
                                elementList->AddElement();

                                // Check if the new element is a container..
                                if (elementList->Element()->Type() == PARSE_CONTAINER) {
                                    current = elementList->Element()->ElementIterator();
                                    _handleStack.push_front(current);
                                    _state = STATE_OPEN;
                                } else {
                                    _state = STATE_START;
                                }
                            }
                            result++;
                            _offset = 0;
                        }
                    }
                    break;
                }
                case STATE_LABEL: {
                    if (_offset == 0) {
                        // Skip till we find a quote..
                        while ((result < maxLength) && (stream[result] != '\"') && (stream[result] != '}')) {
                            result++;
                        }

                        if (result < maxLength) {
                            if (stream[result] == '}') {
                                _state = STATE_CLOSE;
                                break;
                            } else {
                                _buffer.clear();
                                result++;
                                _offset = 1;
                            }
                        }
                    }

                    // Copy the label to the buffer..
                    while ((result < maxLength) && ((stream[result] != '\"') || ((_offset >= 2) && (_buffer[_offset - 2] == '\\')))) {
                        _buffer += stream[result++];
                        _offset++;
                    }

                    if (result < maxLength) {
                        result++;
                        _offset = 0;
                        _state = STATE_DELIMITER;
                    }
                    break;
                }
                case STATE_DELIMITER: {
                    if (_offset == 0) {
                        // See if we find a delimiter bracket in this part
                        while ((result < maxLength) && (stream[result] != ':')) {
                            result++;
                        }

                        if (result < maxLength) {
                            result++;
                            _offset = 1;
                        }
                    }
                    if (_offset == 1) {
                        // Skipp all whitespace
                        while ((result < maxLength) && (isspace(stream[result]))) {
                            result++;
                        }

                        if (result < maxLength) {
                            _offset = 0;

                            // Time to find what we will be filling !!!
                            if (static_cast<ILabelIterator*>(current)->Find(_buffer.c_str()) == false) {
                                _state = STATE_SKIP;
                                _quoted = QUOTED_OFF;
                                _levelSkip = 0;
                            } else if (current->Element()->Type() == PARSE_CONTAINER) {
                                // Oops it is another container.. reiterate..
                                current = current->Element()->ElementIterator();

                                _handleStack.push_front(current);

                                _state = STATE_OPEN;
                            } else {
                                _state = STATE_START;
                                _quoted = QUOTED_OFF;
                                _bufferUsed = 0;
                            }
                        }
                    }
                    break;
                }
                case STATE_SKIP: {
                    // Keep on reading till we find a '}' or a ','
                    // If we find a '{' in the wild we need to read till the next '}' and skipp all ','
                    while ((result < maxLength) && (_state == STATE_SKIP)) {
                        if (_quoted == QUOTED_ESCAPED) {
                            // Whatever the character, we should keep on reading!!
                            _quoted = QUOTED_ON;
                        } else if (_quoted == QUOTED_ON) {
                            if (stream[result] == '\"') {
                                _quoted = QUOTED_OFF;
                            } else if (stream[result] == '\\') {
                                _quoted = QUOTED_ESCAPED;
                            }
                        } else if ((stream[result] == '{') || (stream[result] == '[')) {
                            _levelSkip++;
                        } else if ((stream[result] == '}') || (stream[result] == ']')) {
                            if (_levelSkip == 0) {
                                _state = STATE_CLOSE;
                            } else {
                                _levelSkip--;
                            }
                        } else if (stream[result] == '\"') {
                            _quoted = QUOTED_ON;
                        } else if ((_levelSkip == 0) && (stream[result] == ',')) {
                            _state = STATE_CLOSE;
                        }

                        if (_state == STATE_SKIP) {
                            result++;
                        }
                    }

                    break;
                }
                case STATE_START: {
                    // Skip all whitespace
                    while ((result < maxLength) && (isspace(stream[result]))) {
                        result++;
                    }

                    if (result < maxLength) {
                        _state = STATE_VALUE;
                    } else {
                        break;
                    }
                }

                case STATE_VALUE: {
                    if (current->Element()->Type() == PARSE_DIRECT) {
                        // By definition, no specific handling required here, just deserialize what you have..
                        result += current->Element()->DirectParser()->Deserialize(reinterpret_cast<const char*>(&stream[result]), (maxLength - result), _offset);

                        if (_offset == 0) {
                            _state = STATE_SKIP;
                        }
                    } else {
                        if (_offset == 0) {
                            if (stream[result] == '\"') {
                                _quoted = QUOTED_ON;
                                result++;
                            }
                            _offset++;
                            _buffer.clear();
                        }
                        // Copy till closure state or MinSize is reached..
                        while ((result < maxLength) && (_state == STATE_VALUE)) {
                            if (_quoted == QUOTED_ESCAPED) {
                                // Whatever the character, we should keep on reading!!
                                _quoted = QUOTED_ON;
                            } else if (_quoted == QUOTED_ON) {
                                if (stream[result] == '\"') {
                                    result++;
                                    _quoted = QUOTED_OFF;
                                    _state = STATE_SKIP;
                                }
                            } else if ((_quoted == QUOTED_OFF) && (isspace(stream[result]))) {
                                _state = STATE_SKIP;
                            } else if ((stream[result] == '}') || (stream[result] == ']')) {
                                _state = STATE_CLOSE;
                            } else if (stream[result] == ',') {
                                _state = STATE_CLOSE;
                            }

                            if (_state == STATE_VALUE) {
                                _buffer += stream[result++];
                            }
                        }

                        if (_state != STATE_VALUE) {
                            // We now have the full pack unquoted, deserialize it.
                            _offset = 0;

                            // We need to build a buffer to get the next value complete
                            current->Element()->BufferParser()->Deserialize(_buffer);
                        }
                    }
                    break;
                }
                case STATE_CLOSE: {
                    while ((result < maxLength) && (current != nullptr) && (stream[result] != ',')) {
                        if ((stream[result] == '}') || (stream[result] == ']')) {
                            _state = STATE_HANDLED;
                            _handleStack.pop_front();

                            if (_handleStack.empty() == false) {
                                current = _handleStack.front();
                            } else {
                                current = nullptr;
                            }
                        }
                        result++;
                    }

                    if (result <= maxLength) {
                        // We handled the ','..
                        result++;

                        if (current != nullptr) {
                            IArrayIterator* elementList = dynamic_cast<IArrayIterator*>(current);

                            if (elementList == nullptr) {
                                _state = STATE_LABEL;
                            } else {
                                elementList->AddElement();

                                // Check if the new element is a container..
                                if (elementList->Element()->Type() == PARSE_CONTAINER) {
                                    current = elementList->Element()->ElementIterator();
                                    _handleStack.push_front(current);
                                    _state = STATE_OPEN;
                                } else {
                                    _state = STATE_START;
                                }
                            }
                        } else {
                            // If we have something to report, report it..
                            if (_handling != nullptr) {
                                Deserialized(*_handling);
                                _handling = nullptr;
                            }

                            _buffer.clear();
                            break;
                        }
                    }

                    break;
                }
                default: {
                    ASSERT(FALSE);
                    break;
                }
                }
            }

            _adminLock.Unlock();

            return (result);
        }

        bool IElement::Deserializer::Deserialize(const uint8_t stream[], const uint16_t maxLength, uint16_t& offset)
        {
            ASSERT(maxLength > 0);

            _containerLevel++;

            bool finished = false;
            ContainerLevelInfo* containerLevelInfo;
            std::map<uint16_t, ContainerLevelInfo*>::iterator it;

            it = _containerLevelMap.find(_containerLevel);

            if (it == _containerLevelMap.end()) {
                containerLevelInfo = new ContainerLevelInfo();
                Core::JSON::IElement* parentElement = Element();
                if (parentElement != nullptr ) {
                    containerLevelInfo->elementIterator = parentElement->ElementIterator();
                    containerLevelInfo->childElement = parentElement;
                }

                containerLevelInfo->result = RESULT_INPROGRESS;
                _containerLevelMap.insert(std::make_pair(_containerLevel, containerLevelInfo));
            } else {
                containerLevelInfo = it->second;
            }
            _result = containerLevelInfo->result;

            uint16_t startOffset = offset;
            for (;  ((offset < maxLength) && (finished == false)); offset++) {

                if (EnterScope(stream[offset]) || (containerLevelInfo->state == STATE_CONTAINER) ) {
                    if (IsEnterSet(containerLevelInfo->scopeBit) || (containerLevelInfo->state == STATE_CONTAINER)) {

                        Core::JSON::IElement* element = nullptr;
                        uint16_t currentOffset = offset;
                        if (containerLevelInfo->state != STATE_CONTAINER) {
                            if (containerLevelInfo->childElement != nullptr) {
                                if (containerLevelInfo->childElement->Type() == PARSE_CONTAINER) {
                                    if (stream[offset] == '[') {
                                        element = containerLevelInfo->childElement;
                                    } else {
                                        IArrayIterator* elementList = dynamic_cast<IArrayIterator*>(containerLevelInfo->childElement->ElementIterator());
                                        if (elementList != nullptr) {
                                            elementList->AddElement();
                                            element = elementList->Element();
                                        } else {
                                           element = containerLevelInfo->childElement;
                                        }
                                    }
                                }
                            }
                            containerLevelInfo->state = STATE_CONTAINER; // To maintain details for next level parsing
                            _element = element;
                        }

                        Deserialize(stream, maxLength, offset);
                        if (_result == RESULT_FAILURE) {
                            containerLevelInfo->result = _result;
                            finished = true;
                            break;
                        }

                        if (containerLevelInfo->childElement != nullptr) {
                            if (containerLevelInfo->childElement->Type() == PARSE_DIRECT) {

                                uint16_t size = ((offset > maxLength) ? (maxLength - currentOffset) : (offset - currentOffset));
                                containerLevelInfo->value.append((const char*)stream + currentOffset, size);
                                if (_result == RESULT_SUCCESS) {

                                    containerLevelInfo->childElement->DirectParser()->Deserialize(containerLevelInfo->value.c_str(), containerLevelInfo->value.length(), currentOffset, true);
                                    containerLevelInfo->value.clear();
                                }
                            }
                            _element = containerLevelInfo->childElement;
                        }

                        if (_result == RESULT_SUCCESS) {
                            containerLevelInfo->state = STATE_CONTAINER_VALUE;
                            containerLevelInfo->result = _result = RESULT_INPROGRESS;
                        }
                        offset--; //Just point to the end position of previous parsing
                    } else if (containerLevelInfo->state == STATE_VALUE) {
                        containerLevelInfo->state = STATE_CONTAINER;
                        offset--;
                    } else {
                        SetEnterBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                        if (stream[offset] == '[') {
                            SetSquareBracketBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                        }
                    }

                    if (IsCommaSet(containerLevelInfo->scopeBit)) {
                        ResetCommaBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                    }

                    if (IsDelimeterSet(containerLevelInfo->scopeBit)) {
                        ResetDelimeterBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                    }
                    continue;
                } else if (ExitScope(stream[offset])) {

                    finished = true;
                    if (IsSquareBracketSet(containerLevelInfo->scopeBit)) {
                        if (stream[offset] == ']') {
                            ResetSquareBracketBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                        } else {
                            containerLevelInfo->result = RESULT_FAILURE;
                            break;
                        }
                    } else if (stream[offset] == ']') {
                        break;
                    }

                    ResetEnterBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                    if (containerLevelInfo->state != STATE_VALUE) {
                        containerLevelInfo->result = _result = RESULT_SUCCESS;
                        continue;
                    }
                } else if (WhiteSpace(stream[offset])) {
                    // Skip whiteSpace.
                    continue;
                } else if (stream[offset] == ',') {

                    if ((containerLevelInfo->result == RESULT_INPROGRESS) && (containerLevelInfo->state == STATE_NONE)) { // Comma is occured before a valid data
                        containerLevelInfo->result = RESULT_FAILURE;
                        finished = true;
                        break;
                    }
                    if ((containerLevelInfo->state != STATE_VALUE) && (containerLevelInfo->state != STATE_CONTAINER_VALUE)) {
                        SetCommaBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                        containerLevelInfo->result = RESULT_INPROGRESS;
                    }
                } else {
                    if (containerLevelInfo->state == STATE_NONE) {
                        if (IsSquareBracketSet(containerLevelInfo->scopeBit)) {

                            containerLevelInfo->state = STATE_VALUE;
                            IArrayIterator* elementList = dynamic_cast<IArrayIterator*>(containerLevelInfo->elementIterator);
                            if (elementList != nullptr) {
                                elementList->AddElement();
                                containerLevelInfo->childElement = elementList->Element();
                            }

                            if (IsCommaSet(containerLevelInfo->scopeBit)) {
                                ResetCommaBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                            }
                        } else {
                            containerLevelInfo->state = STATE_KEY;
                        }
                    }
                }

                switch (containerLevelInfo->state) {
                case STATE_KEY: {
                    while ((offset < maxLength) && (containerLevelInfo->state == STATE_KEY)) {

                        if (stream[offset] == ':') {

                            if (IsValidKey(containerLevelInfo->key) != true) {
                                containerLevelInfo->result = RESULT_FAILURE;
                                finished = true;
                                break;
                            }

                            if (containerLevelInfo->elementIterator != nullptr) {
                                if (static_cast<ILabelIterator*>(containerLevelInfo->elementIterator)->Find(containerLevelInfo->key.c_str()) == true) {
                                    containerLevelInfo->childElement = static_cast<ILabelIterator*>(containerLevelInfo->elementIterator)->Element();
                                } else {
                                    containerLevelInfo->childElement = nullptr;
                                }
                            }

                            containerLevelInfo->state = STATE_VALUE;
                            SetDelimeterBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                            if (IsCommaSet(containerLevelInfo->scopeBit)) {
                                ResetCommaBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                            }

                            containerLevelInfo->key.clear();
                        } else {
                            containerLevelInfo->key += stream[offset];
                            offset++;
                        }
                    }
                    break;
                }
                case STATE_VALUE:
                case STATE_CONTAINER_VALUE: {
                    while ((offset < maxLength) && ((containerLevelInfo->state == STATE_VALUE) || (containerLevelInfo->state == STATE_CONTAINER_VALUE))) {

                        if (((stream[offset] == ',') && ((IsCompleteData(containerLevelInfo->value) == true) || (containerLevelInfo->state == STATE_CONTAINER_VALUE))) || (ExitScope(stream[offset]))) {

                            if (((containerLevelInfo->state == STATE_VALUE)) && IsValidData(containerLevelInfo->value) != true) {
                                finished = true;
                                containerLevelInfo->result = RESULT_FAILURE;
                                break;
                            }

                            if (stream[offset] == ',') {
                                SetCommaBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                                containerLevelInfo->result = RESULT_INPROGRESS; // Reset to indicate that we have to parse some more data.
                            } else {
                                containerLevelInfo->result = RESULT_SUCCESS; // At the end of bracket.
                                if (finished == false) {
                                    offset--;
                                }
                            }

                            if (IsDelimeterSet(containerLevelInfo->scopeBit)) {
                                ResetDelimeterBit(containerLevelInfo->scopeBit, containerLevelInfo->scopeCount);
                            }

                            if (containerLevelInfo->state == STATE_VALUE){
                            if (containerLevelInfo->childElement != nullptr) {
                                if (containerLevelInfo->childElement->Type() == PARSE_BUFFERED) {
                                    containerLevelInfo->childElement->BufferParser()->Deserialize(containerLevelInfo->value);
                                } else if (containerLevelInfo->childElement->Type() == PARSE_DIRECT) {
                                    uint16_t offset = 0;
                                    containerLevelInfo->childElement->DirectParser()->Deserialize(containerLevelInfo->value.c_str(), containerLevelInfo->value.length(), offset, true);
                                } else {
                                    containerLevelInfo->result = RESULT_FAILURE;
                                }
                            }
                            }
                            containerLevelInfo->state = STATE_NONE;
                            containerLevelInfo->value.clear();
                        } else {
                            containerLevelInfo->value += stream[offset];
                            offset++;
                        }
                    }
                    break;
                }
                case STATE_NONE:
                    break; //Just skip
                default:
                    ASSERT(FALSE);
                    break;
                }
            }

            bool status = true;
            if ((startOffset == 0) && (offset < maxLength) && (_containerLevel == 1)) {
                status = false;
            }
            if (/*(containerLevelInfo->result == RESULT_FAILURE) ||*/ (finished == true) && (containerLevelInfo->result != RESULT_INPROGRESS)) {
                if ((containerLevelInfo->scopeCount != 0) || (containerLevelInfo->result == RESULT_FAILURE)) {
                    status = false;
                }
                _containerLevelMap.erase(_containerLevel);
                delete containerLevelInfo;
            }

            _containerLevel--;
            _result = containerLevelInfo->result;

            return (status);
        }
    }
}

} //namespace Core::JSON
