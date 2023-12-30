//*************************************************************
//
// File name: controller.cpp
//
//*************************************************************

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <memory>
#include <fcntl.h>
#include <cerrno>
#include <iostream>
#include <stdio.h>
#include "platform.h"
#include "controller.h"
#include "kinisicommands.h"
#include <string>
#include <termios.h>
#include <assert.h>
#include <cstring>

namespace platform
{
    using namespace std;

    bool KinisiController::connect(string port) {
        m_usb = open(port.c_str(), O_RDWR | O_NOCTTY);
        cout << "> m_usb: " << m_usb << endl;
        if (m_usb == -1)
        {
            return false;
        }

        struct termios tty;

        memset(&tty, 0, sizeof tty);
        /* Error Handling */
        if (tcgetattr(m_usb, &tty) != 0)
        {
            std::cout << "> Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
        }

        /* Set Baud Rate */
        cfsetospeed(&tty, (speed_t)B115200);
        cfsetispeed(&tty, (speed_t)B115200);

        /* Setting other Port Stuff */
        tty.c_cflag &= ~PARENB;            // Make 8n1
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;

        tty.c_cflag &= ~CRTSCTS;           // no flow control
        //tty.c_cc[VMIN] = 1;                  // read doesn't block
        //tty.c_cc[VTIME] = 10;                  // 0.5 seconds read timeout
        //tty.c_cflag |= CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

        /* Make raw */
        cfmakeraw(&tty);

        /* Flush Port, then applies attributes */
        tcflush(m_usb, TCIFLUSH);
        if (tcsetattr(m_usb, TCSANOW, &tty) != 0)
        {
            std::cout << "> Error " << errno << " from tcsetattr" << std::endl;
        }

        return true;
    }

    // -------------------------------------------------------------------
    int KinisiController::read(unsigned int lenght) {
        int result = 0;
        ::read(m_usb, (char*)&result, lenght);
        return 0;
    }

    // -------------------------------------------------------------------
    int KinisiController::write(unsigned char* cmd, unsigned int size)
    {
        return ::write(m_usb, cmd, size);
    }

    KinisiController::~KinisiController()
    {
        close(m_usb);
    }

}