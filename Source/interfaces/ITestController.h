#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

struct ITestController : virtual public Core::IUnknown {
    enum { ID = 0x11000024 };

    virtual ~ITestController() {}

    virtual string /*JSON*/ Process(const string& path, const uint8_t skipUrl, const string& body) = 0;
};
} // namespace Exchange
} // namespace WPEFramework
