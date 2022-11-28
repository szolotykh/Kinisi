//*************************************************************
//
// File name: libutil.h
//
//*************************************************************

#ifndef LIBUTIL_UTIL_H
#define LIBUTIL_UTIL_H

#include <thread>
#include <mutex>
#include <functional>

namespace vsutil
    {
    class CTimerInterval
        {
        public:
            CTimerInterval(std::function<void()> action, unsigned int sleep_interval);
            ~CTimerInterval();

        public:
            void Stop();

        private:
            bool isStopping();
            void fProcess();

        private:
            unsigned int m_sleep_interval; // ms
            std::function<void()> m_action;

            std::thread m_thd;
            std::mutex m_StopMutex;
            bool m_bShutdown;
        };
    }

#endif