//*************************************************************
//
// File name: platform.cpp
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
#include "kinisiplatform.h"
#include <string.h>
#include <termios.h>
#include <assert.h>

#define SPEED_RESOLUTION 840

namespace platform
{
    using namespace std;

    // -------------------------------------------------------------------
    void CKinisiPlatform::Build()
    {
        m_usb = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
        cout << "> m_usb: " << m_usb << endl;
        
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

        InitPlatform();
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::InitPlatform()
    {
        unsigned char initCmd[] = { PLATFORM_INITIALIZE };
        int n_written = write(m_usb, initCmd, sizeof(initCmd));
        std::this_thread::sleep_for(0.5s);
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::SetVelocityInput(velocity_t v)
    {
        //assert(v.x <= 100 || v.x >= -100);
        //assert(v.y <= 100 || v.y >= -100);
        //assert(v.t <= 100 || v.t >= -100);

        unsigned char cmd[] = { PLATFORM_SET_VELOCITY_INPUT, v.x, v.y, v.t};
        int n_written = write(m_usb, cmd, sizeof(cmd));
    } 

    // -------------------------------------------------------------------
    void CKinisiPlatform::Move(velocity_t v)
    {
        //cout << "Velocity: " << v.x << " " << v.y << " " << v.t << endl;
        //unsigned char command[] = { STATUS_LED_TOGGLE };
        //int n_written = write(m_usb, command, sizeof(command));

        SetVelocityInput(v);

        //m_FrontLeftMotor->SetVelocity(v.x - v.y - v.t);
		//m_FrontRightMotor->SetVelocity(v.x + v.y + v.t);
		//m_BackLeftMotor->SetVelocity(v.x + v.y - v.t);
		//m_BackRightMotor->SetVelocity(v.x - v.y + v.t);
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Forward (int speed)
        {
        Move({speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Backward (int speed)
        {
        Move({-speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::RotateLeft(int speed)
        {
        Move({0, 0, speed});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::RotateRight(int speed)
        {
        Move({0, 0, -speed});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Left(int speed)
        {
        Move({0, speed, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Right(int speed)
        {
        Move({0, -speed, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Stop()
        {
        Move({0, 0, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Test()
    {
        Forward (1.0);
        std::this_thread::sleep_for(5s);

        Backward (1.0);
        std::this_thread::sleep_for(5s);

        RotateLeft(1.0);
        std::this_thread::sleep_for(5s);

        RotateRight(1.0);
        std::this_thread::sleep_for(5s);

	    Left(1.0);
        std::this_thread::sleep_for(5s);

	    Right(1.0);
        std::this_thread::sleep_for(5s);

	    Stop();
    }

    // -------------------------------------------------------------------
    CKinisiPlatform::~CKinisiPlatform()
    {
        close(m_usb);
    }
}