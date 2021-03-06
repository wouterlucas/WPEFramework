#ifndef __WEBBRIDGESUPPORT_CONFIGURATION_H
#define __WEBBRIDGESUPPORT_CONFIGURATION_H

#include "Config.h"
#include "IPlugin.h"
#include "IShell.h"
#include "ISubSystem.h"
#include "Module.h"

namespace WPEFramework {
namespace Plugin {
    class EXTERNAL Config : public Core::JSON::Container {
    public:
        Config()
            : Core::JSON::Container()
            , Callsign()
            , Locator()
            , ClassName()
            , Versions()
            , AutoStart(true)
            , Resumed(false)
            , WebUI()
            , Precondition()
            , Termination()
            , Configuration(false)
        {
            Add(_T("callsign"), &Callsign);
            Add(_T("locator"), &Locator);
            Add(_T("classname"), &ClassName);
            Add(_T("versions"), &Versions);
            Add(_T("autostart"), &AutoStart);
            Add(_T("resumed"), &Resumed);
            Add(_T("webui"), &WebUI);
            Add(_T("precondition"), &Precondition);
            Add(_T("termination"), &Termination);
            Add(_T("configuration"), &Configuration);
        }
        Config(const Config& copy)
            : Core::JSON::Container()
            , Callsign(copy.Callsign)
            , Locator(copy.Locator)
            , ClassName(copy.ClassName)
            , Versions(copy.Versions)
            , AutoStart(copy.AutoStart)
            , Resumed(copy.Resumed)
            , WebUI(copy.WebUI)
            , Precondition(copy.Precondition)
            , Termination(copy.Termination)
            , Configuration(copy.Configuration)
        {
            Add(_T("callsign"), &Callsign);
            Add(_T("locator"), &Locator);
            Add(_T("classname"), &ClassName);
            Add(_T("versions"), &Versions);
            Add(_T("autostart"), &AutoStart);
            Add(_T("resumed"), &Resumed);
            Add(_T("webui"), &WebUI);
            Add(_T("precondition"), &Precondition);
            Add(_T("termination"), &Termination);
            Add(_T("configuration"), &Configuration);
        }
        ~Config()
        {
        }

        Config& operator=(const Config& RHS)
        {
            Callsign = RHS.Callsign;
            Locator = RHS.Locator;
            ClassName = RHS.ClassName;
            Versions = RHS.Versions;
            AutoStart = RHS.AutoStart;
            Resumed = RHS.Resumed;
            WebUI = RHS.WebUI;
            Configuration = RHS.Configuration;
            Precondition = RHS.Precondition;
            Termination = RHS.Termination;

            return (*this);
        }

    public:
        Core::JSON::String Callsign;
        Core::JSON::String Locator;
        Core::JSON::String ClassName;
        Core::JSON::String Versions;
        Core::JSON::Boolean AutoStart;
        Core::JSON::Boolean Resumed;
        Core::JSON::String WebUI;
        Core::JSON::ArrayType<Core::JSON::EnumType<PluginHost::ISubSystem::subsystem>> Precondition;
        Core::JSON::ArrayType<Core::JSON::EnumType<PluginHost::ISubSystem::subsystem>> Termination;
        Core::JSON::String Configuration;

        static Core::NodeId IPV4UnicastNode(const string& ifname);

    public:
        inline bool IsSameInstance(const Config& RHS) const
        {
            return ((Locator.Value() == RHS.Locator.Value()) && (ClassName.Value() == RHS.ClassName.Value()));
        }
    };

    class EXTERNAL Setting : public Trace::Text {
    private:
        // -------------------------------------------------------------------
        // This object should not be copied or assigned. Prevent the copy
        // constructor and assignment constructor from being used. Compiler
        // generated assignment and copy methods will be blocked by the
        // following statments.
        // Define them but do not implement them, compile error/link error.
        // -------------------------------------------------------------------
        Setting(const Setting& a_Copy) = delete;
        Setting& operator=(const Setting& a_RHS) = delete;

