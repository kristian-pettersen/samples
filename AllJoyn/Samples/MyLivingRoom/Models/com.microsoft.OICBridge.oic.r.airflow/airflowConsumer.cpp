//-----------------------------------------------------------------------------
// <auto-generated> 
//   This code was generated by a tool. 
// 
//   Changes to this file may cause incorrect behavior and will be lost if  
//   the code is regenerated.
//
//   Tool: AllJoynCodeGenerator.exe
//
//   This tool is located in the Windows 10 SDK and the Windows 10 AllJoyn 
//   Visual Studio Extension in the Visual Studio Gallery.  
//
//   The generated code should be packaged in a Windows 10 C++/CX Runtime  
//   Component which can be consumed in any UWP-supported language using 
//   APIs that are available in Windows.Devices.AllJoyn.
//
//   Using AllJoynCodeGenerator - Invoke the following command with a valid 
//   Introspection XML file and a writable output directory:
//     AllJoynCodeGenerator -i <INPUT XML FILE> -o <OUTPUT DIRECTORY>
// </auto-generated>
//-----------------------------------------------------------------------------
#include "pch.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Devices::AllJoyn;
using namespace com::microsoft::OICBridge::oic::r::airflow;

std::map<alljoyn_interfacedescription, WeakReference*> airflowConsumer::SourceInterfaces;

airflowConsumer::airflowConsumer(AllJoynBusAttachment^ busAttachment)
    : m_busAttachment(busAttachment),
    m_proxyBusObject(nullptr),
    m_busObject(nullptr),
    m_sessionListener(nullptr),
    m_sessionId(0)
{
    m_weak = new WeakReference(this);
    m_signals = ref new airflowSignals();
    m_nativeBusAttachment = AllJoynHelpers::GetInternalBusAttachment(m_busAttachment);
}

airflowConsumer::~airflowConsumer()
{
    AllJoynBusObjectManager::ReleaseBusObject(m_nativeBusAttachment, AllJoynHelpers::PlatformToMultibyteString(ServiceObjectPath).data());
    if (SessionListener != nullptr)
    {
        alljoyn_busattachment_setsessionlistener(m_nativeBusAttachment, m_sessionId, nullptr);
        alljoyn_sessionlistener_destroy(SessionListener);
    }
    if (nullptr != ProxyBusObject)
    {
        alljoyn_proxybusobject_destroy(ProxyBusObject);
    }
    delete m_weak;
}

void airflowConsumer::OnSessionLost(_In_ alljoyn_sessionid sessionId, _In_ alljoyn_sessionlostreason reason)
{
    if (sessionId == m_sessionId)
    {
        AllJoynSessionLostEventArgs^ args = ref new AllJoynSessionLostEventArgs(static_cast<AllJoynSessionLostReason>(reason));
        SessionLost(this, args);
    }
}

void airflowConsumer::OnSessionMemberAdded(_In_ alljoyn_sessionid sessionId, _In_ PCSTR uniqueName)
{
    if (sessionId == m_sessionId)
    {
        auto args = ref new AllJoynSessionMemberAddedEventArgs(AllJoynHelpers::MultibyteToPlatformString(uniqueName));
        SessionMemberAdded(this, args);
    }
}

void airflowConsumer::OnSessionMemberRemoved(_In_ alljoyn_sessionid sessionId, _In_ PCSTR uniqueName)
{
    if (sessionId == m_sessionId)
    {
        auto args = ref new AllJoynSessionMemberRemovedEventArgs(AllJoynHelpers::MultibyteToPlatformString(uniqueName));
        SessionMemberRemoved(this, args);
    }
}

QStatus airflowConsumer::AddSignalHandler(_In_ alljoyn_busattachment busAttachment, _In_ alljoyn_interfacedescription interfaceDescription, _In_ PCSTR methodName, _In_ alljoyn_messagereceiver_signalhandler_ptr handler)
{
    alljoyn_interfacedescription_member member;
    if (!alljoyn_interfacedescription_getmember(interfaceDescription, methodName, &member))
    {
        return ER_BUS_INTERFACE_NO_SUCH_MEMBER;
    }

    return alljoyn_busattachment_registersignalhandler(busAttachment, handler, member, NULL);
}

IAsyncOperation<airflowJoinSessionResult^>^ airflowConsumer::JoinSessionAsync(
    _In_ AllJoynServiceInfo^ serviceInfo, _Inout_ airflowWatcher^ watcher)
{
    return create_async([serviceInfo, watcher]() -> airflowJoinSessionResult^
    {
        auto result = ref new airflowJoinSessionResult();
        result->Status = AllJoynStatus::Ok;
        result->Consumer = nullptr;

        result->Consumer = ref new airflowConsumer(watcher->BusAttachment);
        result->Status = result->Consumer->JoinSession(serviceInfo, watcher->BusObjectInterfaceName);

        return result;
    });
}


