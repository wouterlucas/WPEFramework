#ifndef __ICRASHDUMMY_H
#define __ICRASHDUMMY_H

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

struct ICrashDummy : virtual public Core::IUnknown {

    enum { ID = 0x00000072 };

    virtual ~ICrashDummy() {}

    virtual void Crash() = 0;
    virtual bool Configure(PluginHost::IShell *shell) = 0;

};

} // Exchange
} // WPEFramework

#endif // __ICRASHDUMMY_H
