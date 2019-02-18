//*************************************************************
//
// File name: mqttcommands.h
//
//*************************************************************

#ifndef LIBMQTT_MQTTCOMMANDS
#define LIBMQTT_MQTTCOMMANDS

#include <memory>
#include <string>
#include "mqttclient.h"

namespace vsmqtt
    {
    class CMQTTCommand
        {
        public:
            using Ptr = std::unique_ptr<CMQTTCommand>;
        public:
            virtual void Execute(CMQTTClient& mqttClient) = 0;
        };

    class CMQTTSubscribeCommand : public CMQTTCommand
        {
        public:
            CMQTTSubscribeCommand(std::string topic, subscription_callback_t callback);
            void Execute(CMQTTClient& mqttClient);

        private:
            std::string m_topic;
            subscription_callback_t m_callback;
        };

    class CMQTTPublishCommand : public CMQTTCommand
        {
        public:
            CMQTTPublishCommand(std::string topic, std::string msg);
            void Execute(CMQTTClient& mqttClient);

        private:
            std::string m_topic;
            std::string m_msg;
        };
    }
#endif
