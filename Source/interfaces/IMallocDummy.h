#ifndef _IMALLOCDUMMY_H
#define _IMALLOCDUMMY_H

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct IMallocDummy : virtual public Core::IUnknown {
        //QA: How to increment interface ID
        enum { ID = 0x00000011 };

        virtual ~IMallocDummy() {}
        virtual uint64_t Malloc(uint64_t size) = 0;
        virtual uint64_t GetAllocatedMemory(void) = 0;
    };
}
}

#endif // _IMALLOCDUMMY_H
