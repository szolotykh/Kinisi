#include <iostream>
#include <memory>
#include "mqttworker.h"
#include "settings.h"
#include <sstream> 

using namespace std;
using namespace robot;

namespace
    {
    string _BuildAddress(string protocol, string host, int port)
        {
        return protocol + "://" + host + ":" + to_string(port);
        }
    }

int main(){
    cout<<"Robot"<<endl;
    
    CRobotSettings Settings;
    vssettings::LoadSettings("settings.json", Settings);

    auto spConnectionSettings = Settings.GetConnectionSettings();


    robot::connection_settings_t stConnectionSettings{
        _BuildAddress(
            spConnectionSettings->GetProtocol(), 
            spConnectionSettings->GetHost(),
            spConnectionSettings->GetPort()),
        spConnectionSettings->GetUsername(),
        spConnectionSettings->GetPassword()
    };
    robot::CMQTTWorker MQTTWorker(stConnectionSettings);

    cout << "Press Enter to Continue" << endl;
    cin.ignore();
    MQTTWorker.Stop();
    return 0;
}