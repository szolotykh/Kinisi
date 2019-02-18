//*************************************************************
//
// File name: mqttclient.h
//
//*************************************************************

#ifndef VSMQTT_CLIENT
#define VSMQTT_CLIENT

#include <thread>
#include <mutex>
#include <string>
#include <unordered_map>
#include <functional>
#include "mqtt/async_client.h"

namespace vsmqtt
    {
    using subscription_callback_t = std::function<void(std::string)>;
    using subscriptions_map_t = std::unordered_map<std::string, subscription_callback_t>;
    using subscriptions_map_ptr = std::shared_ptr<subscriptions_map_t>;
    
    class CSubscriptionActionListener : public virtual mqtt::iaction_listener
        {
        public:
            CSubscriptionActionListener ()
            : m_sName("")
            {
            }

            CSubscriptionActionListener(const std::string& name)
            : m_sName(name)
            {
            }

        // Events
        void on_failure(const mqtt::token& tok) override;
        void on_success(const mqtt::token& tok) override;

        private:
            std::string m_sName;
        };

    class CMQTTClientCallback : public virtual mqtt::callback
        {
        public:
            CMQTTClientCallback()
            : m_spClient(nullptr)
            , m_spSubscriptions(nullptr)
            {
            }
            
            CMQTTClientCallback(
                std::shared_ptr<mqtt::async_client> client,
                subscriptions_map_ptr subscriptions)
            : m_spClient(client)
            , m_spSubscriptions(subscriptions)
            {
            }

        public:
            void connected(const std::string& cause) override;
            void connection_lost(const std::string& cause) override {}
            void message_arrived(mqtt::const_message_ptr msg) override;
            void delivery_complete(mqtt::delivery_token_ptr tok) override {}

        private:
            std::shared_ptr<mqtt::async_client> m_spClient;
            subscriptions_map_ptr m_spSubscriptions;
        };

    class CMQTTClient
        {
        public:
            CMQTTClient(std::string address);
            ~CMQTTClient();

        public:
            bool Connect(std::string username, std::string password);
            bool Subscribe(std::string topic, subscription_callback_t callback);
            void Publish(std::string topic, std::string data);
            void Disconnect();

        private:
            CMQTTClientCallback m_ClientCallback;
            std::string m_sAddress;
            int m_QOS;
            std::shared_ptr<mqtt::async_client> m_spClient;
            CSubscriptionActionListener m_SubscriptionActionListener;

            subscriptions_map_ptr m_spSubscriptions;
        };
    }
#endif