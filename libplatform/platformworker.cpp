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
        , m_settings (settings)
        {
        }
     
    // -------------------------------------------------------------------
    bool CPlatformWorker::Start()
    {
        IPlatformPtr upPlatform = BuildPlatform(platform_type_t::REAL);
        if (!upPlatform->Start())
        {
            return false;
        }

        m_thd = std::thread (&CPlatformWorker::fProcess, this, upPlatform);
        return true;
    }

    // -------------------------------------------------------------------
    void CPlatformWorker::Stop() 
        {
        lock_guard<mutex> lockGuard(m_StopMutex);
        m_bShutdown = true;
        }

    // -------------------------------------------------------------------
    bool CPlatformWorker::isStopping()
        {
        lock_guard<mutex> lockGuard(m_StopMutex);
        return m_bShutdown;
        }

    // -------------------------------------------------------------------
    void CPlatformWorker::fProcess (IPlatformPtr upPlatform)
        {
        // Worker main loop
        while (!isStopping ())
            {
            vscommon::ICommand::Ptr command = PullCommand();
            if(command)
                {
                command->Execute(upPlatform);
                }
            this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }

    // -------------------------------------------------------------------
    CPlatformWorker::~CPlatformWorker()
        {
        if (m_thd.joinable())
            {
            m_thd.join();
            }
        }
    }