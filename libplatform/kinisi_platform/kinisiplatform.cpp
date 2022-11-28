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

        InitMotor(0);
        InitMotor(1);
        InitMotor(2);
        InitMotor(3);
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::InitMotor(uint8_t motorIndex)
    {
        unsigned char initCmd[] = { INITIALIZE_MOTOR, motorIndex };
        int n_written = write(m_usb, initCmd, sizeof(initCmd));
        std::this_thread::sleep_for(0.5s);
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::SetMotorVelocity(uint8_t motorIndex, double velocity)
    {
        bool direction = velocity >= 0;
        uint16_t speed = abs(velocity) / 100 * SPEED_RESOLUTION;
        unsigned char M0Cmd[] = { SET_MOTOR_SPEED, motorIndex, direction, speed, speed >> 8 };
        int n_written = write(m_usb, M0Cmd, sizeof(M0Cmd));
    } 

    // -------------------------------------------------------------------
    void CKinisiPlatform::Move(velocity_t v)
    {
        //cout << "Velocity: " << v.x << " " << v.y << " " << v.t << endl;
        //unsigned char command[] = { STATUS_LED_TOGGLE };
        //int n_written = write(m_usb, command, sizeof(command));


        SetMotorVelocity(3, (v.x - v.y - v.t));
        SetMotorVelocity(0, (v.x + v.y + v.t));
        SetMotorVelocity(2, (v.x + v.y - v.t));
        SetMotorVelocity(1, (v.x - v.y + v.t));

        //m_FrontLeftMotor->SetVelocity(v.x - v.y - v.t);
		//m_FrontRightMotor->SetVelocity(v.x + v.y + v.t);
		//m_BackLeftMotor->SetVelocity(v.x + v.y - v.t);
		//m_BackRightMotor->SetVelocity(v.x - v.y + v.t);
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Forward (double speed)
        {
        Move({speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Backward (double speed)
        {
        Move({-speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::RotateLeft(double speed)
        {
        Move({0, 0, speed});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::RotateRight(double speed)
        {
        Move({0, 0, -speed});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Left(double speed)
        {
        Move({0, speed, 0});
        }

    // -------------------------------------------------------------------
    void CKinisiPlatform::Right(double speed)
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