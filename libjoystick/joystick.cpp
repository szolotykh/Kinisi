#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/joystick.h>
#include <string>
#include <sstream>

#include "mqttworker.h"
#include "settings.h"
#include "joystick.h"


using namespace std;
using namespace robot;

namespace
{
    string _BuildAddress(string protocol, string host, int port)
    {
        return protocol + "://" + host + ":" + to_string(port);
    }
}

void print_joystick_info(int fd) {
    int axes = 0;
    int buttons = 0;
    char name[128];
    ioctl(fd, JSIOCGAXES, &axes);
    ioctl(fd, JSIOCGBUTTONS, &buttons);
    ioctl(fd, JSIOCGNAME(sizeof(name)), &name);

    cout << name << endl;
    cout<< "Axes: " << axes << endl;
    cout<< "Buttons: " << buttons << endl;
}

string joystick_event_str(const js_event &e)
{
    stringstream output;

    uint8_t etype = e.type;
    if (etype & JS_EVENT_INIT)
        {
            output << "INIT ";
            etype &= ~JS_EVENT_INIT; 
        }

    if (etype == JS_EVENT_BUTTON)
    {
        output << "Button";
    }
    else if(etype == JS_EVENT_AXIS)
    {
        output << "Axes";
    }
    else
    {
        return "";
    }

    output<< " " << (int)e.number << " " << (int)e.value<<endl;
    return output.str();
}

int main()
{
    cout<<"Joystick"<<endl;

    int fd = open ("/dev/input/js0", O_RDONLY);
    if(fd < 0)
    {
        cout << "Joystick is not connected." << endl;
        return 0;
    }

    print_joystick_info(fd);

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

    try
    {
        while(1)
        {
            struct js_event e;
            read (fd, &e, sizeof(e));
            string message = joystick_event_str(e);
            cout << message;

            MQTTWorker.PushCommand(make_unique<vsmqtt::CMQTTPublishCommand>("joystick", message));
        }
    }
    catch(...)
    {
        cout<<"catch"<<endl;
    }

    close(fd);
    return 0;
}
