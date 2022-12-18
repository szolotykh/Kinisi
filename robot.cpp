#include <iostream>
#include <memory>
#include "mqttworker.h"
#include "platformworker.h"
#include "joystickworker.h"
#include "settings.h"
#include <sstream> 
#include <joystick.h>
#include "util.h"

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

    bool isStopping = false;
    
    CRobotSettings Settings;
    vssettings::LoadSettings("settings.json", Settings);

    auto spConnectionSettings = Settings.GetConnectionSettings();

    platform::platform_settings_t stPlatformSettings;
    platform::CPlatformWorker PlatformWorker(stPlatformSettings);

    platform::velocity_t velocity;
    std::mutex VelocityUpdateMutex;

    vsjoystick::CJoystickWorker JoystickWorker(vsjoystick::settings_t{ port:JOYSTICK_PORT });
    JoystickWorker.AddEvent(std::make_shared<vsjoystick::CJoystickAxisEvent>(
        [&PlatformWorker, &velocity, &VelocityUpdateMutex](vsjoystick::joystick_event_t event)
        {
            switch (event.number)
            {
                case JS_AXIS_STICK_LEFT_X:
                {
                lock_guard<mutex> lockGuard(VelocityUpdateMutex);
                int speed = (double)event.value / 327.68f;
                velocity.t = -speed;
                }
                break;

            case JS_AXIS_STICK_LEFT_Y:
                {
                lock_guard<mutex> lockGuard(VelocityUpdateMutex);
                int speed = (double)event.value / 327.68f;
                velocity.x = speed;
                }
                break;

            case JS_AXIS_STICK_RIGHT_X:
                {
                lock_guard<mutex> lockGuard(VelocityUpdateMutex);
                int speed = (double)event.value / 327.68f;
                velocity.y = speed;
                }
                break;

                //cout << "Axis " << event.number << " " << (int)speed << endl;
                //cout << "event.value " << event.number << " " << (int)event.value << endl;

            default:
                break;
            }
        }));

    JoystickWorker.AddEvent(std::make_shared<vsjoystick::CJoystickButtonEvent>(
        [&PlatformWorker, &isStopping](vsjoystick::joystick_event_t event) {
            //cout << "Button " << event.number << " " << (int)event.value << endl;
            if (event.number == 11 && event.value == 1) {
                isStopping = true;
                cout << "Stopping.";
            }
        }));
    JoystickWorker.Start();
    
    // Velocity publisher (100ms interval)
    vsutil::CTimerInterval VelocityUpdater([&PlatformWorker, &velocity, &VelocityUpdateMutex](){
            lock_guard<mutex> lockGuard(VelocityUpdateMutex);
            PlatformWorker.PushCommand(make_unique<platform::CMoveCommand>(velocity));
        },
        100);

    while (!isStopping) {
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }

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


#ifdef MQTT_INTERFACE
    MQTTWorker.Stop();
#endif // MQTT_INTERFACE
    VelocityUpdater.Stop();
    JoystickWorker.Stop();
    PlatformWorker.Stop();
    return 0;
}