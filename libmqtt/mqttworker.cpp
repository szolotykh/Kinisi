//*************************************************************
//
// File name: mqttworker.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>

#include "mqttclient.h"
#include "mqttcommands.h"
#include "mqttworker.h"

using namespace std;

namespace vsmqtt
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
        lock_guard<mutex> lockGuard(m_StopMutex);
        m_bShutdown = true;
        }
    // -------------------------------------------------------------------
    bool CMQTTWorker::isStopping()
        {
        lock_guard<mutex> lockGuard(m_StopMutex);
        return m_bShutdown;
        }

    // -------------------------------------------------------------------
    void CMQTTWorker::fProcess (connection_settings_t settings)
        {
        auto client = make_shared<CMQTTClient>(settings.host);
        if(!client->Connect(settings.username, settings.password)){
            return;
        }
        
        while (!isStopping ())
            {
            vscommon::ICommand::Ptr command = PullCommand();
            if(command)
                {
                command->Execute(client);
                }
            this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        
        client->Disconnect();
        }

    // -------------------------------------------------------------------
    CMQTTWorker::~CMQTTWorker()
        {
        m_thd.join();
        }
    }