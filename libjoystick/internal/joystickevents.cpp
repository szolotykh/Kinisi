//*************************************************************
//
// File name: joystickevents.cpp
//
//*************************************************************

#include "joystickevents.h"
#include <joystick.h>

using namespace std;

namespace vsjoystick
{
    CJoystickEvent::CJoystickEvent(callback_t callback)
    : m_callback(callback)
    {
    }

    void CJoystickEvent::Execute(joystick_event_t event) {
        m_callback(event);
    }

    //----------------------------------------------------------------------
    CJoystickAxisEvent::CJoystickAxisEvent(callback_t callback)
        : CJoystickEvent(callback)
    {
    }

    void CJoystickAxisEvent::Execute(joystick_event_t event) {
        if (event.type == JS_EVENT_AXIS)
        {
            CJoystickEvent::Execute(event);
        }
    }

    //----------------------------------------------------------------------
    CJoystickButtonEvent::CJoystickButtonEvent(callback_t callback)
        : CJoystickEvent(callback)
    {
    }

    void CJoystickButtonEvent::Execute(joystick_event_t event) {
        if (event.type == JS_EVENT_BUTTON)
        {
            CJoystickEvent::Execute(event);
        }
    }
}