//*************************************************************
//
// File name: joystickcommands.h
//
// MQTT Worker commangs
//*************************************************************

#ifndef LIBJOYSTICK_JOYSTICKCOMMANDS
#define LIBJOYSTICK_JOYSTICKCOMMANDS

#include <memory>
#include <string>
#include <cstdint>
#include <functional>

namespace vsjoystick
{
    struct joystick_event_t
    {
        unsigned int time;
        int value;
        unsigned char type;
        unsigned number;
    };

    class IJoystickEvent
    {
    public:
        using Ptr = std::shared_ptr<IJoystickEvent>;
    public:
        virtual void Execute(joystick_event_t event) = 0;
    };

    class CJoystickEvent : public IJoystickEvent
    {
    public:
        using callback_t = std::function<void(joystick_event_t)>;

    public:
        CJoystickEvent( callback_t callback);
        void Execute(joystick_event_t event);

    private:
        callback_t m_callback;
    };
}
#endif
