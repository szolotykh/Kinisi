//*************************************************************
//
// File name: joystickevents.cpp
//
//*************************************************************

#include "joystickevents.h"

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
}