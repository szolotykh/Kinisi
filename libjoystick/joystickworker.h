//*************************************************************
//
// File name: joystickworker.h
//
//*************************************************************

#ifndef LIBJOYSTICK_MQTTWORKER
#define LIBJOYSTICK_MQTTWORKER

#include <thread>
#include <mutex>
#include <string>
#include <vector>

#include "joystickevents.h"

namespace vsjoystick
{
    // Connection settings
    struct settings_t
    {
        std::string port;
    };

    // Joystick Worker
    class CJoystickWorker
    {
    public:
        CJoystickWorker(settings_t settings);
        ~CJoystickWorker();

    public:
        void Start();
        void Stop();
        bool AddEvent(IJoystickEvent::Ptr event);

    private:
        bool isStopping();
        void fProcess(settings_t settings);

    private:
        const settings_t m_settings;
        std::vector<IJoystickEvent::Ptr> m_events;
        std::thread m_thd;
        std::mutex m_StopMutex;

        bool m_isRunning;
        bool m_bShutdown;
    };
}
#endif