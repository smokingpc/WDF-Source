//
//    Copyright (C) Microsoft.  All rights reserved.
//
#ifndef _FXPOXINTERFACE_H_
#define _FXPOXINTERFACE_H_

#include "FxDevicePwrReqStateMachine.hpp"

class FxPoxInterface {

friend class FxDevicePwrRequirementMachine;

public:
    FxPoxInterface(
        __in FxPkgPnp* PkgPnp
        );

    ~FxPoxInterface(
        VOID
        );

    NTSTATUS
    CreateDevicePowerRequirementMachine(
        VOID
        );

    NTSTATUS
    NotifyDevicePowerDown(
        VOID
        );


    VOID
    DeviceIsPoweredOn(
        VOID
        );

    FxPkgPnp*
    PkgPnp(
        VOID
        )
    {
        return m_PkgPnp;
    }

    POHANDLE
    GetPoHandle(
        VOID
        )
    {
        return m_PoHandle;
    }

    NTSTATUS
    InitializeComponents(
        VOID
        );

    VOID
    UninitializeComponents(
        VOID
        );

    VOID
    RequestComponentActive(
        VOID
        );

    BOOLEAN
    DeclareComponentIdle(
        VOID
        );

    VOID
    UpdateIdleTimeoutHint(
        VOID
        );

    VOID
    SimulateDevicePowerRequired(
        VOID
        );

    VOID
    SimulateDevicePowerNotRequired(
        VOID
        );

    VOID
    PoxReportDevicePoweredOn(
        VOID
        );

    VOID
    PowerRequiredCallbackInvoked(
        VOID
        );

    VOID
    PowerNotRequiredCallbackInvoked(
        VOID
        );

    VOID
    SimulateDevicePowerRequiredInReflector(
        VOID
        );

    VOID
    NotifyDeviceDirectedPoweredDown(
        VOID
        );

    VOID
    NotifyDeviceDirectedPoweredUp(
        VOID
        );

    VOID
    DirectedPowerDownCallbackInvoked(
        VOID
        );

    VOID
    DirectedPowerUpCallbackInvoked(
        VOID
        );

    BOOLEAN
    IsDirectedTransitionInProgress(
        VOID
        );

    VOID
    SetDirectedTransitionInProgress(
        VOID
        );

    VOID
    ClearDirectedTransitionInProgress(
        VOID
        );

private:

    NTSTATUS
    PoxRegisterDevice(
        VOID
        );

    VOID
    DprProcessEventFromPoxCallback(
        __in FxDevicePwrRequirementEvents Event
        );

    struct _POX_SETTINGS *
    GetPowerFrameworkSettings(
        VOID
        );

    VOID
    PowerRequiredCallbackWorker(
        __in BOOLEAN InvokedFromPoxCallback
        );

    VOID
    PowerNotRequiredCallbackWorker(
        __in BOOLEAN InvokedFromPoxCallback
        );

    VOID
    PoxStartDevicePowerManagement(
        VOID
        );

    VOID
    PoxUnregisterDevice(
        VOID
        );

    VOID
    PoxActivateComponent(
        VOID
        );

    VOID
    PoxIdleComponent(
        VOID
        );

    VOID
    PoxSetDeviceIdleTimeout(
        __in ULONGLONG IdleTimeout
        );

    VOID
    DirectedPowerUpCallbackWorker(
        _In_ BOOLEAN InvokedFromPoxCallback
        );

    VOID
    DirectedPowerDownCallbackWorker(
        _In_ BOOLEAN InvokedFromPoxCallback
        );

    VOID
    NotifyPoxDirectedPowerDownCompletion(
        VOID
        );

    VOID
    NotifyPoxDirectedPowerUpCompletion(
        VOID
        );

    VOID
    PoxCompleteDirectedPowerDownTransition(
        VOID
        );

    VOID
    PoxCompleteDirectedPowerUpTransition(
        VOID
        );

    static PO_FX_COMPONENT_IDLE_STATE_CALLBACK StateCallback;
    static PO_FX_COMPONENT_ACTIVE_CONDITION_CALLBACK ComponentActiveCallback;
    static PO_FX_COMPONENT_IDLE_CONDITION_CALLBACK ComponentIdleCallback;
    static PO_FX_DEVICE_POWER_REQUIRED_CALLBACK PowerRequiredCallback;
    static PO_FX_DEVICE_POWER_NOT_REQUIRED_CALLBACK PowerNotRequiredCallback;
    static PO_FX_POWER_CONTROL_CALLBACK PowerControlCallback;
    static PO_FX_DIRECTED_POWER_UP_CALLBACK DirectedPowerUpCallback;
    static PO_FX_DIRECTED_POWER_DOWN_CALLBACK DirectedPowerDownCallback;

public:
    //
    // Device power requirement state machine
    //
    FxDevicePwrRequirementMachine * m_DevicePowerRequirementMachine;

    //
    // Idle timeout hint to be provided to power framework at the next
    // opportunity, i.e. a pending update to the idle timeout hint.
    //
    ULONG m_NextIdleTimeoutHint;

private:
    FxPkgPnp* m_PkgPnp;

    //
    // Handle obtained upon registration with power manager
    //
    POHANDLE m_PoHandle;

    //
    // Variable that tracks whether device power is required and the lock that
    // protects this variable
    //
    BOOLEAN m_DevicePowerRequired;
    MxLock m_DevicePowerRequiredLock;

    //
    // Idle timeout hint currently provided to power framework.
    //
    ULONG m_CurrentIdleTimeoutHint;

    //
    // Variable that tracks whether a directed power (up/down) transition is
    // currently in progress. This variable is synchronized using interlocked
    // operations.
    //
    volatile LONG m_DirectedTransitionActive;
};

#endif // _FXPOXINTERFACE_H_
