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

#include "command_manager.h"
#include "platformcommands.h"

namespace platform
    {
    struct platform_settings_t
        {
        };

    class CPlatformWorker : public vscommon::CCommandManager
        {
        public:
            CPlatformWorker(platform_settings_t settings);
            ~CPlatformWorker();

        public:
            bool Start();
            void Stop();

        private:
            bool isStopping();
            void fProcess (IPlatformPtr upPlatform);

        private:
            platform_settings_t m_settings;

            std::thread m_thd;
            std::mutex m_StopMutex;
            bool m_bShutdown;
        };
    }

#endif