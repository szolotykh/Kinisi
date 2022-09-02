//*************************************************************
//
// File name: joystickworker.cpp
//
//*************************************************************

#include "joystickworker.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/joystick.h>

using namespace std;

namespace vsjoystick
{
    CJoystickWorker::CJoystickWorker(settings_t settings)
        : m_isRunning(false)
        , m_bShutdown(false)
        , m_settings(settings)
    {
        cout << "CJoystickWorker" << endl;
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::AddEvent(IJoystickEvent::Ptr event)
    {
        if (m_isRunning) {
            return false;
        }

        m_events.push_back(event);
        return true;
    }

    // -------------------------------------------------------------------
    void CJoystickWorker::Start()
    {
        m_isRunning = true;
        m_thd = std::thread(&CJoystickWorker::fProcess, this, m_settings);
    }

    // -------------------------------------------------------------------
    void CJoystickWorker::Stop()
    {
        if (m_isRunning) {
            lock_guard<mutex> lockGuard(m_StopMutex);
            m_bShutdown = true;
        }
    }

    // -------------------------------------------------------------------
    void CJoystickWorker::fProcess(settings_t settings)
    {
        int fd = open(settings.port.c_str(), O_RDONLY);
        if (fd < 0)
        {
            cout << "Joystick is not connected." << endl;
            return;
        }

        while (!isStopping())
        {
            js_event e;
            read(fd, &e, sizeof(e));

            joystick_event_t joystickEvent{
                time:e.time,
                value : e.value,
                type: e.type,
                number: e.number
            };
            
            // Pass joystick event to all worker events
            for (auto we : m_events) {
                we->Execute(joystickEvent);
            }
        }

        close(fd);
    }

    bool CJoystickWorker::isStopping()
    {
        lock_guard<mutex> lockGuard(m_StopMutex);
        return m_bShutdown;
    }

    // -------------------------------------------------------------------
    CJoystickWorker::~CJoystickWorker()
    {
        m_thd.join();
    }
}