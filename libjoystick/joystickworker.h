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

    private:
        enum EWorkerState
        {
            Stopped = 0,
            Stopping,
            Starting,
            Running
        };

    private:
        bool IsStop();
        bool IsStopping();
        bool IsRunning();
        bool isStarting();

        void SetState(EWorkerState state);

        void fProcess(int fd);

    public:
        bool Start();
        void Stop();
        bool IsConnected();
        bool AddEvent(IJoystickEvent::Ptr event);

    private:
        int m_fd;

        const settings_t m_settings;
        std::vector<IJoystickEvent::Ptr> m_events;
        std::thread m_thd;
        std::mutex m_StateMutex;

        EWorkerState m_state;
    };
}
#endif