IAsyncOperation<airflowSetDirectionResult^>^ airflowConsumer::SetDirectionAsync(_In_ Platform::String^ value)
{
    return create_async([this, value]() -> airflowSetDirectionResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "s", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            m_objectInterface.c_str(),
            "Direction",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new airflowSetDirectionResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<airflowGetDirectionResult^>^ airflowConsumer::GetDirectionAsync()
{
    return create_async([this]() -> airflowGetDirectionResult^
    {
        PropertyGetContext<Platform::String^> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            m_objectInterface.c_str(),
            "Direction",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<Platform::String^>*>(context);

                if (ER_OK == status)
                {
                    Platform::String^ argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "s", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new airflowGetDirectionResult();
        result->Status = getContext.GetStatus();
        result->Direction = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<airflowSetRangeResult^>^ airflowConsumer::SetRangeAsync(_In_ Platform::String^ value)
{
    return create_async([this, value]() -> airflowSetRangeResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "s", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            m_objectInterface.c_str(),
            "Range",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new airflowSetRangeResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<airflowGetRangeResult^>^ airflowConsumer::GetRangeAsync()
{
    return create_async([this]() -> airflowGetRangeResult^
    {
        PropertyGetContext<Platform::String^> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            m_objectInterface.c_str(),
            "Range",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<Platform::String^>*>(context);

                if (ER_OK == status)
                {
                    Platform::String^ argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "s", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new airflowGetRangeResult();
        result->Status = getContext.GetStatus();
        result->Range = getContext.GetValue();
        return result;
    });
}

IAsyncOperation<airflowSetSpeedResult^>^ airflowConsumer::SetSpeedAsync(_In_ int64 value)
{
    return create_async([this, value]() -> airflowSetSpeedResult^
    {
        PropertySetContext setContext;

        alljoyn_msgarg inputArgument = alljoyn_msgarg_create();
        TypeConversionHelpers::SetAllJoynMessageArg(inputArgument, "x", value);

        alljoyn_proxybusobject_setpropertyasync(
            ProxyBusObject,
            m_objectInterface.c_str(),
            "Speed",
            inputArgument,
            [](QStatus status, alljoyn_proxybusobject obj, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertySetContext*>(context);
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &setContext);

        alljoyn_msgarg_destroy(inputArgument);

        setContext.Wait();

        auto result = ref new airflowSetSpeedResult();
        result->Status = setContext.GetStatus();
        return result;
    });
}

IAsyncOperation<airflowGetSpeedResult^>^ airflowConsumer::GetSpeedAsync()
{
    return create_async([this]() -> airflowGetSpeedResult^
    {
        PropertyGetContext<int64> getContext;
        
        alljoyn_proxybusobject_getpropertyasync(
            ProxyBusObject,
            m_objectInterface.c_str(),
            "Speed",
            [](QStatus status, alljoyn_proxybusobject obj, const alljoyn_msgarg value, void* context)
            {
                UNREFERENCED_PARAMETER(obj);
                auto propertyContext = static_cast<PropertyGetContext<int64>*>(context);

                if (ER_OK == status)
                {
                    int64 argument;
                    TypeConversionHelpers::GetAllJoynMessageArg(value, "x", &argument);

                    propertyContext->SetValue(argument);
                }
                propertyContext->SetStatus(status);
                propertyContext->SetEvent();
            },
            c_MessageTimeoutInMilliseconds,
            &getContext);

        getContext.Wait();

        auto result = ref new airflowGetSpeedResult();
        result->Status = getContext.GetStatus();
        result->Speed = getContext.GetValue();
        return result;
    });
}

void airflowConsumer::OnPropertyChanged(_In_ alljoyn_proxybusobject obj, _In_ PCSTR interfaceName, _In_ const alljoyn_msgarg changed, _In_ const alljoyn_msgarg invalidated)
{
    UNREFERENCED_PARAMETER(obj);
    UNREFERENCED_PARAMETER(interfaceName);
    UNREFERENCED_PARAMETER(invalidated);

    alljoyn_msgarg changedProperties;
    size_t changedPropertyCount;
    if (ER_OK != alljoyn_msgarg_get(changed, "a{sv}", &changedPropertyCount, &changedProperties))
    {
        return;
    }

    for (size_t i = 0; i < changedPropertyCount; i++)
    {
        char* propertyName;
        alljoyn_msgarg propertyValue;
        if (ER_OK != alljoyn_msgarg_get(alljoyn_msgarg_array_element(changedProperties, i), "{sv}", &propertyName, &propertyValue))
        {
            return;
        }

        if (strcmp("Direction", propertyName) == 0)
        {
            DirectionChanged(this, nullptr);
        }
        if (strcmp("Range", propertyName) == 0)
        {
            RangeChanged(this, nullptr);
        }
        if (strcmp("Speed", propertyName) == 0)
        {
            SpeedChanged(this, nullptr);
        }
    }
}

int32 airflowConsumer::JoinSession(_In_ AllJoynServiceInfo^ serviceInfo, const std::string& ifName)
{
    alljoyn_sessionlistener_callbacks callbacks =
    {
        AllJoynHelpers::SessionLostHandler<airflowConsumer>,
        AllJoynHelpers::SessionMemberAddedHandler<airflowConsumer>,
        AllJoynHelpers::SessionMemberRemovedHandler<airflowConsumer>
    };

    alljoyn_busattachment_enableconcurrentcallbacks(AllJoynHelpers::GetInternalBusAttachment(m_busAttachment));

    SessionListener = alljoyn_sessionlistener_create(&callbacks, m_weak);
    alljoyn_sessionopts sessionOpts = alljoyn_sessionopts_create(ALLJOYN_TRAFFIC_TYPE_MESSAGES, true, ALLJOYN_PROXIMITY_ANY, ALLJOYN_TRANSPORT_ANY);

    std::vector<char> sessionNameUtf8 = AllJoynHelpers::PlatformToMultibyteString(serviceInfo->UniqueName);
    auto status = alljoyn_busattachment_joinsession(
        m_nativeBusAttachment,
        &sessionNameUtf8[0],
        serviceInfo->SessionPort,
        SessionListener,
        &m_sessionId,
        sessionOpts);
    if (status != AllJoynStatus::Ok && status != 0x909b) // If the session has already been joined, don't error out here
    {
        return status;
    }
    alljoyn_sessionopts_destroy(sessionOpts);

    ServiceObjectPath = serviceInfo->ObjectPath;
    std::vector<char> objectPath = AllJoynHelpers::PlatformToMultibyteString(ServiceObjectPath);

    if (objectPath.empty())
    {
        return AllJoynStatus::Fail;
    }

    ProxyBusObject = alljoyn_proxybusobject_create(m_nativeBusAttachment, &sessionNameUtf8[0], &objectPath[0], m_sessionId);
    if (nullptr == ProxyBusObject)
    {
        return AllJoynStatus::Fail;
    }

    RETURN_IF_QSTATUS_ERROR(alljoyn_proxybusobject_introspectremoteobject(ProxyBusObject));

    //get the interface name
    m_objectInterface = ifName;

    PCSTR propertyNames[] = { "Direction", "Range", "Speed" };

    RETURN_IF_QSTATUS_ERROR(alljoyn_proxybusobject_registerpropertieschangedlistener(
        ProxyBusObject,
        m_objectInterface.c_str(),
        propertyNames,
        _countof(propertyNames),
        AllJoynHelpers::PropertyChangedHandler<airflowConsumer>, 
        m_weak));


    alljoyn_interfacedescription description = alljoyn_busattachment_getinterface(m_nativeBusAttachment, m_objectInterface.c_str());
    if (nullptr == description)
    {
        return AllJoynStatus::Fail;
    }

    unsigned int noneMechanismIndex = 0;
    bool authenticationMechanismsContainsNone = m_busAttachment->AuthenticationMechanisms->IndexOf(AllJoynAuthenticationMechanism::None, &noneMechanismIndex);
    QCC_BOOL interfaceIsSecure = alljoyn_interfacedescription_issecure(description);

    // If the current set of AuthenticationMechanisms supports authentication, 
    // determine whether to secure the connection.
    if (AllJoynHelpers::CanSecure(m_busAttachment->AuthenticationMechanisms))
    {
        // Secure the connection if the org.alljoyn.Bus.Secure XML annotation
        // is specified, or if None is not present in AuthenticationMechanisms.
        if (!authenticationMechanismsContainsNone || interfaceIsSecure)
        {
            alljoyn_proxybusobject_secureconnection(ProxyBusObject, QCC_FALSE);
        }
    }
    else
    {
        // If the current set of AuthenticationMechanisms does not support authentication
        // but the interface requires security, report an error.
        if (interfaceIsSecure)
        {
            return static_cast<int32>(ER_BUS_NO_AUTHENTICATION_MECHANISM);
        }
    }

    RETURN_IF_QSTATUS_ERROR(AllJoynBusObjectManager::GetBusObject(m_nativeBusAttachment, AllJoynHelpers::PlatformToMultibyteString(ServiceObjectPath).data(), &m_busObject));

    if (!AllJoynBusObjectManager::BusObjectIsRegistered(m_nativeBusAttachment, m_busObject))
    {
        RETURN_IF_QSTATUS_ERROR(alljoyn_busobject_addinterface(BusObject, description));
    }


    SourceInterfaces[description] = m_weak;
    RETURN_IF_QSTATUS_ERROR(AllJoynBusObjectManager::TryRegisterBusObject(m_nativeBusAttachment, BusObject, true));
    m_signals->Initialize(BusObject, m_sessionId);

    return AllJoynStatus::Ok;
}
