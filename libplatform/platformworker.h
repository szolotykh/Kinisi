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

namespace platform
    {
    struct platform_settings_t
        {
        };

    class CPlatformWorker
        {
        public:
            CPlatformWorker(platform_settings_t settings);
            ~CPlatformWorker();

        public:
            void Stop();

        private:
            bool isStopping();
            void fProcess (platform_settings_t settings);

        private:
            std::thread m_thd;
            std::mutex m_mutex;
            bool m_bShutdown;
        };
    }

#endif