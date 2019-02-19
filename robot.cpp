#include <iostream>
#include <memory>
#include "mqttworker.h"
#include "platformworker.h"
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


    vsmqtt::connection_settings_t stConnectionSettings{
        _BuildAddress(
            spConnectionSettings->GetProtocol(), 
            spConnectionSettings->GetHost(),
            spConnectionSettings->GetPort()),
        spConnectionSettings->GetUsername(),
        spConnectionSettings->GetPassword()
    };
    vsmqtt::CMQTTWorker MQTTWorker(stConnectionSettings);

    platform::platform_settings_t stPlatformSettings;
    platform::CPlatformWorker PlatformWorker(stPlatformSettings);


    MQTTWorker.PushCommand(make_unique<vsmqtt::CMQTTSubscribeCommand>(
        "velocity",
        [&PlatformWorker](string msg){
            cout<<"velocity:"<<msg<<endl;
            platform::velocity_t velocity;
            stringstream ss;
            ss<<msg;
            ss >> velocity.x >>velocity.y >> velocity.t;
            PlatformWorker.PushCommand(make_unique<platform::CMoveCommand>(velocity));
        }));

    cout << "Press Enter to Continue" << endl;
    cin.ignore();
    MQTTWorker.Stop();
    PlatformWorker.Stop();
    return 0;
}