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
        : m_state(EWorkerState::Stopped)
        , m_settings(settings)
    {
        cout << "CJoystickWorker" << endl;
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::AddEvent(IJoystickEvent::Ptr event)
    {
        if (IsStop()) {
            m_events.push_back(event);
            return true;
        }
        return false;
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::Start()
    {
        if (IsRunning())
        {
            return true;
        }

        int fd = open(m_settings.port.c_str(), O_RDONLY);
        if (fd < 0)
        {
            return false;
        }

        SetState(Running);
        m_thd = std::thread(&CJoystickWorker::fProcess, this, fd);
        return true;
    }

    // -------------------------------------------------------------------
    void CJoystickWorker::fProcess(int fd)
    {
        while (!IsStopping())
        {
            js_event e;
            read(fd, &e, sizeof(e));

            joystick_event_t joystickEvent{
                time:e.time,
                value : e.value,
                type: e.type & ~JS_EVENT_INIT,
                number: e.number,
                initial: e.type & JS_EVENT_INIT
            };
            
            // Pass joystick event to all worker events
            for (auto we : m_events) {
                we->Execute(joystickEvent);
            }
        }
        close(fd);
        SetState(Stopped);
    }

    // -------------------------------------------------------------------
    void CJoystickWorker::Stop()
    {
        SetState(Stopping);
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::IsConnected()
    {
        return IsRunning();
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::IsStop()
    {
        lock_guard<mutex> lockGuard(m_StateMutex);
        return m_state == EWorkerState::Stopped;
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::IsStopping()
    {
        lock_guard<mutex> lockGuard(m_StateMutex);
        return m_state == EWorkerState::Stopping;
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::IsRunning()
    {
        lock_guard<mutex> lockGuard(m_StateMutex);
        return m_state == EWorkerState::Running;
    }

    // -------------------------------------------------------------------
    bool CJoystickWorker::isStarting()
    {
        lock_guard<mutex> lockGuard(m_StateMutex);
        return m_state == EWorkerState::Starting;
    }

    // -------------------------------------------------------------------
    void  CJoystickWorker::SetState(EWorkerState state)
    {
        lock_guard<mutex> lockGuard(m_StateMutex);
        m_state = state;
    }

    // -------------------------------------------------------------------
    CJoystickWorker::~CJoystickWorker()
    {
        if (m_thd.joinable())
        {
            m_thd.join();
        }
    }
}