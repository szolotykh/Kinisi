#include <iostream>
#include "mqttworker.h"
#include "settings.h"
#include <sstream> 

using namespace std;
using namespace vssettings;



class CConnectionSettings : public CPropertyGroup
    {
    public:
        CConnectionSettings()
            {
            AddProperty(CProperty("protocol",   property_type_t::STRING,    "tcp"));
            AddProperty(CProperty("host",       property_type_t::STRING,    "localhost"));
            AddProperty(CProperty("port",       property_type_t::INT,       8883));
            AddProperty(CProperty("username",   property_type_t::STRING,    "empty"));
            AddProperty(CProperty("password",   property_type_t::STRING,    ""));
            }

    public:
        std::string GetProtocol(){ return GetProperty("protocol").GetString(); }
        void SetProtocol(const std::string& host){ GetProperty("protocol").SetValue(host);}

        std::string GetHost(){ return GetProperty("host").GetString(); }
        void SetHost(const std::string& host){ GetProperty("host").SetValue(host);}

        int GetPort(){ return GetProperty("port").GetInt(); }
        void SetPort(const std::string& host){ GetProperty("port").SetValue(host); }

        std::string GetUsername(){ return GetProperty("username").GetString(); }
        void SetUsername(const std::string& host){ GetProperty("username").SetValue(host); }

        std::string GetPassword(){ return GetProperty("password").GetString();}
        void SetPassword(const std::string& host){ GetProperty("password").SetValue(host); }
    };

int main(){
    cout<<"Robot"<<endl;
    
    CConnectionSettings Settings;
    Settings.LoadSettings("settings.json");
    cout<<Settings.GetProtocol()<<endl;
    cout<<Settings.GetHost()<<endl;
    cout<<Settings.GetPort()<<endl;
    cout<<Settings.GetUsername()<<endl;
    cout<<Settings.GetPassword()<<endl;

    stringstream ssAdress;
    ssAdress << Settings.GetProtocol() + "://" + Settings.GetHost() << ":" << Settings.GetPort();

    robot::connection_settings_t stConnectionSettings{
        ssAdress.str(),
        Settings.GetUsername(),
        Settings.GetPassword()
    };
    robot::CMQTTWorker MQTTWorker(stConnectionSettings);

    cout << "Press Enter to Continue" << endl;
    cin.ignore();
    MQTTWorker.Stop();
    return 0;
}