//*************************************************************
//
// File name: command_manager.cpp
//
//*************************************************************

#include <mutex>
#include "command_manager.h"

using namespace std;

namespace vscommon
    {
    // -------------------------------------------------------------------
    bool CCommandManager::PushCommand(ICommand::Ptr command)
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        m_qCommands.push(std::move(command));
        return true;
        }

    // -------------------------------------------------------------------
    ICommand::Ptr CCommandManager::PullCommand()
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        if (m_qCommands.empty())
            {
            return nullptr; 
            }
        ICommand::Ptr command = std::move(m_qCommands.front());
        m_qCommands.pop();
        return std::move(command);
        }

    // -------------------------------------------------------------------
    void CCommandManager::CancelAllCommands()
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        command_queue_t empty;
        std::swap(m_qCommands, empty);
        }
    }