    public:
        Setting(const string& key, const bool value)
        {
            Trace::Text::Set(_T("Setting: [") + key + _T("] set to value [") + (value ? _T("TRUE]") : _T("FALSE]")));
        }
        Setting(const string& key, const string& value)
        {
            Trace::Text::Set(_T("Setting: [") + key + _T("] set to value [") + value + _T("]"));
        }
        template <typename NUMBERTYPE, const bool SIGNED, const NumberBase BASETYPE>
        Setting(const string& key, const NUMBERTYPE value)
        {
            Core::NumberType<NUMBERTYPE, SIGNED, BASETYPE> number(value);
            Trace::Text::Set(_T("Setting: [") + key + _T("] set to value [") + number.Text() + _T("]"));
        }
        ~Setting()
        {
        }
    };
}

namespace PluginHost {

    class EXTERNAL Config {
    private:
        Config();
        Config(const Config&);
        Config operator=(const Config&);

    public:
        Config(
            const string& version,
            const string& model,
            const bool background,
            const string& webPrefix,
            const string& JSONRPCPrefix,
            const string& volatilePath,
            const string& persistentPath,
            const string& dataPath,
            const string& systemPath,
            const string& proxyStubPath,
            const string& hashKey,
            const Core::NodeId& accessor,
            const Core::NodeId& communicator,
            const string& redirect)
            : _webPrefix('/' + webPrefix)
            , _JSONRPCPrefix('/' + JSONRPCPrefix)
            , _volatilePath(Core::Directory::Normalize(volatilePath))
            , _persistentPath(Core::Directory::Normalize(persistentPath))
            , _dataPath(Core::Directory::Normalize(dataPath))
            , _hashKey(hashKey)
            , _appPath(Core::File::PathName((Core::ProcessInfo().Executable())))
            , _systemPath(Core::Directory::Normalize(systemPath))
            , _proxyStubPath(Core::Directory::Normalize(proxyStubPath))
            , _accessor(accessor)
            , _communicator(communicator)
            , _redirect(redirect)
            , _security(nullptr)
            , _background(background)
            , _version(version)
            , _model(model)
        {
            ASSERT(_appPath.empty() == false);
        }
        ~Config()
        {
            ASSERT(_security != nullptr);
            _security->Release();
        }

    public:
        inline const string& Version() const
        {
            return (_version);
        }
        inline const string& Model() const
        {
            return (_model);
        }
        inline const string& Redirect() const
        {
            return (_redirect);
        }
        inline const string& WebPrefix() const
        {
            return (_webPrefix);
        }
        inline const string& JSONRPCPrefix() const
        {
            return (_JSONRPCPrefix);
        }
        inline const string& VolatilePath() const
		{
            return (_volatilePath);
        }
        inline const string& PersistentPath() const
        {
            return (_persistentPath);
        }
        inline const string& DataPath() const
        {
            return (_dataPath);
        }
        inline const string& AppPath() const
        {
            return (_appPath);
        }
        inline const Core::NodeId& Accessor() const
        {
            return (_accessor);
        }
        inline const Core::NodeId& Communicator() const
        {
            return (_communicator);
        }
        inline const string& SystemPath() const
        {
            return (_systemPath);
        }
        inline const string& ProxyStubPath() const
        {
            return (_proxyStubPath);
        }
        inline const string& HashKey() const
        {
            return (_hashKey);
        }
        inline ISecurity* Security() const
        {
            _security->AddRef();
            return (_security);
        }
        inline bool Background() const
        {
            return (_background);
        }

	private:
        friend class Server;

        inline void Security(ISecurity* security)
        {
            ASSERT((_security == nullptr) && (security != nullptr));

            _security = security;

            if (_security != nullptr) {
                _security->AddRef();
			}
        }

    private:
        const string _webPrefix;
        const string _JSONRPCPrefix;
        const string _volatilePath;
        const string _persistentPath;
        const string _dataPath;
        const string _hashKey;
        const string _appPath;
        const string _systemPath;
        const string _proxyStubPath;
        const Core::NodeId _accessor;
        const Core::NodeId _communicator;
        const string _redirect;
        ISecurity* _security;
        bool _background;
        const string _version;
        const string _model;
    };
}
}

#endif // __WEBBRIDGESUPPORT_CONFIGURATION_H
