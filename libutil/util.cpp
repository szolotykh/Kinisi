//*************************************************************
//
// File name: util.cpp
//
//*************************************************************

#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

#include "util.h"

using namespace std;

namespace vsutil
{
    // -------------------------------------------------------------------
    CTimerInterval::CTimerInterval(std::function<void()> action, unsigned int sleep_interval)
        : m_action(action)
        , m_sleep_interval(sleep_interval)
        , m_bShutdown(false)
        , m_thd(std::thread(&CTimerInterval::fProcess, this))
    {
    }

    // -------------------------------------------------------------------
    void CTimerInterval::Stop()
    {
        lock_guard<mutex> lockGuard(m_StopMutex);
        m_bShutdown = true;
    }

    // -------------------------------------------------------------------
    bool CTimerInterval::isStopping()
    {
        lock_guard<mutex> lockGuard(m_StopMutex);
        return m_bShutdown;
    }

    // -------------------------------------------------------------------
    void CTimerInterval::fProcess()
    {
        // Worker main loop
        while (!isStopping())
        {
            m_action();
            this_thread::sleep_for(std::chrono::milliseconds(m_sleep_interval));
        }
    }

    // -------------------------------------------------------------------
    CTimerInterval::~CTimerInterval()
    {
        m_thd.join();
    }
}