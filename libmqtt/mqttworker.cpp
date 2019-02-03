//*************************************************************
//
// File name: mqttworker.h
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>

#include "mqttclient.h"
#include "mqttworker.h"


using namespace std;

namespace robot
    {
    // -------------------------------------------------------------------
    CMQTTWorker::CMQTTWorker(connection_settings_t settings)
        : m_bShutdown (false)
        , m_thd (std::thread (&CMQTTWorker::fProcess, this, settings))
        {
        cout<<"CMQTTWorker"<<endl;
        }

    // -------------------------------------------------------------------
    void CMQTTWorker::Stop() 
        {
        lock_guard<mutex> lockGuard(m_mutex);
        m_bShutdown = true;
        }
    // -------------------------------------------------------------------
    bool CMQTTWorker::isStopping()
        {
        lock_guard<mutex> lockGuard(m_mutex);
        return m_bShutdown;
        }

    // -------------------------------------------------------------------
    void CMQTTWorker::fProcess (connection_settings_t settings)
        {
        vsmqtt::CMQTTClient client (settings.host);
        if(!client.Connect(settings.username, settings.password)){
            return;
        }
        client.Subscribe("robot", [](string msg){
            cout<<"robot:"<<msg<<endl;
        });

        client.Subscribe("robot/sensor", [](string msg){
            cout<<"robot/sensor: "<<msg<<endl;
        });
        
        while (!isStopping ())
            {
            // Create the payload as a text CSV string
            string payload = "hello";
            cout << payload << endl;
            client.Publish("status", payload);
            this_thread::sleep_for(5s);
            }
        
        client.Disconnect();
        }

    // -------------------------------------------------------------------
    CMQTTWorker::~CMQTTWorker()
        {
        m_thd.join();
        }
    }