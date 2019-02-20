//*************************************************************
//
// File name: command_manager.c
//
//*************************************************************

#ifndef LIBCOMMON_COMMAND_MANAGER_H
#define LIBCOMMON_COMMAND_MANAGER_H

#include <string>
#include <mutex>
#include <queue>

#include "commands.h"

namespace vscommon
    {
    class CCommandManager
        {
        using command_queue_t = std::queue<vscommon::ICommand::Ptr>;

        public:
            bool PushCommand(vscommon::ICommand::Ptr command);
            void CancelAllCommands();
            vscommon::ICommand::Ptr PullCommand();

        private:
            std::mutex m_CommandMutex;
            command_queue_t m_qCommands;
        };
    }

#endif