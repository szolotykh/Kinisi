//*************************************************************
//
// File name: virtualplatform.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>

#include "platform.h"
#include "virtualplatform.h"


namespace platform
    {
    using namespace std;

    // -------------------------------------------------------------------
    void CVirtualPlatform::Build()
        {
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::Move(velocity_t v)
        {
        stringstream ss;
        ss << "> Front Left Motor. Speed: " << v.x - v.y - v.t << endl;
		ss << "> Front Right Motor. Speed: " << v.x + v.y + v.t << endl;
		ss << "> Back Left Motor. Speed: " << v.x + v.y - v.t << endl;
		ss << "> Back Right Motor. Speed: " << v.x - v.y + v.t << endl;
        cout << ss.str();
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::Forward (char speed)
        {
        cout<<"FORWARD. Speed: " << speed << endl;
        Move({speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::Backward (char speed)
        {
        cout<<"BACKWARD. Speed: " << speed << endl;
        Move({-speed, 0, 0});
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::RotateLeft(char speed)
        {
        cout<<"ROTATE LEFT. Speed: " << speed << endl;
        Move({0, 0, speed});
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::RotateRight(char speed)
        {
        cout << "ROTATE RIGHE. Speed: " << speed << endl;
        Move({0, 0, -speed});
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::Left(char speed)
        {
        cout << "LEFT. Speed: " << speed << endl;
        Move({0, speed, 0});
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::Right(char speed)
        {
        cout << "RIGHE. Speed: " << speed << endl;
        Move({0, -speed, 0});
        }

    // -------------------------------------------------------------------
    void CVirtualPlatform::Stop()
        {
        cout << "STOP." << endl;
        Move({0, 0, 0});
        }

    // -------------------------------------------------------------------
    CVirtualPlatform::~CVirtualPlatform()
        {
        Stop();
        }
    }