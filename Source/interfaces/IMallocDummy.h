#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct IMallocDummy : virtual public Core::IUnknown {
        //ToDo: ID needs to be adjusted
        enum { ID = 0x11000011 };

        virtual ~IMallocDummy() {}
        virtual uint32_t Malloc(uint32_t size) = 0;
        virtual void Free(void) = 0;
        virtual void Statm(uint32_t &allocated, uint32_t &size, uint32_t &resident) = 0;
    };
}
}
