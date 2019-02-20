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
#include "commands.h"

namespace vsmqtt
    {
    class CMQTTSubscribeCommand : public vscommon::ICommand
        {
        public:
            CMQTTSubscribeCommand(std::string topic, subscription_callback_t callback);
            void Execute(vscommon::ICommand::TargetPtr target);

        private:
            std::string m_topic;
            subscription_callback_t m_callback;
        };

    class CMQTTPublishCommand : public vscommon::ICommand
        {
        public:
            CMQTTPublishCommand(std::string topic, std::string msg);
            void Execute(vscommon::ICommand::TargetPtr target);

        private:
            std::string m_topic;
            std::string m_msg;
        };
    }
#endif
