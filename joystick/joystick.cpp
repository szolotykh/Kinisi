#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/joystick.h>
#include <string>
#include <sstream>

using namespace std;

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

#define JS_BUTTON_A 0;
#define JS_BUTTON_B 1;
#define JS_BUTTON_X 3;
#define JS_BUTTON_Y 4;
#define JS_BUTTON_STICK_LB 6;
#define JS_BUTTON_STICK_LB 7;
#define JS_BUTTON_VIEW 10;
#define JS_BUTTON_MENU 11;
#define JS_BUTTON_XBOX 12;
#define JS_BUTTON_STICK_LEFT 13;
#define JS_BUTTON_STICK_RIGHT 14;

#define JS_AXIS_STICK_LEFT_X 0
#define JS_AXIS_STICK_LEFT_Y 1
#define JS_AXIS_STICK_RIGHT_X 2
#define JS_AXIS_STICK_RIGHT_Y 3
#define JS_AXIS_RT 4
#define JS_AXIS_LT 5
#define JS_AXIS_DPOD_X 6
#define JS_AXIS_DPOD_Y 7

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

void print_joystick_event(const js_event &e)
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
        return;
    }

    output<< " " << (int)e.number << " " << (int)e.value<<endl;
    cout << output.str();
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

    try
    {
        while(1)
        {
            struct js_event e;
            read (fd, &e, sizeof(e));
            print_joystick_event(e);
        }
    }
    catch(...)
    {
        cout<<"catch"<<endl;
    }

    close(fd);
    return 0;
}
