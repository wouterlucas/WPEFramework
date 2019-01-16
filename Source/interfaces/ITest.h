#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

struct ITest : virtual public Core::IUnknown {
    enum { ID = 0x11000023 };

    virtual ~ITest() {}

    virtual void Setup(const string& body) = 0;
    virtual const string& /*JSON*/ Execute(const string& method) = 0;
    virtual void Cleanup(void) = 0;

    virtual const std::list<string> /*JSON*/ GetMethods(void) = 0;
    virtual const string& /*JSON*/ GetMethodDes(const string& method) = 0;
    virtual const string& /*JSON*/ GetMethodParam(const string& method) = 0;

};
} // namespace Exchange
} // namespace WPEFramework
