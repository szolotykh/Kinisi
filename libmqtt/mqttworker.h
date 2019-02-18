//*************************************************************
//
// File name: mqttworker.h
//
//*************************************************************

#ifndef LIBMQTT_MQTTWORKER
#define LIBMQTT_MQTTWORKER

#include <thread>
#include <mutex>
#include <string>
#include <queue>

#include "mqttcommands.h"

namespace vsmqtt
    {
    struct connection_settings_t
        {
        std::string host;
        std::string username;
        std::string password;
        };

    class CMQTTWorker
        {
        using commands_queue_t = std::queue<CMQTTCommand::Ptr>;

        public:
            CMQTTWorker(connection_settings_t settings);
            ~CMQTTWorker();

        public:
            bool PushCommand(CMQTTCommand::Ptr command);
            void CancelAllCommands();
            void Stop();

        private:
            CMQTTCommand::Ptr PullCommand();
            bool isStopping();
            void fProcess (connection_settings_t settings);

        private:
            std::thread m_thd;
            std::mutex m_StopMutex;
            std::mutex m_CommandMutex;
            bool m_bShutdown;
            commands_queue_t m_qCommands;
        };
    }
#endif
