#include <iostream>
#include <memory>
#include "mqttworker.h"
#include "platformworker.h"
#include "joystickworker.h"
#include "settings.h"
#include <sstream> 
#include <joystick.h>

using namespace std;
using namespace robot;

#define JOYSTICK_PORT "/dev/input/js0"

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

    platform::platform_settings_t stPlatformSettings;
    platform::CPlatformWorker PlatformWorker(stPlatformSettings);

    platform::velocity_t velocity;
    int previousX = 0;

    vsjoystick::CJoystickWorker JoystickWorker(vsjoystick::settings_t{ port:JOYSTICK_PORT });
    JoystickWorker.AddEvent(std::make_shared<vsjoystick::CJoystickAxisEvent>(
        [&PlatformWorker, &velocity, &previousX](vsjoystick::joystick_event_t event) {
            if (event.number == JS_AXIS_STICK_LEFT_X || event.number == JS_AXIS_STICK_LEFT_Y){
                double speed = (double)event.value / 327.68f;
                if (event.number == JS_AXIS_STICK_LEFT_X) {
                    speed *= -1;
                    velocity.y = speed;
                }
                if (event.number == JS_AXIS_STICK_LEFT_Y) {
                    velocity.x = speed;
                }

                if (previousX != event.value * 10 / 32768) {
                    previousX = event.value * 10 / 32768;
                    cout << "previousX " << previousX << endl;
                    PlatformWorker.PushCommand(make_unique<platform::CMoveCommand>(velocity));
                }

                //cout << "Axis " << event.number << " " << speed << endl;
            }
        }));

    JoystickWorker.AddEvent(std::make_shared<vsjoystick::CJoystickButtonEvent>(
        [&PlatformWorker](vsjoystick::joystick_event_t event) {
            cout << "Button " << event.number << " " << (int)event.value << endl;
        }));
    JoystickWorker.Start();
    


#ifdef MQTT_INTERFACE
    vsmqtt::connection_settings_t stConnectionSettings{
    _BuildAddress(
        spConnectionSettings->GetProtocol(),
        spConnectionSettings->GetHost(),
        spConnectionSettings->GetPort()),
    spConnectionSettings->GetUsername(),
    spConnectionSettings->GetPassword()
    };

    vsmqtt::CMQTTWorker MQTTWorker(stConnectionSettings);
    MQTTWorker.PushCommand(make_unique<vsmqtt::CMQTTSubscribeCommand>(
        "velocity",
        [&PlatformWorker](string msg) {
            cout << "velocity:" << msg << endl;
            platform::velocity_t velocity;
            stringstream ss;
            ss << msg;
            ss >> velocity.x >> velocity.y >> velocity.t;
            PlatformWorker.PushCommand(make_unique<platform::CMoveCommand>(velocity));
        }));
#endif // MQTT_INTERFACE



    cout << "Press Enter to Continue" << endl;
    cin.ignore();

#ifdef MQTT_INTERFACE
    MQTTWorker.Stop();
#endif // MQTT_INTERFACE
    JoystickWorker.Stop();
    PlatformWorker.Stop();
    return 0;
}