//*************************************************************
//
// File name: platform.cpp
//
//*************************************************************


#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <memory>
#include <phidget22.h>
#include "motor.h"

#include "platform.h"
#include "hwplatform.h"


namespace platform
    {
    using namespace std;

    // -------------------------------------------------------------------
    void CHWPlatform::Build()
        {
        m_FrontLeftMotor = make_unique<CMotor>(FRONT_DC_MC_SERIAL_NUM,   FRONT_LEFT_MOTOR_CHANNEL);
        m_FrontRightMotor = make_unique<CMotor>(FRONT_DC_MC_SERIAL_NUM,   FRONT_RIGHT_MOTOR_CHANNEL);
        m_BackLeftMotor = make_unique<CMotor>(BACK_DC_MC_SERIAL_NUM,    BACK_LEFT_MOTOR_CHANNEL);
        m_BackRightMotor = make_unique<CMotor>(BACK_DC_MC_SERIAL_NUM,    BACK_RIGHT_MOTOR_CHANNEL);

        // Reverse left side motors
        m_FrontLeftMotor->SetReverseDirection();
        m_BackLeftMotor->SetReverseDirection();

        uint32_t timeout = 5000;
        m_FrontLeftMotor->Attach(timeout);
        m_FrontRightMotor->Attach(timeout);
        m_BackLeftMotor->Attach(timeout);
        m_BackRightMotor->Attach(timeout);
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Move(velocity_t v)
        {
        m_FrontLeftMotor->SetVelocity(v.x - v.y - v.t);
		m_FrontRightMotor->SetVelocity(v.x + v.y + v.t);
		m_BackLeftMotor->SetVelocity(v.x + v.y - v.t);
		m_BackRightMotor->SetVelocity(v.x - v.y + v.t);
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Forward (double speed)
        {
        Move({speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Backward (double speed)
        {
        Move({-speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::RotateLeft(double speed)
        {
        Move({0, 0, speed});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::RotateRight(double speed)
        {
        Move({0, 0, -speed});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Left(double speed)
        {
        Move({0, speed, 0});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Right(double speed)
        {
        Move({0, -speed, 0});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Stop()
        {
        Move({0, 0, 0});
        }

    // -------------------------------------------------------------------
    void CHWPlatform::Test()
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
    CHWPlatform::~CHWPlatform()
        {
        Stop();
        }
    }