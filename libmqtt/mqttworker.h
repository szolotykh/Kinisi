//*************************************************************
//
// File name: mqttworker.h
//
//*************************************************************

#ifndef ROBOT_MQTTWORKER
#define ROBOT_MQTTWORKER

#include <thread>
#include <mutex>
#include <string>

namespace robot
    {
    struct connection_settings_t
        {
        std::string host;
        std::string username;
        std::string password;
        };

    class CMQTTWorker
        {
        public:
            CMQTTWorker(connection_settings_t settings);
            ~CMQTTWorker();

        public:
            void Stop();

        private:
            bool isStopping();
            void fProcess (connection_settings_t settings);

        private:
            std::thread m_thd;
            std::mutex m_mutex;
            bool m_bShutdown;
        };
    }
#endif
