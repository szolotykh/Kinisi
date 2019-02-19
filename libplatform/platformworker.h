//*************************************************************
//
// File name: platformworker.h
//
//*************************************************************

#ifndef LIBPLATFORM_PLATFORMWORKER
#define LIBPLATFORM_PLATFORMWORKER

#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include "platformcommands.h"

namespace platform
    {
    struct platform_settings_t
        {
        };

    class CPlatformWorker
        {
        using commands_queue_t = std::queue<CCommand::Ptr>;
        
        public:
            CPlatformWorker(platform_settings_t settings);
            ~CPlatformWorker();

        public:
            bool PushCommand(CCommand::Ptr command);
            void CancelAllCommands();
            void Stop();

        private:
            CCommand::Ptr PullCommand();
            bool isStopping();
            void fProcess (platform_settings_t settings);

        private:
            std::thread m_thd;
            std::mutex m_StopMutex;
            std::mutex m_CommandMutex;
            bool m_bShutdown;
            commands_queue_t m_qCommands;
        };
    }

#endif