//*************************************************************
//
// File name: mqttcommands.h
//
// MQTT Worker commangs
//*************************************************************

#ifndef LIBMQTT_MQTTCOMMANDS
#define LIBMQTT_MQTTCOMMANDS

#include <memory>
#include <string>
#include <functional>
#include "commands.h"

namespace vsmqtt
    {
    class CMQTTSubscribeCommand : public vscommon::ICommand
        {
        public:
            using callback_t = std::function<void(std::string)>;

        public:
            CMQTTSubscribeCommand(std::string topic, callback_t callback);
            void Execute(vscommon::ICommand::TargetPtr target);

        private:
            std::string m_topic;
            callback_t m_callback;
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
