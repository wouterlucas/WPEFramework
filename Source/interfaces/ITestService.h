#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

struct ITestService : virtual public Core::IUnknown {
    // ToDo: ID needs to be adjusted
    enum { ID = 0x11000022 };

    virtual ~ITestService() {}

    virtual uint32_t Malloc(uint32_t size) = 0;
    virtual void Free(void) = 0;
    virtual void Statm(uint32_t& allocated, uint32_t& size, uint32_t& resident) = 0;

    virtual bool Configure(PluginHost::IShell* shell) = 0;
    virtual void Crash() = 0;
    virtual bool CrashNTimes(uint8_t n) = 0;
    virtual void ExecPendingCrash() = 0;
    virtual uint8_t PendingCrashCount() = 0;
};
} // namespace Exchange
} // namespace WPEFramework
