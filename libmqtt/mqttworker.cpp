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
    bool CMQTTWorker::PushCommand(CMQTTCommand::Ptr command)
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        m_qCommands.push(std::move(command));
        return true;
        }

    // -------------------------------------------------------------------
    CMQTTCommand::Ptr CMQTTWorker::PullCommand()
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        if (m_qCommands.empty())
            {
            return nullptr; 
            }
        CMQTTCommand::Ptr command = std::move(m_qCommands.front());
        m_qCommands.pop();
        return std::move(command);
        }

    // -------------------------------------------------------------------
    void CMQTTWorker::CancelAllCommands()
        {
        lock_guard<mutex> lockGuard(m_CommandMutex);
        commands_queue_t empty;
        std::swap(m_qCommands, empty);
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
        vsmqtt::CMQTTClient client (settings.host);
        if(!client.Connect(settings.username, settings.password)){
            return;
        }
        
        while (!isStopping ())
            {
            CMQTTCommand::Ptr command = PullCommand();
            if(command)
                {
                command->Execute(client);
                }
            this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        
        client.Disconnect();
        }

    // -------------------------------------------------------------------
    CMQTTWorker::~CMQTTWorker()
        {
        m_thd.join();
        }
    }