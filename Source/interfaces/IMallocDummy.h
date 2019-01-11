#ifndef _IMALLOCDUMMY_H
#define _IMALLOCDUMMY_H

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct IMallocDummy : virtual public Core::IUnknown {
        //QA: How to increment interface ID
        enum { ID = 0x11000011 };

        virtual ~IMallocDummy() {}
        virtual uint32_t Malloc(uint32_t size) = 0;
        virtual void Free(void) = 0;
        virtual void Statm(uint32_t &allocated, uint32_t &size, uint32_t &resident) = 0;
    };
}
}

#endif // _IMALLOCDUMMY_H
