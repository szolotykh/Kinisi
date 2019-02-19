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
    bool CPlatformWorker::PushCommand(CCommand::Ptr command)
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        m_qCommands.push(std::move(command));
        return true;
        }

    // -------------------------------------------------------------------
    CCommand::Ptr CPlatformWorker::PullCommand()
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        if (m_qCommands.empty())
            {
            return nullptr; 
            }
        CCommand::Ptr command = std::move(m_qCommands.front());
        m_qCommands.pop();
        return std::move(command);
        }

    // -------------------------------------------------------------------
    void CPlatformWorker::CancelAllCommands()
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        commands_queue_t empty;
        std::swap(m_qCommands, empty);
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
    void CPlatformWorker::fProcess (platform_settings_t settings)
        {
        IPlatformPtr upPlatform = BuildPlatform(platform_type_t::REAL);
        
        // Worker main loop
        while (!isStopping ())
            {
            CCommand::Ptr command = PullCommand();
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
        m_thd.join();
        }
    }