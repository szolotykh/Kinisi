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
#include "controller.h"
#include <string.h>
#include <termios.h>
#include <assert.h>
#include <vector>

#define SPEED_RESOLUTION 840

namespace platform
{
    using namespace std;

    // -------------------------------------------------------------------
    bool CKinisiPlatform::Start()
    {
        if (!controller.connect("/dev/ttyACM0"))
        {
            return false;
        }

        InitPlatform();
        return true;
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::InitPlatform()
    {
        controller.initialize_omni_platform(false, false, false, 1, 1);
        cout << "Omni platform initialized" << endl;
    }

    // -------------------------------------------------------------------
    void CKinisiPlatform::SetVelocityInput(velocity_t v)
    {
        //assert(v.x <= 100 || v.x >= -100);
        //assert(v.y <= 100 || v.y >= -100);
        //assert(v.t <= 100 || v.t >= -100);

        /*
        std::vector<unsigned char> msg { 
            PLATFORM_SET_VELOCITY_INPUT, 
            static_cast<unsigned char>(v.x),
            static_cast<unsigned char>(v.y),
            static_cast<unsigned char>(v.t)};
        WriteMessage(msg);
        */

        controller.set_platform_velocity_input(
            static_cast<int8_t>(v.x),
            static_cast<int8_t>(v.y),
            static_cast<int8_t>(v.t));
        cout << "SetVelocityInput: " << v.x << ", " << v.y << ", " << v.t << endl;
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

    }
}