#include <iostream>
#include <memory>
#include "mqttworker.h"
#include "settings.h"
#include <sstream> 

using namespace std;
using namespace robot;

int main(){
    cout<<"Robot"<<endl;
    
    CRobotSettings Settings;
    vssettings::LoadSettings("settings.json", Settings);

    auto spConnectionSettings = Settings.GetConnectionSettings();

    stringstream ssAdress;
    ssAdress << spConnectionSettings->GetProtocol() + "://" + spConnectionSettings->GetHost() << ":" << spConnectionSettings->GetPort();

    robot::connection_settings_t stConnectionSettings{
        ssAdress.str(),
        spConnectionSettings->GetUsername(),
        spConnectionSettings->GetPassword()
    };
    robot::CMQTTWorker MQTTWorker(stConnectionSettings);

    cout << "Press Enter to Continue" << endl;
    cin.ignore();
    MQTTWorker.Stop();
    return 0;
}