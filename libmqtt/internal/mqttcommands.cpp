//*************************************************************
//
// File name: mqttcommands.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>

#include "mqttclient.h"
#include "mqttcommands.h"

using namespace std;

namespace vsmqtt
    {
    using namespace vscommon;
    // -------------------------------------------------------------------
    CMQTTSubscribeCommand::CMQTTSubscribeCommand(std::string topic, callback_t callback)
        : m_topic(topic)
        , m_callback(callback)
        {
        }

    // -------------------------------------------------------------------
    void CMQTTSubscribeCommand::Execute(ICommand::TargetPtr target)
        {
        static_pointer_cast<CMQTTClient>(target)->Subscribe(m_topic, m_callback);
        }

    // -------------------------------------------------------------------
    CMQTTPublishCommand::CMQTTPublishCommand(std::string topic, std::string msg)
        : m_topic(topic)
        , m_msg(msg)
        {
        }

    // -------------------------------------------------------------------
    void CMQTTPublishCommand::Execute(ICommand::TargetPtr target)
        {
        static_pointer_cast<CMQTTClient>(target)->Publish(m_topic, m_msg);
        }
    }