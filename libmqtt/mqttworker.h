//*************************************************************
//
// File name: mqttworker.h
//
// MQTT Worker is running MQTT client in separate thread and
// provides command interface for expernal threads to communicate
// with the client.
//*************************************************************

#ifndef LIBMQTT_MQTTWORKER
#define LIBMQTT_MQTTWORKER

#include <thread>
#include <mutex>
#include <string>
#include <queue>

#include "command_manager.h"
#include "mqttcommands.h"

namespace vsmqtt
    {
    // Connection settings
    struct connection_settings_t
        {
        std::string host;
        std::string username;
        std::string password;
        };

    // MQTT Worker
    class CMQTTWorker : public vscommon::CCommandManager
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
            std::mutex m_StopMutex;
            bool m_bShutdown;
        };
    }
#endif