#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

struct ICrashDummy : virtual public Core::IUnknown {

    enum { ID = 0x00000072 };

    virtual ~ICrashDummy() {}

    virtual bool Configure(PluginHost::IShell* shell) = 0;
    virtual void Crash() = 0;
    virtual bool CrashNTimes(uint8_t n) = 0;
    virtual void ExecPendingCrash() = 0;
    virtual uint8_t PendingCrashCount() = 0;

};

} // namespace Exchange
} // namespace WPEFramework
