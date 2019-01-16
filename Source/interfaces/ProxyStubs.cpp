#include "IAVNClient.h"
#include "IBluetooth.h"
#include "IBrowser.h"
#include "IComposition.h"
#include "IDictionary.h"
#include "IGuide.h"
#include "INetflix.h"
#include "IContentDecryption.h"
#include "INetflix.h"
#include "IPlayGiga.h"
#include "IProvisioning.h"
#include "IPower.h"
#include "IRPCLink.h"
#include "IRtspClient.h"
#include "IStreaming.h"
#include "ITVControl.h"
#include "IWebDriver.h"
#include "IWebServer.h"
#include "ITestService.h"

MODULE_NAME_DECLARATION(BUILDREF_WEBBRIDGE)

namespace WPEFramework {
namespace ProxyStubs {

    using namespace Exchange;

    // -------------------------------------------------------------------------------------------
    // STUB
    // -------------------------------------------------------------------------------------------

    //
    // IBrowser interface stub definitions (interface/IBrowser.h)
    //
    ProxyStub::MethodHandler BrowserStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void SetURL(const string& URL) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());

            message->Parameters().Implementation<IBrowser>()->SetURL(parameters.Text());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual string GetURL() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IBrowser>()->GetURL());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t GetFPS() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Number(message->Parameters().Implementation<IBrowser>()->GetFPS());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Register(IBrowser::INotification* sink) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IBrowser::INotification* implementation = reader.Number<IBrowser::INotification*>();
            IBrowser::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IBrowser::INotification>(channel,
                implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IBrowserNotification: %p"), implementation);
            } else {
                parameters.Implementation<IBrowser>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Unregister(IBrowser::INotification* sink) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            // Need to find the proxy that goes with the given implementation..
            IBrowser::INotification* stub = reader.Number<IBrowser::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            IBrowser::INotification* proxy = RPC::Administrator::Instance().FindProxy<IBrowser::INotification>(channel.operator->(), stub);


            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find stub for IBrowserNotification: %p"), stub);
            } else {
                parameters.Implementation<IBrowser>()->Unregister(proxy);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // Careful, this method is out of interface order
            //
            // virtual void Hide(const bool hidden) = 0
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());

            message->Parameters().Implementation<IBrowser>()->Hide(parameters.Boolean());
        },
        nullptr
    };
    // IBrowser interface stub definitions

    //
    // IBrowser::INotification interface stub definitions (interface/IBrowser.h)
    //
    ProxyStub::MethodHandler BrowserNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void LoadFinished(const string& URL) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string URL(parameters.Text());

            message->Parameters().Implementation<IBrowser::INotification>()->LoadFinished(URL);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void URLChanged(const string& URL) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string URL(parameters.Text());

            ASSERT(message.IsValid() == true);
            ASSERT(message->Parameters().Implementation<IBrowser::INotification>() != nullptr);

            message->Parameters().Implementation<IBrowser::INotification>()->URLChanged(URL);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Hidden(const bool hidden) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            bool hidden(parameters.Boolean());

            ASSERT(message.IsValid() == true);
            ASSERT(message->Parameters().Implementation<IBrowser::INotification>() != nullptr);

            message->Parameters().Implementation<IBrowser::INotification>()->Hidden(hidden);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Closure() = 0;
            //
            ASSERT(message.IsValid() == true);
            ASSERT(message->Parameters().Implementation<IBrowser::INotification>() != nullptr);

            message->Parameters().Implementation<IBrowser::INotification>()->Closure();
        },
        nullptr
    };
    // IBrowser::INotification interface stub definitions

    ProxyStub::MethodHandler GuideStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {

            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IGuide: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            }
            else {
                writer.Number(parameters.Implementation<IGuide>()->StartParser(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IGuide::INotification* implementation = reader.Number<IGuide::INotification*>();
            IGuide::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IGuide::INotification>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IGuide::INotification: %p"), implementation);
            }
            else {
                parameters.Implementation<IGuide>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IGuide::INotification* stub = reader.Number<IGuide::INotification*>();
            IGuide::INotification* proxy = RPC::Administrator::Instance().FindProxy<IGuide::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find stub for IGuide::Notification: %p"), stub);
            }
            else {
                parameters.Implementation<IGuide>()->Unregister(proxy);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // const string GetChannels()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IGuide>()->GetChannels());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // const string GetPrograms(const uint32_t channelNum)
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IGuide>()->GetPrograms());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // const string GetCurrentProgram()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            response.Text(message->Parameters().Implementation<IGuide>()->GetCurrentProgram(parameters.Text()));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // const string GetAudioLanguages()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            response.Text(message->Parameters().Implementation<IGuide>()->GetAudioLanguages(parameters.Number<uint32_t>()));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // const string GetSubtitleLanguages()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            response.Text(message->Parameters().Implementation<IGuide>()->GetSubtitleLanguages(parameters.Number<uint32_t>()));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // bool SetParentalControlPin(const string&, const string&)
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string oldPin(parameters.Text());
            string newPin(parameters.Text());
            response.Boolean(message->Parameters().Implementation<IGuide>()->SetParentalControlPin(oldPin, newPin));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // bool SetParentalControl(const string&, const bool)
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string pin(parameters.Text());
            bool isLocked(parameters.Boolean());
            response.Boolean(message->Parameters().Implementation<IGuide>()->SetParentalControl(pin, isLocked));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // bool IsParentalControlled()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Boolean(message->Parameters().Implementation<IGuide>()->IsParentalControlled());

        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // bool SetParentalLock(const string&, const bool, const string&)
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string pin(parameters.Text());
            bool isLocked(parameters.Boolean());
            string channelNum(parameters.Text());
            response.Boolean(message->Parameters().Implementation<IGuide>()->SetParentalLock(pin, isLocked, channelNum));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // bool IsParentalLocked(const uint32_t);
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string channelNum(parameters.Text());
            response.Boolean(message->Parameters().Implementation<IGuide>()->IsParentalLocked(channelNum));
        },
        nullptr
    };

    //
    // IWebDriver interface stub definitions (interface/IWebDriver.h)
    //
    ProxyStub::MethodHandler WebDriverStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Configure(PluginHost::IShell* framework) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for WebDriver: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            } else {
                writer.Number(parameters.Implementation<IWebDriver>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        nullptr
    };
    // IWebDriver interface stub definitions


    //
    // ITestService interface stub definitions (interface/ITestService.h)
    //
    ProxyStub::MethodHandler TestServiceStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Malloc(uint32_t size) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            uint32_t size(parameters.Number<uint32_t>());
            uint32_t result = message->Parameters().Implementation<ITestService>()->Malloc(size);

            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Number<uint32_t>(result);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            //  virtual void Free(void) = 0;
            //
            message->Parameters().Implementation<ITestService>()->Free();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            //  virtual void Statm(uint32_t &allocated, uint32_t &size, uint32_t &resident) = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            uint32_t allocated = 0; /* If it would be in->out, you need to read them from the package and fill */
            uint32_t size = 0;   /* them in here, but these are just out values. */
            uint32_t resident = 0;
            message->Parameters().Implementation<ITestService>()->Statm(allocated, size, resident);
            response.Number<uint32_t>(allocated);
            response.Number<uint32_t>(size);
            response.Number<uint32_t>(resident);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual bool Configure(PluginHost::IShell *shell) = 0;
            RPC::Data::Frame::Reader reader(message->Parameters().Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");
            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for ICrashDummy: %p"), implementation);
                writer.Number<bool>(false);
            }
            else {
                writer.Number(message->Parameters().Implementation<ITestService>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Crash() = 0;
            //
            message->Parameters().Implementation<ITestService>()->Crash();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual bool CrashNTimes(uint8_t n) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            uint8_t n(parameters.Number<uint8_t>());
            writer.Number(message->Parameters().Implementation<ITestService>()->CrashNTimes(n));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void ExecPendingCrash() = 0;
            //
            message->Parameters().Implementation<ITestService>()->ExecPendingCrash();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint8_t PendingCrashCount() = 0;
            //
            RPC::Data::Frame::Writer writer(message->Response().Writer());
            writer.Number(message->Parameters().Implementation<ITestService>()->PendingCrashCount());
        },
        nullptr
    };
    // ITestService interface stub definitions

    //
    // IBluetooth interface stub definitions (interface/IBluetooth.h)
    //
     ProxyStub::MethodHandler BluetoothStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Configure(PluginHost::IShell* service) = 0;
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for Bluetooth: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            } else {
                writer.Number(parameters.Implementation<IBluetooth>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // Scan()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Boolean(message->Parameters().Implementation<IBluetooth>()->Scan());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // StopScan()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Boolean(message->Parameters().Implementation<IBluetooth>()->StopScan());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // DiscoveredDevices()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IBluetooth>()->DiscoveredDevices());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // PairedDevices()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IBluetooth>()->PairedDevices());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // Pair()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            response.Boolean(message->Parameters().Implementation<IBluetooth>()->Pair(parameters.Text()));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // Connect()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            response.Boolean(message->Parameters().Implementation<IBluetooth>()->Connect(parameters.Text()));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // Disconnect()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Boolean(message->Parameters().Implementation<IBluetooth>()->Disconnect());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // IsScanning()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Boolean(message->Parameters().Implementation<IBluetooth>()->IsScanning());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // Connected()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IBluetooth>()->Connected());
        },
        nullptr
    };
    // IBluetooth interface stub definitions

    //
    // IOCDM interface stub definitions (interface/IOCDM.h)
    //
    ProxyStub::MethodHandler OpenCDMiStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Configure(PluginHost::IShell* service) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for WebDriver: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            } else {
                writer.Number(parameters.Implementation<IContentDecryption>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Reset() = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Number(message->Parameters().Implementation<IContentDecryption>()->Reset());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual RPC::IStringIterator* Systems() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Number(message->Parameters().Implementation<IContentDecryption>()->Systems());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual RPC::IStringIterator* Designators(const string& keySystem) const = 0;
            //
            RPC::Data::Frame::Reader reader(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
            string keySystem (reader.Text());
            response.Number(message->Parameters().Implementation<IContentDecryption>()->Designators(keySystem));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual RPC::IStringIterator* Sessions(const string& keySystem) const = 0;
            //
            RPC::Data::Frame::Reader reader(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());
            string keySystem (reader.Text());
            response.Number(message->Parameters().Implementation<IContentDecryption>()->Sessions(keySystem));
        },
        nullptr
    };
    // IContentDecryption interface stub definitions

    //
    // INetflix interface stub definitions (interface/INetflix.h)
    //
    ProxyStub::MethodHandler NetflixStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Register(INetflix::INotification* netflix) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            INetflix::INotification* implementation = reader.Number<INetflix::INotification*>();
            INetflix::INotification* proxy = RPC::Administrator::Instance().CreateProxy<INetflix::INotification>(channel,
                implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for INetflixNotification: %p"), implementation);
            } else {
                parameters.Implementation<INetflix>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Unregister(INetflix::INotification* netflix) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            // Need to find the proxy that goes with the given implementation..
            INetflix::INotification* stub = reader.Number<INetflix::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            INetflix::INotification* proxy = RPC::Administrator::Instance().FindProxy<INetflix::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find stub for IBrowserNotification: %p"), stub);
            } else {
                parameters.Implementation<INetflix>()->Unregister(proxy);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual string GetESN() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<INetflix>()->GetESN());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void FactoryReset() = 0;
            //
            message->Parameters().Implementation<INetflix>()->FactoryReset();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void SystemCommand(const string& command) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string element(parameters.Text());
            message->Parameters().Implementation<INetflix>()->SystemCommand(element);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Language(const string& language) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string element(parameters.Text());
            message->Parameters().Implementation<INetflix>()->Language(element);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void SetVisible(bool visibility) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<INetflix>()->SetVisible(parameters.Boolean());
        },
        nullptr
    };
    // INetflix interface stub definitions

    //
    // INetflix::INotification interface stub definitions (interface/INetflix.h)
    //
    ProxyStub::MethodHandler NetflixNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void StateChange(const INetflix::state state) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            INetflix::state newState(parameters.Number<INetflix::state>());

            message->Parameters().Implementation<INetflix::INotification>()->StateChange(newState);
        },
        nullptr
    };
    // INetflix::INotification interface stub definitions

    //
    // IProvisioning interface stub definitions (interface/IProvisioning.h)
    //
    ProxyStub::MethodHandler ProvisioningStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Register(IProvisioning::INotification* provisioning) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IProvisioning::INotification* implementation = reader.Number<IProvisioning::INotification*>();
            IProvisioning::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IProvisioning::INotification>(
                channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IProvisioningNotification: %p"), implementation);
            } else {
                parameters.Implementation<IProvisioning>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Unregister(IProvisioning::INotification* provisioning) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            // Need to find the proxy that goes with the given implementation..
            IProvisioning::INotification* stub = reader.Number<IProvisioning::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            IProvisioning::INotification* proxy = RPC::Administrator::Instance().FindProxy<IProvisioning::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find a stub for IProvisioningNotification: %p"), stub);
            } else {
                parameters.Implementation<IProvisioning>()->Unregister(proxy);
            }
        },
        nullptr
    };
    // IProvisioning interface stub definitions

    //
    // IProvisioning::INotification interface stub definitions (interface/IProvisioning.h)
    //
    ProxyStub::MethodHandler ProvisioningNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Provisioned(const string& component) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string element(parameters.Text());

            message->Parameters().Implementation<IProvisioning::INotification>()->Provisioned(element);
        },
        nullptr
    };
    // IProvisioning::INotification interface stub definitions

    //
    // IComposition interface stub definitions (interface/IComposition.h)
    //
    ProxyStub::MethodHandler CompositionStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Register(IComposition::INotification* notification) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IComposition::INotification* implementation = reader.Number<IComposition::INotification*>();
            IComposition::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IComposition::INotification>(
                channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for ICompositionNotification: %p"), implementation);
            } else {
                parameters.Implementation<IComposition>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Unregister(IComposition::INotification* notification) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            // Need to find the proxy that goes with the given implementation..
            IComposition::INotification* stub = reader.Number<IComposition::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            IComposition::INotification* proxy = RPC::Administrator::Instance().FindProxy<IComposition::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find a stub for ICompositionNotification: %p"), stub);
            } else {
                parameters.Implementation<IComposition>()->Unregister(proxy);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual IClient* Client(const uint8_t index) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer output(message->Response().Writer());

            output.Number<IComposition::IClient*>(parameters.Implementation<IComposition>()->Client(reader.Number<uint8_t>()));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual IClient* Client(const string& name) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer output(message->Response().Writer());

            output.Number<IComposition::IClient*>(parameters.Implementation<IComposition>()->Client(reader.Text()));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Configure(PluginHost::IShell* service) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(
                    channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a proxy for PluginHost::IShell: %p"), implementation);
            } else {
                writer.Number(parameters.Implementation<IComposition>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Resolution(const ScreenResolution) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            parameters.Implementation<IComposition>()->Resolution(reader.Number<IComposition::ScreenResolution>());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual ScreenResolution Resolution() const = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            writer.Number<IComposition::ScreenResolution>(parameters.Implementation<IComposition>()->Resolution());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
                //
                // virtual uint32_t Geometry(const string& callsign, const IComposition::Rectangle& rectangle) = 0;
                //
                RPC::Data::Input& parameters(message->Parameters());
                RPC::Data::Frame::Reader reader(parameters.Reader());
                const std::string name(reader.Text());
                IComposition::Rectangle rectangle;
                rectangle.x = reader.Number<uint32_t>();
                rectangle.y = reader.Number<uint32_t>();
                rectangle.width = reader.Number<uint32_t>();
                rectangle.height = reader.Number<uint32_t>();
                RPC::Data::Frame::Writer writer(message->Response().Writer());
                writer.Number<uint32_t>(parameters.Implementation<IComposition>()->Geometry(name, rectangle));

        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
                //
                // virtual IComposition::Rectangle Geometry(const string& callsign) const;
                //
                RPC::Data::Input& parameters(message->Parameters());
                RPC::Data::Frame::Reader reader(parameters.Reader());
                const std::string name(reader.Text());
                IComposition::Rectangle rectangle = parameters.Implementation<IComposition>()->Geometry(name);
                RPC::Data::Frame::Writer writer(message->Response().Writer());
                writer.Number<uint32_t>(rectangle.x);
                writer.Number<uint32_t>(rectangle.y);
                writer.Number<uint32_t>(rectangle.width);
                writer.Number<uint32_t>(rectangle.height);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
                //
                // virtual uint32_t ToTop(const string& callsign) = 0;
                //
                RPC::Data::Input& parameters(message->Parameters());
                RPC::Data::Frame::Reader reader(parameters.Reader());
                const std::string callsign(reader.Text());
                uint32_t result = parameters.Implementation<IComposition>()->ToTop(callsign);
                RPC::Data::Frame::Writer writer(message->Response().Writer());
                writer.Number<uint32_t>(result);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
                //
                // virtual uint32_t PutBelow(const string& callsignRelativeTo, const string& callsignToReorder);
                //
                RPC::Data::Input& parameters(message->Parameters());
                RPC::Data::Frame::Reader reader(parameters.Reader());
                const std::string callsignRelativeTo(reader.Text());
                const std::string callsignToReorder(reader.Text());
                uint32_t result = parameters.Implementation<IComposition>()->PutBelow(callsignRelativeTo, callsignToReorder);
                RPC::Data::Frame::Writer writer(message->Response().Writer());
                writer.Number<uint32_t>(result);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
                //
                // virtual RPC::IStringIterator* ClientsInZorder() const
                //
                RPC::Data::Frame::Writer response(message->Response().Writer());
                response.Number(message->Parameters().Implementation<IComposition>()->ClientsInZorder());
        },
        nullptr
    };
    // IComposition interface stub definitions

    //
    // IComposition::IClient interface stub definitions (interface/IComposition.h)
    //
    ProxyStub::MethodHandler CompositionClientStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual string Name() const = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            writer.Text(parameters.Implementation<IComposition::IClient>()->Name());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Kill() = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());

            parameters.Implementation<IComposition::IClient>()->Kill();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Opacity(const uint32_t value) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            parameters.Implementation<IComposition::IClient>()->Opacity(reader.Number<uint32_t>());

        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void ChangedGeometry(const Rectangle& rectangle);;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            IComposition::Rectangle rectangle = IComposition::Rectangle();
            rectangle.x = reader.Number<uint32_t>();
            rectangle.y = reader.Number<uint32_t>();
            rectangle.width = reader.Number<uint32_t>();
            rectangle.height = reader.Number<uint32_t>();
            parameters.Implementation<IComposition::IClient>()->ChangedGeometry(rectangle);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void ChangedZOrder(const uint8_t zorder);
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            parameters.Implementation<IComposition::IClient>()->ChangedZOrder(reader.Number<uint8_t>());
        },
        nullptr
    };
    // IComposition::IClient interface stub definitions

    //
    // IComposition::INotification interface stub definitions (interface/IComposition.h)
    //
    ProxyStub::MethodHandler CompositionNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Attached(IClient* client) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            IComposition::IClient* implementation = reader.Number<IComposition::IClient*>();
            IComposition::IClient* proxy = RPC::Administrator::Instance().CreateProxy<IComposition::IClient>(channel,
                implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IComposition::IClient %p"), implementation);
            } else {
                parameters.Implementation<IComposition::INotification>()->Attached(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Detached(IClient* client) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            IComposition::IClient* implementation = reader.Number<IComposition::IClient*>();
            IComposition::IClient* proxy = RPC::Administrator::Instance().CreateProxy<IComposition::IClient>(channel,
                implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IComposition::IClient %p"), implementation);
            } else {
                parameters.Implementation<IComposition::INotification>()->Detached(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        nullptr
    };
    // IComposition::INotification interface stub definitions

    //
    // IWebServer interface stub definitions (interface/IWebServer.h)
    //
    ProxyStub::MethodHandler WebServerStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void AddProxy(const string& path, const string& subst, const string& address) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string path(parameters.Text());
            string subst(parameters.Text());
            string address(parameters.Text());

            message->Parameters().Implementation<IWebServer>()->AddProxy(path, subst, address);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void RemoveProxy(const string& path) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string path(parameters.Text());

            message->Parameters().Implementation<IWebServer>()->RemoveProxy(path);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual string Accessor() const = 0;
            //
            string accessorUrl = message->Parameters().Implementation<IWebServer>()->Accessor();
            RPC::Data::Frame::Writer output(message->Response().Writer());
            output.Text(accessorUrl);
        },
        nullptr
    };
    // IWebServer interface stub definitions

    //
    // IRtspClient interface stub definitions (interface/IRtspClient.h)
    //
    ProxyStub::MethodHandler RtspClientStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Configure(PluginHost::IShell* framework) = 0;
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IGuide: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            }
            else {
                writer.Number(parameters.Implementation<IRtspClient>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Setup(const string& assetId, uint32_t position)
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string assetId(parameters.Text());
            uint32_t position = parameters.Number<uint32_t>();

            message->Parameters().Implementation<IRtspClient>()->Setup(assetId, position);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Play(int32_t scale, uint32_t position)
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            int32_t  scale    = parameters.Number<int32_t>();
            uint32_t position = parameters.Number<uint32_t>();

            message->Parameters().Implementation<IRtspClient>()->Play(scale, position);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Teardown()
            message->Parameters().Implementation<IRtspClient>()->Teardown();
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual void Set(const string& name, const string& value) = 0;
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string name(parameters.Text());
            string value(parameters.Text());

            message->Parameters().Implementation<IRtspClient>()->Set(name, value);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual string Get(const string& name) const = 0;
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string name(parameters.Text());

            string value = message->Parameters().Implementation<IRtspClient>()->Get(name);
            RPC::Data::Frame::Writer output(message->Response().Writer());
            output.Text(value);
        },
        nullptr
    };
    // IRtspClient interface stub definitions
    ProxyStub::MethodHandler AVNClientStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Configure(PluginHost::IShell* framework) = 0;
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IAVNClient: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            }
            else {
                writer.Number(parameters.Implementation<IAVNClient>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            //virtual void Launch(const string& appURL);
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const string appURL(parameters.Text());
            message->Parameters().Implementation<IAVNClient>()->Launch(appURL);
        },

        nullptr
    };

    ProxyStub::MethodHandler TunerStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            // virtual uint32_t Configure(PluginHost::IShell* framework) = 0;
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IGuide: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            }
            else {
                writer.Number(parameters.Implementation<IStreaming>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IStreaming::INotification* implementation = reader.Number<IStreaming::INotification*>();
            IStreaming::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IStreaming::INotification>(channel, implementation, true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IStreaming::INotification: %p"), implementation);
            }
            else {
                parameters.Implementation<IStreaming>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IStreaming::INotification* stub = reader.Number<IStreaming::INotification*>();
            IStreaming::INotification* proxy = RPC::Administrator::Instance().FindProxy<IStreaming::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find stub for IStreaming::INotification: %p"), stub);
            }
            else {
                parameters.Implementation<IStreaming>()->Unregister(proxy);
            }
        },
       [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void StartScan()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IStreaming>()->StartScan();
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void StoptScan()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IStreaming>()->StopScan();
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void SetCurrentChannel(const uint32_t channelId)
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IStreaming>()->SetCurrentChannel(parameters.Text());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // const string GetCurrentChannel()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IStreaming>()->GetCurrentChannel());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // bool IsScanning()
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Boolean(message->Parameters().Implementation<IStreaming>()->IsScanning());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void Test(const string& str) = 0;
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IStreaming>()->Test(parameters.Text());
        },
        nullptr
    };

    ProxyStub::MethodHandler GuideNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void EITBroadcast()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IGuide::INotification>()->EITBroadcast();
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void EmergencyAlert()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IGuide::INotification>()->EmergencyAlert();
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void ParentalControlChanged()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            message->Parameters().Implementation<IGuide::INotification>()->ParentalControlChanged();
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void ParentalLockChanged()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string lcn(parameters.Text());
            message->Parameters().Implementation<IGuide::INotification>()->ParentalLockChanged(lcn);
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void TestNotification(const string& msg)
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string data(parameters.Text());
            message->Parameters().Implementation<IGuide::INotification>()->TestNotification(data);
        },
        nullptr
    };
    ProxyStub::MethodHandler TunerNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void ScanningStateChanged()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const uint32_t state(parameters.Number<uint32_t>());
            message->Parameters().Implementation<IStreaming::INotification>()->ScanningStateChanged(state);
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void CurrentChannelChanged()
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string lcn(parameters.Text());
            message->Parameters().Implementation<IStreaming::INotification>()->CurrentChannelChanged(lcn);
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            // void TestNotification(const std::string &msg)
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            string data(parameters.Text());
            message->Parameters().Implementation<IStreaming::INotification>()->TestNotification(data);
        },
        nullptr
    };

    ProxyStub::MethodHandler StreamStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual StreamType Type() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Number(message->Parameters().Implementation<IStream>()->Type());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual DRMType DRM() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number(message->Parameters().Implementation<IStream>()->DRM());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual IControl* Control() = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<IStream::IControl*>(message->Parameters().Implementation<IStream>()->Control());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual void Callback(IStream::ICallback* callback) = 0;
             //
             RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
             IStream::ICallback* implementation = parameters.Number<IStream::ICallback*>();
             IStream::ICallback* proxy = nullptr;

             if (implementation != nullptr) {
                 proxy = RPC::Administrator::Instance().CreateProxy<IStream::ICallback>(channel,
                     implementation,
                     true, false);

                 ASSERT((proxy != nullptr) && "Failed to create proxy");
             }
             RPC::Data::Frame::Writer response(message->Response().Writer());
             message->Parameters().Implementation<IStream>()->Callback(proxy);
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual State State() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number(message->Parameters().Implementation<IStream>()->State());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint32_t Load(std::string configuration) const = 0;
             //
             RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
             string configuration(parameters.Text());
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint32_t>(message->Parameters().Implementation<IStream>()->Load(configuration));
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual string Metadata() const = 0;
            //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Text(message->Parameters().Implementation<IStream>()->Metadata());
         },
         nullptr
    };

    ProxyStub::MethodHandler StreamCallbackStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void DRM(uint32_t state) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            uint32_t state(parameters.Number<uint32_t>());
            message->Parameters().Implementation<IStream::ICallback>()->DRM(state);
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void StateChange(IStream::state state) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            IStream::state state(parameters.Number<IStream::state>());
            message->Parameters().Implementation<IStream::ICallback>()->StateChange(state);
         },
         nullptr
    };

    ProxyStub::MethodHandler StreamControlStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Speed(int32_t request) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const int32_t request(parameters.Number<int32_t>());
            message->Parameters().Implementation<IStream::IControl>()->Speed(request);
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual int32_t Speed() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<int32_t>(message->Parameters().Implementation<IStream::IControl>()->Speed());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual void Position(uint64_t absoluteTime) = 0;
             //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const uint64_t absoluteTime(parameters.Number<uint64_t>());
            message->Parameters().Implementation<IStream::IControl>()->Position(absoluteTime);
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint64_t Position() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint64_t>(message->Parameters().Implementation<IStream::IControl>()->Position());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual void TimeRange(uint64_t& begin, uint64_t& end) const = 0;
             //
            RPC::Data::Frame::Writer response(message->Response().Writer());
            uint64_t begin = 0; /* If it would be in->out, you need to read them from the package and fill */
            uint64_t end = 0;   /* them in here, but these are just out values. */
            message->Parameters().Implementation<IStream::IControl>()->TimeRange(begin, end);
            response.Number<uint64_t>(begin);
            response.Number<uint64_t>(end);
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual IGeometry* Geometry() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<IStream::IControl::IGeometry*>(message->Parameters().Implementation<IStream::IControl>()->Geometry());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual void Geometry(const IGeometry* settings) = 0;
             //
             RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
             IStream::IControl::IGeometry* implementation = parameters.Number<IStream::IControl::IGeometry*>();
             IStream::IControl::IGeometry* proxy = nullptr;

             if (implementation != nullptr) {
                 proxy = RPC::Administrator::Instance().CreateProxy<IStream::IControl::IGeometry>(channel,
                     implementation,
                     true, false);

                 ASSERT((proxy != nullptr) && "Failed to create proxy");
             }
             RPC::Data::Frame::Writer response(message->Response().Writer());
             message->Parameters().Implementation<IStream::IControl>()->Geometry(proxy);
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual void Callback(IStream::IControl ICallback* callback) = 0;
             //
             RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
             IStream::IControl::ICallback* implementation = parameters.Number<IStream::IControl::ICallback*>();
             IStream::IControl::ICallback* proxy = nullptr;

             if (implementation != nullptr) {
                 proxy = RPC::Administrator::Instance().CreateProxy<IStream::IControl::ICallback>(channel,
                     implementation,
                     true, false);

                 ASSERT((proxy != nullptr) && "Failed to create proxy");
             }
             RPC::Data::Frame::Writer response(message->Response().Writer());
             message->Parameters().Implementation<IStream::IControl>()->Callback(proxy);
         },
         nullptr
    };

    ProxyStub::MethodHandler StreamControlGeometryStubMethods[] = {
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint32_t X() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint32_t>(message->Parameters().Implementation<IStream::IControl::IGeometry>()->X());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint32_t Y() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint32_t>(message->Parameters().Implementation<IStream::IControl::IGeometry>()->Y());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint32_t Z() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint32_t>(message->Parameters().Implementation<IStream::IControl::IGeometry>()->Z());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint32_t Width() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint32_t>(message->Parameters().Implementation<IStream::IControl::IGeometry>()->Width());
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
             //
             // virtual uint32_t Height() const = 0;
             //
             RPC::Data::Frame::Writer response(message->Response().Writer());
             response.Number<uint32_t>(message->Parameters().Implementation<IStream::IControl::IGeometry>()->Height());
         },
         nullptr
    };

    ProxyStub::MethodHandler StreamControlCallbackStubMethods[] = {
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void TimeUpdate(uint64_t position) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            uint64_t position(parameters.Number<uint64_t>());
            message->Parameters().Implementation<IStream::IControl::ICallback>()->TimeUpdate(position);
         },
         nullptr
    };

    ProxyStub::MethodHandler PlayerStubMethods[] = {
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual IStream* CreateStream(IStream::StreamType streamType) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            RPC::Data::Frame::Writer response(message->Response().Writer());

            IStream::streamtype streamType(parameters.Number<IStream::streamtype>());

            response.Number<IStream*>(message->Parameters().Implementation<IPlayer>()->CreateStream(streamType));
         },
         [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Configure(PluginHost::IShell* service) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer writer(message->Response().Writer());

            PluginHost::IShell* implementation = reader.Number<PluginHost::IShell*>();
            PluginHost::IShell* proxy = RPC::Administrator::Instance().CreateProxy<PluginHost::IShell>(channel, implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for WPEPlayer: %p"), implementation);
                writer.Number<uint32_t>(Core::ERROR_RPC_CALL_FAILED);
            } else {
                writer.Number(parameters.Implementation<IPlayer>()->Configure(proxy));
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
         nullptr
    };

    //
    // IRPCLink interface stub definitions (interface/IRPCLink.h)
    //
    ProxyStub::MethodHandler RPCLinkStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Register(INotification* notification) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IRPCLink::INotification* implementation = reader.Number<IRPCLink::INotification*>();
            IRPCLink::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IRPCLink::INotification>(channel,
                implementation,
                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IRPCLink::INotification: %p"), implementation);
            } else {
                parameters.Implementation<IRPCLink>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Unregister(INotification* notification) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            // Need to find the proxy that goes with the given implementation..
            IRPCLink::INotification* stub = reader.Number<IRPCLink::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            IRPCLink::INotification* proxy = RPC::Administrator::Instance().FindProxy<IRPCLink::INotification>(channel.operator->(), stub);

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find a stub for IRPCLink::INotification: %p"), stub);
            } else {
                parameters.Implementation<IRPCLink>()->Unregister(proxy);
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Start(const uint32_t id, const string& name) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer output(message->Response().Writer());
            const uint32_t id(reader.Number<uint32_t>());
            const string name(reader.Text());

            output.Number<uint32_t>(parameters.Implementation<IRPCLink>()->Start(id, name));
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t Stop() = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer output(message->Response().Writer());

            output.Number<uint32_t>(parameters.Implementation<IRPCLink>()->Stop());
        },
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual uint32_t ForceCallback() = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());
            RPC::Data::Frame::Writer output(message->Response().Writer());

            output.Number<uint32_t>(parameters.Implementation<IRPCLink>()->ForceCallback());
        },
        nullptr
    };
    // IRPCLink interface stub definitions

    //
    // IRPCLink::INotification interface stub definitions (interface/IRPCLink.h)
    //
    ProxyStub::MethodHandler RPCLinkNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Completed(const uint32_t id, const string& name) = 0;
            //
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const uint32_t id(parameters.Number<uint32_t>());
            const string name(parameters.Text());

            message->Parameters().Implementation<IRPCLink::INotification>()->Completed(id, name);
        },

        nullptr
    };
    ProxyStub::MethodHandler PlayGigaStubMethods[] = {
       [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            //virtual void Launch(const string& game, const string& token);
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const string game(parameters.Text());
            const string token(parameters.Text());
            message->Parameters().Implementation<IPlayGiga>()->Launch(game, token);
        },

        nullptr
    };
    ProxyStub::MethodHandler PowerStubMethods[] = {
       [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            //virtual PCStatus SetState(const State state, uint32_t timeout);
            RPC::Data::Frame::Writer response(message->Response().Writer());
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            response.Number(message->Parameters().Implementation<IPower>()->SetState(parameters.Number<IPower::PCState>(), parameters.Number<uint32_t>()));
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            //virtual State GetState();
            RPC::Data::Frame::Writer response(message->Response().Writer());
            response.Number(message->Parameters().Implementation<IPower>()->GetState());
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            //virtual void PowerKey();
            message->Parameters().Implementation<IPower>()->PowerKey();
        },
        [](Core::ProxyType<Core::IPCChannel>&, Core::ProxyType<RPC::InvokeMessage>& message) {
            //virtual void Configure(const string& settings);
            RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
            const string settings(parameters.Text());
            message->Parameters().Implementation<IPower>()->Configure(settings);
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Register(IPower::INotification* sink) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            IPower::INotification* implementation = reader.Number<IPower::INotification*>();
            IPower::INotification* proxy = RPC::Administrator::Instance().CreateProxy<IPower::INotification>(channel,
                                                                                                                implementation,
                                                                                                                true, false);

            ASSERT((proxy != nullptr) && "Failed to create proxy");

            if (proxy == nullptr) {
                TRACE_L1(_T("Could not create a stub for IPowerNotification: %p"), implementation);
            } else {
                parameters.Implementation<IPower>()->Register(proxy);
                if (proxy->Release() != Core::ERROR_NONE) {
                    TRACE_L1("Oops seems like we did not maintain a reference to this sink. %d", __LINE__);
                }
            }
        },
        [](Core::ProxyType<Core::IPCChannel>& channel, Core::ProxyType<RPC::InvokeMessage>& message) {
            //
            // virtual void Unregister(IPower::INotification* sink) = 0;
            //
            RPC::Data::Input& parameters(message->Parameters());
            RPC::Data::Frame::Reader reader(parameters.Reader());

            // Need to find the proxy that goes with the given implementation..
            IPower::INotification* stub = reader.Number<IPower::INotification*>();

            // NOTE: FindProxy does *NOT* AddRef the result. Do not release what is obtained via FindProxy..
            IPower::INotification* proxy = RPC::Administrator::Instance().FindProxy<IPower::INotification>(channel.operator->(), stub);


            if (proxy == nullptr) {
                TRACE_L1(_T("Could not find stub for IBrowserNotification: %p"), stub);
            } else {
                 parameters.Implementation<IPower>()->Unregister(proxy);
           }
        },
        nullptr
    };

    //
    // IPower::INotification interface stub definitions (interface/IPower.h)
    //
    ProxyStub::MethodHandler PowerNotificationStubMethods[] = {
        [](Core::ProxyType<Core::IPCChannel>& channel VARIABLE_IS_NOT_USED, Core::ProxyType<RPC::InvokeMessage>& message) {
           //
           // virtual void StateChange(const IPower::PCState) = 0;
           //
           RPC::Data::Frame::Reader parameters(message->Parameters().Reader());
           IPower::PCState state(parameters.Number<IPower::PCState >());
           message->Parameters().Implementation<IPower::INotification>()->StateChange(state);
        },
        nullptr
    };


    // IRPCLink::INotification interface stub definitions

    typedef ProxyStub::StubType<IBrowser, BrowserStubMethods, ProxyStub::UnknownStub> BrowserStub;
    typedef ProxyStub::StubType<IBrowser::INotification, BrowserNotificationStubMethods, ProxyStub::UnknownStub> BrowserNotificationStub;
    typedef ProxyStub::StubType<IGuide, GuideStubMethods, ProxyStub::UnknownStub> IGuideStub;
    typedef ProxyStub::StubType<IGuide::INotification, GuideNotificationStubMethods, ProxyStub::UnknownStub> GuideNotificationStub;
    typedef ProxyStub::StubType<IWebDriver, WebDriverStubMethods, ProxyStub::UnknownStub> WebDriverStub;
    typedef ProxyStub::StubType<IContentDecryption, OpenCDMiStubMethods, ProxyStub::UnknownStub> OpenCDMiStub;
    typedef ProxyStub::StubType<IBluetooth, BluetoothStubMethods, ProxyStub::UnknownStub> BluetoothStub;
    typedef ProxyStub::StubType<INetflix, NetflixStubMethods, ProxyStub::UnknownStub> NetflixStub;
    typedef ProxyStub::StubType<INetflix::INotification, NetflixNotificationStubMethods, ProxyStub::UnknownStub> NetflixNotificationStub;
    typedef ProxyStub::StubType<IProvisioning, ProvisioningStubMethods, ProxyStub::UnknownStub> ProvisioningStub;
    typedef ProxyStub::StubType<IProvisioning::INotification, ProvisioningNotificationStubMethods, ProxyStub::UnknownStub> ProvisioningNotificationStub;
    typedef ProxyStub::StubType<IWebServer, WebServerStubMethods, ProxyStub::UnknownStub> WebServerStub;
    typedef ProxyStub::StubType<IComposition, CompositionStubMethods, ProxyStub::UnknownStub> CompositionStub;
    typedef ProxyStub::StubType<IComposition::IClient, CompositionClientStubMethods, ProxyStub::UnknownStub> CompositionClientStub;
    typedef ProxyStub::StubType<IComposition::INotification, CompositionNotificationStubMethods, ProxyStub::UnknownStub> CompositionNotificationStub;
    typedef ProxyStub::StubType<IAVNClient, AVNClientStubMethods, ProxyStub::UnknownStub> AVNClientStub;
    typedef ProxyStub::StubType<IStreaming, TunerStubMethods, ProxyStub::UnknownStub> TunerStub;
    typedef ProxyStub::StubType<IStreaming::INotification, TunerNotificationStubMethods, ProxyStub::UnknownStub> TunerNotificationStub;
    typedef ProxyStub::StubType<IStream, StreamStubMethods, ProxyStub::UnknownStub> StreamStub;
    typedef ProxyStub::StubType<IStream::ICallback, StreamCallbackStubMethods, ProxyStub::UnknownStub> StreamCallbackStub;
    typedef ProxyStub::StubType<IStream::IControl, StreamControlStubMethods, ProxyStub::UnknownStub> StreamControlStub;
    typedef ProxyStub::StubType<IStream::IControl::ICallback, StreamControlCallbackStubMethods, ProxyStub::UnknownStub> StreamControlCallbackStub;
    typedef ProxyStub::StubType<IStream::IControl::IGeometry, StreamControlGeometryStubMethods, ProxyStub::UnknownStub> StreamControlGeometryStub;
    typedef ProxyStub::StubType<IPlayer, PlayerStubMethods, ProxyStub::UnknownStub> PlayerStub;
    typedef ProxyStub::StubType<IRPCLink, RPCLinkStubMethods, ProxyStub::UnknownStub> RPCLinkStub;
    typedef ProxyStub::StubType<IRPCLink::INotification, RPCLinkNotificationStubMethods, ProxyStub::UnknownStub> RPCLinkNotificationStub;
    typedef ProxyStub::StubType<IPlayGiga, PlayGigaStubMethods, ProxyStub::UnknownStub> PlayGigaStub;
    typedef ProxyStub::StubType<IRtspClient, RtspClientStubMethods, ProxyStub::UnknownStub> RtspClientStub;
    typedef ProxyStub::StubType<IPower, PowerStubMethods, ProxyStub::UnknownStub> PowerStub;
    typedef ProxyStub::StubType<IPower::INotification, PowerNotificationStubMethods, ProxyStub::UnknownStub> PowerNotificationStub;
    typedef ProxyStub::StubType<ITestService, TestServiceStubMethods, ProxyStub::UnknownStub> TestServiceStub;

    // -------------------------------------------------------------------------------------------
    // PROXY
    // -------------------------------------------------------------------------------------------
    class BrowserProxy : public ProxyStub::UnknownProxyType<IBrowser> {
    public:
        BrowserProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~BrowserProxy()
        {
        }

    public:
        // Stub order:
        // virtual void SetURL(const string& URL) = 0;
        // virtual string GetURL() const = 0;
        // virtual uint32_t GetFPS() const = 0;
        // virtual void Register(IBrowser::INotification* sink) = 0;
        // virtual void Unregister(IBrowser::INotification* sink) = 0;
        // virtual void Hide(const bool hidden) = 0
        virtual void SetURL(const string& URL)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(URL);
            Invoke(newMessage);
        }

        virtual string GetURL() const
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }

        virtual uint32_t GetFPS() const
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<uint32_t>();
        }

        virtual void Register(IBrowser::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IBrowser::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual void Unregister(IBrowser::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IBrowser::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual void Hide(const bool hide)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Boolean(hide);
            Invoke(newMessage);
        }
    };

    class BrowserNotificationProxy : public ProxyStub::UnknownProxyType<IBrowser::INotification> {
    public:
        BrowserNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~BrowserNotificationProxy()
        {
        }

    public:
        // Stub order:
        // virtual void LoadFinished(const string& URL) = 0;
        // virtual void URLChanged(const string& URL) = 0;
        // virtual void Hidden(const bool hidden) = 0;
        // virtual void Closure() = 0;
        virtual void LoadFinished(const string& URL)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(URL);
            Invoke(newMessage);
        }

        virtual void URLChanged(const string& URL)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(URL);
            Invoke(newMessage);
        }

        virtual void Hidden(const bool hidden)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Boolean(hidden);
            Invoke(newMessage);
        }

        virtual void Closure()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);
        }
    };

    class IGuideProxy : public ProxyStub::UnknownProxyType<IGuide> {
    public:
        IGuideProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~IGuideProxy()
        {
        }

    public:
        virtual uint32_t StartParser(PluginHost::IShell* webbridge)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(webbridge);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual void Register(IGuide::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IGuide::INotification*>(notification);
            Invoke(newMessage);

        }
        virtual void Unregister(IGuide::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IGuide::INotification*>(notification);
            Invoke(newMessage);
        }
        virtual const string GetChannels()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
        virtual const string GetPrograms()
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
        virtual const string GetCurrentProgram(const string& channelNum)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(channelNum);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
        virtual const string GetAudioLanguages(const uint32_t eventId)
        {
            IPCMessage newMessage(BaseClass::Message(6));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(eventId);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
        virtual const string GetSubtitleLanguages(const uint32_t eventId)
        {
            IPCMessage newMessage(BaseClass::Message(7));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(eventId);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
        virtual bool SetParentalControlPin(const string& oldPin, const string& newPin)
        {
            IPCMessage newMessage(BaseClass::Message(8));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(oldPin);
            writer.Text(newPin);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }
        virtual bool SetParentalControl(const string& pin, const bool isLocked)
        {
            IPCMessage newMessage(BaseClass::Message(9));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(pin);
            writer.Boolean(isLocked);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }
        virtual bool IsParentalControlled()
        {
            IPCMessage newMessage(BaseClass::Message(10));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }
        virtual bool SetParentalLock(const string& pin, const bool isLocked, const string& channelNum)
        {
            IPCMessage newMessage(BaseClass::Message(11));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(pin);
            writer.Boolean(isLocked);
            writer.Text(channelNum);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }
        virtual bool IsParentalLocked(const string& channelNum)
        {
            IPCMessage newMessage(BaseClass::Message(12));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(channelNum);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

    };

    class WebDriverProxy : public ProxyStub::UnknownProxyType<IWebDriver> {
    public:
        WebDriverProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~WebDriverProxy()
        {
        }

    public:
        // Stub order:
        // virtual uint32_t Configure(PluginHost::IShell* framework) = 0;
        virtual uint32_t Configure(PluginHost::IShell* webbridge)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(webbridge);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
    };

    class TestServiceProxy : public ProxyStub::UnknownProxyType<ITestService> {
    public:
        TestServiceProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~TestServiceProxy()
        {
        }

    public:
        /* Stub order:
         * virtual uint32_t Malloc(uint32_t size) = 0
         * virtual void Free(void) = 0
         * virtual void Statm(uint32_t &allocated, uint32_t &size, uint32_t &resident) = 0
         * virtual bool Configure(PluginHost::IShell* service) = 0;
         * virtual void Crash() = 0;
         * virtual bool CrashNTimes(uint8_t n) = 0;
         * virtual void ExecPendingCrash() = 0;
         * virtual uint8_t PendingCrashCount() = 0;
         */

        virtual uint32_t Malloc(uint32_t size)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(size);
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual void Free(void)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);
        }

        virtual void Statm(uint32_t &allocated, uint32_t &size, uint32_t &resident)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);
            RPC::Data::Frame::Reader response(newMessage->Response().Reader());
            allocated = response.Number<uint32_t>();
            size = response.Number<uint32_t>();
            resident = response.Number<uint32_t>();
        }

        virtual bool Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<bool>());
        }

        virtual void Crash()
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);
        }

        virtual bool CrashNTimes(uint8_t n)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint8_t>(n);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<bool>());
        }

        virtual void ExecPendingCrash() {
            IPCMessage newMessage(BaseClass::Message(6));
            Invoke(newMessage);
        }

        virtual uint8_t PendingCrashCount()
        {
            IPCMessage newMessage(BaseClass::Message(7));
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint8_t>());
        }
    };

    class OpenCDMiProxy : public ProxyStub::UnknownProxyType<IContentDecryption> {
    public:
        OpenCDMiProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~OpenCDMiProxy()
        {
        }

    public:
        // Stub order:
        // virtual uint32_t Configure(PluginHost::IShell* service) = 0;
        virtual uint32_t Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual uint32_t Reset() {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual RPC::IStringIterator* Systems() const {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (const_cast<OpenCDMiProxy&>(*this).CreateProxy<RPC::IStringIterator>(reader.Number<RPC::IStringIterator*>()));
        }
        virtual RPC::IStringIterator* Designators(const string& keySystem) const {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(keySystem);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (const_cast<OpenCDMiProxy&>(*this).CreateProxy<RPC::IStringIterator>(reader.Number<RPC::IStringIterator*>()));
        }
        virtual RPC::IStringIterator* Sessions(const string& keySystem) const {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(keySystem);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (const_cast<OpenCDMiProxy&>(*this).CreateProxy<RPC::IStringIterator>(reader.Number<RPC::IStringIterator*>()));
        }
    };

    class BluetoothProxy : public ProxyStub::UnknownProxyType<IBluetooth> {
    public:
        BluetoothProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~BluetoothProxy()
        {
        }
    public:
        virtual uint32_t Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual bool Scan()
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

        virtual bool StopScan()
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

        virtual string DiscoveredDevices()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }

        virtual string PairedDevices()
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }

        virtual bool Pair(string deviceId)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(deviceId);
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

        virtual bool Connect(string deviceId)
        {
            IPCMessage newMessage(BaseClass::Message(6));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(deviceId);
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

        virtual bool Disconnect()
        {
            IPCMessage newMessage(BaseClass::Message(7));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

        virtual bool IsScanning()
        {
            IPCMessage newMessage(BaseClass::Message(8));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }

        virtual string Connected()
        {
            IPCMessage newMessage(BaseClass::Message(9));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
    };


    class NetflixProxy : public ProxyStub::UnknownProxyType<INetflix> {
    public:
        NetflixProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~NetflixProxy()
        {
        }

    public:
        // Stub order:
        // virtual void Register(INetflix::INotification* netflix) = 0;
        // virtual void Unregister(INetflix::INotification* netflix) = 0;
        // virtual string GetESN() const = 0;
        // virtual void FactoryReset() = 0;
        // virtual void SystemCommand(const string& command) = 0;
        // virtual void Language(const string& language) = 0;
        virtual void Register(INetflix::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<INetflix::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual void Unregister(INetflix::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<INetflix::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual string GetESN() const
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }

        virtual void FactoryReset()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);
        }

        virtual void SystemCommand(const string& command)
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(command);
            Invoke(newMessage);
        }

        virtual void Language(const string& language)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(language);
            Invoke(newMessage);
        }

        virtual void SetVisible(bool visibility)
        {
            IPCMessage newMessage(BaseClass::Message(6));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Boolean(visibility);
            Invoke(newMessage);
        }
    };

    class NetflixNotificationProxy : public ProxyStub::UnknownProxyType<INetflix::INotification> {
    public:
        NetflixNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~NetflixNotificationProxy()
        {
        }

    public:
        // Stub order:
        // virtual void StateChange(const INetflix::state state) = 0;
        virtual void StateChange(const Exchange::INetflix::state newState)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<Exchange::INetflix::state>(newState);

            Invoke(newMessage);
        }
    };


    class ProvisioningProxy : public ProxyStub::UnknownProxyType<IProvisioning> {
    public:
        ProvisioningProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~ProvisioningProxy()
        {
        }

    public:
        // Stub order:
        // virtual void Register(IProvisioning::INotification* provisioning) = 0;
        // virtual void Unregister(IProvisioning::INotification* provisioning) = 0;
        virtual void Register(IProvisioning::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IProvisioning::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual void Unregister(IProvisioning::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IProvisioning::INotification*>(notification);
            Invoke(newMessage);
        }
    };

    class ProvisioningNotificationProxy : public ProxyStub::UnknownProxyType<IProvisioning::INotification> {
    public:
        ProvisioningNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~ProvisioningNotificationProxy()
        {
        }

    public:
        // Stub order:
        // virtual void Provisioned(const string& component) = 0;
        virtual void Provisioned(const string& element)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(element);
            Invoke(newMessage);
        }
    };

    class CompositionProxy : public ProxyStub::UnknownProxyType<IComposition> {
    public:
        CompositionProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~CompositionProxy()
        {
        }

    public:
        void Register(IComposition::INotification* notification) override
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IComposition::INotification*>(notification);
            Invoke(newMessage);
        }

        void Unregister(IComposition::INotification* notification) override
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IComposition::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual IClient* Client(const uint8_t index) override
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(index);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (CreateProxy<IClient>(reader.Number<IClient*>()));
        }

        IClient* Client(const string& name) override
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(name);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (CreateProxy<IClient>(reader.Number<IClient*>()));
        }

        uint32_t Configure(PluginHost::IShell* service) override
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        void Resolution(const ScreenResolution format) override
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IComposition::ScreenResolution>(format);
            Invoke(newMessage);
        }

        ScreenResolution Resolution() const override
        {
            IPCMessage newMessage(BaseClass::Message(6));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (reader.Number<IComposition::ScreenResolution>());
        }

        uint32_t Geometry(const string& callsign, const IComposition::Rectangle& rectangle) override {
           IPCMessage newMessage(BaseClass::Message(7));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(callsign);
            writer.Number<uint32_t>(rectangle.x);
            writer.Number<uint32_t>(rectangle.y);
            writer.Number<uint32_t>(rectangle.width);
            writer.Number<uint32_t>(rectangle.height);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (reader.Number<uint32_t>());
        }


        virtual IComposition::Rectangle Geometry(const string& callsign) const override {
            IPCMessage newMessage(BaseClass::Message(8));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(callsign);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            IComposition::Rectangle rectangle;
            rectangle.x = reader.Number<uint32_t>();
            rectangle.y = reader.Number<uint32_t>();
            rectangle.width = reader.Number<uint32_t>();
            rectangle.height = reader.Number<uint32_t>();
            return rectangle;
        }

        uint32_t ToTop(const string& callsign) override {
            IPCMessage newMessage(BaseClass::Message(9));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(callsign);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<uint32_t>();
        }

        uint32_t PutBelow(const string& callsignRelativeTo, const string& callsignToReorder) override {
            IPCMessage newMessage(BaseClass::Message(10));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(callsignRelativeTo);
            writer.Text(callsignToReorder);
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<uint32_t>();
        }

        RPC::IStringIterator* ClientsInZorder() const override {
            IPCMessage newMessage(BaseClass::Message(11));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (const_cast<CompositionProxy&>(*this).CreateProxy<RPC::IStringIterator>(reader.Number<RPC::IStringIterator*>()));

        }

    };

    class CompositionClientProxy : public ProxyStub::UnknownProxyType<IComposition::IClient> {
    public:
        CompositionClientProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        ~CompositionClientProxy() override = default;

    public:
        string Name() const override
        {
            IPCMessage newMessage(BaseClass::Message(0));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return (reader.Text());
        }

        void Kill() override
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);
        }

        void Opacity(const uint32_t value) override
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(value);
            Invoke(newMessage);
        }

        void ChangedGeometry(const IComposition::Rectangle& rectangle) override
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(rectangle.x);
            writer.Number<uint32_t>(rectangle.y);
            writer.Number<uint32_t>(rectangle.width);
            writer.Number<uint32_t>(rectangle.height);
            Invoke(newMessage);
        }

        void ChangedZOrder(const uint8_t zorder) override
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint8_t>(zorder);
            Invoke(newMessage);
        }
    };

    class CompositionNotificationProxy : public ProxyStub::UnknownProxyType<IComposition::INotification> {
    public:
        // Stub order:
        CompositionNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~CompositionNotificationProxy()
        {
        }

    public:
        // Stub order:
        // virtual void Attached(IClient* client) = 0;
        // virtual void Detached(IClient* client) = 0;
        virtual void Attached(IComposition::IClient* element)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IComposition::IClient*>(element);
            Invoke(newMessage);
        }

        virtual void Detached(IComposition::IClient* element)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IComposition::IClient*>(element);
            Invoke(newMessage);
        }
    };

    class WebServerProxy : public ProxyStub::UnknownProxyType<IWebServer> {
    public:
        WebServerProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~WebServerProxy()
        {
        }

    public:
        // Stub order:
        // virtual void AddProxy(const string& path, const string& subst, const string& address) = 0;
        // virtual void RemoveProxy(const string& path) = 0;
        // virtual string Accessor() const = 0;
        virtual void AddProxy(const string& path, const string& subst, const string& address)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(path);
            writer.Text(subst);
            writer.Text(address);
            Invoke(newMessage);
        }

        virtual void RemoveProxy(const string& path)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(path);
            Invoke(newMessage);
        }

        virtual string Accessor() const
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            string accessorURL = reader.Text();
            return accessorURL;
        }
    };

    class RtspClientProxy : public ProxyStub::UnknownProxyType<IRtspClient> {
    public:
        RtspClientProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~RtspClientProxy()
        {
        }

    public:
        virtual uint32_t Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual uint32_t Setup(const string& assetId, uint32_t position)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(assetId);
            writer.Number(position);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual uint32_t Play(int32_t scale, uint32_t position)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(scale);
            writer.Number(position);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual uint32_t Teardown()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }


        virtual void Set(const string& name, const string& value)
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(name);
            writer.Text(value);
            Invoke(newMessage);
        }

        virtual string Get(const string& name) const
        {
            IPCMessage newMessage(BaseClass::Message(5));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            string value = reader.Text();
            return value;
        }
    };
    class AVNClientProxy : public ProxyStub::UnknownProxyType<IAVNClient> {
    public:
        AVNClientProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~AVNClientProxy()
        {
        }

    public:
        virtual uint32_t Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual void Launch(const string& appURL)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(appURL);
            Invoke(newMessage);
        }
    };

    class TunerProxy : public ProxyStub::UnknownProxyType<IStreaming> {
    public:
        TunerProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~TunerProxy()
        {
        }

    public:
        virtual uint32_t Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual void Register(IStreaming::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IStreaming::INotification*>(notification);
            Invoke(newMessage);

        }
        virtual void Unregister(IStreaming::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IStreaming::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual void StartScan()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            Invoke(newMessage);
        }
        virtual void StopScan()
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            Invoke(newMessage);
        }
        virtual void SetCurrentChannel(const string& channelId)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(channelId);
            Invoke(newMessage);
        }
        virtual const string GetCurrentChannel()
        {
            IPCMessage newMessage(BaseClass::Message(6));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Text();
        }
        virtual bool IsScanning()
        {
            IPCMessage newMessage(BaseClass::Message(7));
            Invoke(newMessage);
            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Boolean();
        }
        // Add methods above this line - Dont forget to update the id for the test
        virtual void Test(const string& str)
        {
            IPCMessage newMessage(BaseClass::Message(8));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(str);
            Invoke(newMessage);
        }
    };

    class TunerNotificationProxy : public ProxyStub::UnknownProxyType<IStreaming::INotification> {
    public:
        TunerNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~TunerNotificationProxy()
        {
        }

    public:
        virtual void ScanningStateChanged(const uint32_t state)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(state);
            Invoke(newMessage);
        }
        virtual void CurrentChannelChanged(const string& lcn)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(lcn);
            Invoke(newMessage);
        }
        // Add methods above this line- Dont forget to update the id for the TestNotification
        virtual void TestNotification(const string& str)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(str);
            Invoke(newMessage);
        }
    };

    class GuideNotificationProxy : public ProxyStub::UnknownProxyType<IGuide::INotification> {
    public:
        GuideNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~GuideNotificationProxy()
        {
        }
    public:
        virtual void EITBroadcast()
        {
            IPCMessage newMessage(BaseClass::Message(0));
            Invoke(newMessage);
        }
        virtual void EmergencyAlert()
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);
        }
        virtual void ParentalControlChanged()
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);
        }
        virtual void ParentalLockChanged(const string& lcn)
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(lcn);
            Invoke(newMessage);
        }
       // Add methods above this line- Dont forget to update the id for the TestNotification
        virtual void TestNotification(const string& str)
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(str);
            Invoke(newMessage);
        }

    };

   class StreamProxy : public ProxyStub::UnknownProxyType<IStream> {
   public:
        StreamProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~StreamProxy()
        {
        }
   public:
        virtual IStream::streamtype Type() const
        {
            IPCMessage newMessage(BaseClass::Message(0));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<IStream::streamtype>());
        }
        virtual IStream::drmtype DRM() const
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<IStream::drmtype>());
        }
        virtual IStream::IControl* Control()
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (CreateProxy<IStream::IControl>(reader.Number<IStream::IControl*>()));
        }
        virtual void Callback(IStream::ICallback* callback)
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(callback);
            Invoke(newMessage);
        }
        virtual IStream::state State() const
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<IStream::state>());
        }
        virtual uint32_t Load(std::string configuration)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(configuration);
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual string Metadata() const
        {
            IPCMessage newMessage(BaseClass::Message(6));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Text());
        }
   };

   class StreamCallbackProxy : public ProxyStub::UnknownProxyType<IStream::ICallback> {
   public:
        StreamCallbackProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~StreamCallbackProxy()
        {
        }
   public:
        virtual void DRM(uint32_t state)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(state);
            Invoke(newMessage);
        }
        virtual void StateChange(IStream::state state)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IStream::state>(state);
            Invoke(newMessage);
        }
   };

   class StreamControlProxy : public ProxyStub::UnknownProxyType<IStream::IControl> {
   public:
        StreamControlProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~StreamControlProxy()
        {
        }
   public:
        virtual void Speed(int32_t request)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<int32_t>(request);
            Invoke(newMessage);
        }
        virtual int32_t Speed() const
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<int32_t>());
        }
        virtual void Position(uint64_t absoluteTime)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint64_t>(absoluteTime);
            Invoke(newMessage);
        }
        virtual uint64_t Position() const
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint64_t>());
        }
        virtual void TimeRange(uint64_t& begin, uint64_t& end) const
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);
            RPC::Data::Frame::Reader response(newMessage->Response().Reader());
            begin = response.Number<uint64_t>();
            end = response.Number<uint64_t>();
        }
        virtual IStream::IControl::IGeometry* Geometry() const
        {
            IPCMessage newMessage(BaseClass::Message(5));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (const_cast<StreamControlProxy&>(*this).CreateProxy<IStream::IControl::IGeometry>(reader.Number<IStream::IControl::IGeometry*>()));
        }
        virtual void Geometry(const IStream::IControl::IGeometry* settings)
        {
            IPCMessage newMessage(BaseClass::Message(6));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(settings);
            Invoke(newMessage);
        }

        virtual void Callback(IStream::IControl::ICallback* callback)
        {
            IPCMessage newMessage(BaseClass::Message(7));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number(callback);
            Invoke(newMessage);
        }
   };

   class StreamControlGeometryProxy : public ProxyStub::UnknownProxyType<IStream::IControl::IGeometry> {
   public:
        StreamControlGeometryProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~StreamControlGeometryProxy()
        {
        }
   public:
        virtual uint32_t X() const
        {
            IPCMessage newMessage(BaseClass::Message(0));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual uint32_t Y() const
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual uint32_t Z() const
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual uint32_t Width() const
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
        virtual uint32_t Height() const
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
   };

   class StreamControlCallbackProxy : public ProxyStub::UnknownProxyType<IStream::IControl::ICallback> {
   public:
        StreamControlCallbackProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~StreamControlCallbackProxy()
        {
        }
   public:
        virtual void TimeUpdate(uint64_t position)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint64_t>(position);
            Invoke(newMessage);
        }
   };

   class PlayerProxy : public ProxyStub::UnknownProxyType<IPlayer> {
   public:
        PlayerProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }
        virtual ~PlayerProxy()
        {
        }
   public:
        virtual IStream* CreateStream(IStream::streamtype streamType)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IStream::streamtype>(streamType);
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());

            return (CreateProxy<IStream>(reader.Number<IStream*>()));
        }
        virtual uint32_t Configure(PluginHost::IShell* service)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<PluginHost::IShell*>(service);
            Invoke(newMessage);
            return (newMessage->Response().Reader().Number<uint32_t>());
        }
   };

   class RPCLinkProxy : public ProxyStub::UnknownProxyType<IRPCLink> {
   public:
        RPCLinkProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~RPCLinkProxy()
        {
        }

    public:
        // Stub order:
        // virtual void Register(INotification* notification) = 0;
        // virtual void Unregister(INotification* notification) = 0;
        // virtual uint32_t Start(const uint32_t id, const string& name) = 0;
        // virtual uint32_t Stop() = 0;
        // virtual uint32_t ForceCallback() = 0;
        virtual void Register(IRPCLink::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IRPCLink::INotification*>(notification);
            Invoke(newMessage);
         }

        virtual void Unregister(IRPCLink::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(1));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IRPCLink::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual uint32_t Start(const uint32_t id, const string& name)
        {
            IPCMessage newMessage(BaseClass::Message(2));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(id);
            writer.Text(name);
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual uint32_t Stop()
        {
            IPCMessage newMessage(BaseClass::Message(3));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }

        virtual uint32_t ForceCallback()
        {
            IPCMessage newMessage(BaseClass::Message(4));
            Invoke(newMessage);

            return (newMessage->Response().Reader().Number<uint32_t>());
        }
    };

    class RPCLinkNotificationProxy : public ProxyStub::UnknownProxyType<IRPCLink::INotification> {
    public:
        RPCLinkNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
            const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~RPCLinkNotificationProxy()
        {
        }

    public:
        // Stub order:
        // virtual void Completed(const uint32_t id, const string& name) = 0;
        virtual void Completed(const uint32_t id, const string& name)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<uint32_t>(id);
            writer.Text(name);
            Invoke(newMessage);
        }
    };

    class PlayGigaProxy : public ProxyStub::UnknownProxyType<IPlayGiga> {
    public:
        PlayGigaProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~PlayGigaProxy()
        {
        }

    public:
        virtual void Launch(const string& game, const string& token)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(game);
            writer.Text(token);
            Invoke(newMessage);
        }
    };

    class PowerProxy : public ProxyStub::UnknownProxyType<IPower> {
    public:
        PowerProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation, const bool otherSideInformed)
            : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~PowerProxy()
        {
        }

    public:
        virtual PCStatus SetState(const PCState state, const uint32_t timeout)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IPower::PCState>(state);
            writer.Number(timeout);
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<IPower::PCStatus>();
        }

        virtual PCState GetState() const
        {
            IPCMessage newMessage(BaseClass::Message(1));
            Invoke(newMessage);

            RPC::Data::Frame::Reader reader(newMessage->Response().Reader());
            return reader.Number<IPower::PCState>();
        }

        virtual void PowerKey()
        {
            IPCMessage newMessage(BaseClass::Message(2));
            Invoke(newMessage);
        }

        virtual void Configure(const string& settings)
        {
            IPCMessage newMessage(BaseClass::Message(3));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Text(settings);
            Invoke(newMessage);
        }

        virtual void Register(IPower::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(4));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IPower::INotification*>(notification);
            Invoke(newMessage);
        }

        virtual void Unregister(IPower::INotification* notification)
        {
            IPCMessage newMessage(BaseClass::Message(5));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IPower::INotification*>(notification);
            Invoke(newMessage);
        }

    };

    class PowerNotificationProxy : public ProxyStub::UnknownProxyType<IPower::INotification> {
    public:
        PowerNotificationProxy(Core::ProxyType<Core::IPCChannel>& channel, void* implementation,
                                 const bool otherSideInformed)
                : BaseClass(channel, implementation, otherSideInformed)
        {
        }

        virtual ~PowerNotificationProxy()
        {
        }

    public:
        // Stub order:
        // virtual void StateChange(const IPower::PCState) = 0;
        virtual void StateChange(const IPower::PCState state)
        {
            IPCMessage newMessage(BaseClass::Message(0));
            RPC::Data::Frame::Writer writer(newMessage->Parameters().Writer());
            writer.Number<IPower::PCState>(state);
            Invoke(newMessage);
        }
    };

    // -------------------------------------------------------------------------------------------
    // Registration
    // -------------------------------------------------------------------------------------------
    static class Instantiation {
    public:
        Instantiation()
        {
            RPC::Administrator::Instance().Announce<IBrowser, BrowserProxy, BrowserStub>();
            RPC::Administrator::Instance().Announce<IBrowser::INotification, BrowserNotificationProxy, BrowserNotificationStub>();
            RPC::Administrator::Instance().Announce<IGuide, IGuideProxy, IGuideStub>();
            RPC::Administrator::Instance().Announce<IGuide::INotification, GuideNotificationProxy, GuideNotificationStub>();
            RPC::Administrator::Instance().Announce<IWebDriver, WebDriverProxy, WebDriverStub>();
            RPC::Administrator::Instance().Announce<IContentDecryption, OpenCDMiProxy, OpenCDMiStub>();
            RPC::Administrator::Instance().Announce<IBluetooth, BluetoothProxy, BluetoothStub>();
            RPC::Administrator::Instance().Announce<INetflix, NetflixProxy, NetflixStub>();
            RPC::Administrator::Instance().Announce<INetflix::INotification, NetflixNotificationProxy, NetflixNotificationStub>();
            RPC::Administrator::Instance().Announce<IProvisioning, ProvisioningProxy, ProvisioningStub>();
            RPC::Administrator::Instance().Announce<IProvisioning::INotification, ProvisioningNotificationProxy, ProvisioningNotificationStub>();
            RPC::Administrator::Instance().Announce<IWebServer, WebServerProxy, WebServerStub>();
            RPC::Administrator::Instance().Announce<IComposition, CompositionProxy, CompositionStub>();
            RPC::Administrator::Instance().Announce<IComposition::IClient, CompositionClientProxy, CompositionClientStub>();
            RPC::Administrator::Instance().Announce<IComposition::INotification, CompositionNotificationProxy, CompositionNotificationStub>();
            RPC::Administrator::Instance().Announce<IAVNClient, AVNClientProxy, AVNClientStub>();
            RPC::Administrator::Instance().Announce<IStreaming, TunerProxy, TunerStub>();
            RPC::Administrator::Instance().Announce<IStreaming::INotification, TunerNotificationProxy, TunerNotificationStub>();
            RPC::Administrator::Instance().Announce<IStream, StreamProxy, StreamStub>();
            RPC::Administrator::Instance().Announce<IStream::ICallback, StreamCallbackProxy, StreamCallbackStub>();
            RPC::Administrator::Instance().Announce<IStream::IControl, StreamControlProxy, StreamControlStub>();
            RPC::Administrator::Instance().Announce<IStream::IControl::ICallback, StreamControlCallbackProxy, StreamControlCallbackStub>();
            RPC::Administrator::Instance().Announce<IStream::IControl::IGeometry, StreamControlGeometryProxy, StreamControlGeometryStub>();
            RPC::Administrator::Instance().Announce<IPlayer, PlayerProxy, PlayerStub>();
            RPC::Administrator::Instance().Announce<IRPCLink, RPCLinkProxy, RPCLinkStub>();
            RPC::Administrator::Instance().Announce<IRPCLink::INotification, RPCLinkNotificationProxy, RPCLinkNotificationStub>();
            RPC::Administrator::Instance().Announce<IPlayGiga, PlayGigaProxy, PlayGigaStub>();
            RPC::Administrator::Instance().Announce<IPower, PowerProxy, PowerStub>();
            RPC::Administrator::Instance().Announce<IPower::INotification, PowerNotificationProxy, PowerNotificationStub>();
            RPC::Administrator::Instance().Announce<IRtspClient, RtspClientProxy, RtspClientStub>();
            RPC::Administrator::Instance().Announce<ITestService, TestServiceProxy, TestServiceStub>();
        }

        ~Instantiation()
        {
        }

    } ProxyStubRegistration;
} // namespace ProxyStubs
} // namespace WPEFramework
