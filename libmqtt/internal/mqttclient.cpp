//*************************************************************
//
// File name: mqttclient.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <memory>
#include <chrono>
#include <mutex>
#include <unordered_map>
#include <functional>
#include "mqtt/async_client.h"
#include "mqttclient.h"

using namespace std;

namespace vsmqtt
    {
    // -------------------------------------------------------------------
    void CMQTTClientCallback::connected(const std::string& cause) {
        cout<<">> Connected"<< endl;
    }

    // -------------------------------------------------------------------
    void CMQTTClientCallback::message_arrived(mqtt::const_message_ptr msg) {
        // Calling subscription callback
        auto& callback = m_spSubscriptions->at(msg->get_topic());
        callback(msg->to_string());
    }

    // -------------------------------------------------------------------
    CMQTTClient::CMQTTClient(string address)
        : m_sAddress (address)
        , m_spSubscriptions (make_shared<subscriptions_map_t>())
        , m_QOS (1)
        {
        cout<<"CMQTTClient"<<endl;

        const int MAX_BUFFERED_MSGS = 120;
        const string PERSIST_DIR { "data-persist" };
        const string TOPIC { "data/rand" };
        
        
        m_spClient = make_shared<mqtt::async_client> (m_sAddress, "kinisi-platform", MAX_BUFFERED_MSGS, PERSIST_DIR);


        // Callbacks
        m_ClientCallback = CMQTTClientCallback (m_spClient, m_spSubscriptions);
        m_spClient->set_callback(m_ClientCallback);
        }

    // -------------------------------------------------------------------
    bool CMQTTClient::Connect(string username, string password)
        {
        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(20000);
        connOpts.set_clean_session(true);
        connOpts.set_automatic_reconnect(true);
        connOpts.set_user_name(username);
        connOpts.set_password(password);

        try
            {
            // Connect to the MQTT broker
            cout << "Connecting to server '" << m_sAddress << "'..." << flush;
            m_spClient->connect(connOpts)->wait();
            cout << "OK" << endl;
            return true;
            }
        catch (const mqtt::exception& exc)
            {
            cerr << exc.what() << endl;
            return false;
            }
        }

    bool CMQTTClient::Subscribe (std::string topic, subscription_callback_t callback)
        {
        if(m_spSubscriptions->find(topic) != m_spSubscriptions->end()){
            // Callback for this topic exists
            return false;
        }
        m_spSubscriptions->insert ({topic, callback});
        m_spClient->subscribe(topic, m_QOS, nullptr, m_SubscriptionActionListener);
        }

    // -------------------------------------------------------------------
    void CMQTTClient::Publish(string topic, string data)
        {
        // Topics
        mqtt::topic topicStatus(*m_spClient.get(), topic, m_QOS, true);
        // Publish to the topic
        topicStatus.publish(std::move(data));
        }

    // -------------------------------------------------------------------
    void CMQTTClient::Disconnect ()
        {
        try
            {
            // Disconnect
            cout << "\nDisconnecting..." << flush;
            m_spClient->disconnect()->wait();
            cout << "OK" << endl;
            }
        catch (const mqtt::exception& exc)
            {
            cerr << exc.what() << endl;
            return;
            }
        }

    // -------------------------------------------------------------------
    CMQTTClient::~CMQTTClient()
        {
        }

    // -------------------------------------------------------------------
    void CSubscriptionActionListener::on_failure(const mqtt::token& token)
        {
        stringstream msg;
        msg << m_sName << " failure. ";
        if (token.get_message_id() != 0)
            {
            msg << "Token: " << token.get_message_id() << endl;
            }
        cerr << msg.str();
        }

    // -------------------------------------------------------------------
    void CSubscriptionActionListener::on_success(const mqtt::token& token)
        {
        stringstream msg;
        msg << m_sName << " success. ";

        if (token.get_message_id() != 0)
            {
            msg << "Token: " << token.get_message_id() << endl;
            }

        auto topics = token.get_topics();
        if (topics && !topics->empty())
            {
            msg << " Topic: " << (*topics)[0] << endl;
            }

        cerr << msg.str();
        }
    }