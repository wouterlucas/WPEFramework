#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct ISystemCommand : virtual public Core::IUnknown {
        enum { ID = 0x00000072 };

        typedef struct {
            string name;
            string value;
        } CommandParam;

        using CommandParams = std::vector<CommandParam>;
        using CommandId = string;

        struct IExecutor : virtual public Core::IUnknown {
            enum { ID = 0x00000073 };

            virtual ~IExecutor() {}

            virtual bool Execute(const CommandParams& params) = 0;
        };

        virtual ~ISystemCommand() {}

        virtual void Register(const CommandId& id, ISystemCommand::IExecutor* delegate) = 0;
        virtual void Unregister(ISystemCommand::IExecutor* delegate) = 0;

        virtual bool Execute(const CommandId& id, const CommandParams& params) = 0;
        virtual std::vector<CommandId> SupportedCommands() const = 0;
    };

}  // namespace Exchange
}  // namespace WPEFramework
