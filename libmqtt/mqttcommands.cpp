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
    // -------------------------------------------------------------------
    CMQTTSubscribeCommand::CMQTTSubscribeCommand(std::string topic, subscription_callback_t callback)
        : m_topic(topic)
        , m_callback(callback)
        {
        }

    // -------------------------------------------------------------------
    void CMQTTSubscribeCommand::Execute(CMQTTClient& mqttClient)
        {
        mqttClient.Subscribe(m_topic, m_callback);
        }

    // -------------------------------------------------------------------
    CMQTTPublishCommand::CMQTTPublishCommand(std::string topic, std::string msg)
        : m_topic(topic)
        , m_msg(msg)
        {
        }

    // -------------------------------------------------------------------
    void CMQTTPublishCommand::Execute(CMQTTClient& mqttClient)
        {
        mqttClient.Publish(m_topic, m_msg);
        }
    }