//*************************************************************
//
// File name: platformworker.cpp
//
//*************************************************************
#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>

#include "platform.h"
#include "platformworker.h"

using namespace std;

namespace platform
    {
    // -------------------------------------------------------------------
    CPlatformWorker::CPlatformWorker(platform_settings_t settings)
        : m_bShutdown (false)
        , m_thd (std::thread (&CPlatformWorker::fProcess, this, settings))
        {
        }

    // -------------------------------------------------------------------
    void CPlatformWorker::Stop() 
        {
        lock_guard<mutex> lockGuard(m_mutex);
        m_bShutdown = true;
        }
    // -------------------------------------------------------------------
    bool CPlatformWorker::isStopping()
        {
        lock_guard<mutex> lockGuard(m_mutex);
        return m_bShutdown;
        }

    // -------------------------------------------------------------------
    void CPlatformWorker::fProcess (platform_settings_t settings)
        {
        IPlatformPtr upPlatform = BuildPlatform(platform_type_t::VIRTUAL);
        
        // Worker main loop
        while (!isStopping ())
            {
            upPlatform->Forward(1);
            this_thread::sleep_for(5s);
            }
        }

    // -------------------------------------------------------------------
    CPlatformWorker::~CPlatformWorker()
        {
        m_thd.join();
        }
    }