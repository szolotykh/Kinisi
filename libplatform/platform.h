//*************************************************************
//
// File name: platform.h
//
//*************************************************************

#ifndef ROBOT_PLATFORM_H
#define ROBOT_PLATFORM_H

#include <phidget22.h>
#include <memory>
#include <motor.h>

#define FRONT_DC_MC_SERIAL_NUM  487360
#define BACK_DC_MC_SERIAL_NUM   147360

#define FRONT_LEFT_MOTOR_CHANNEL    0
#define FRONT_RIGHT_MOTOR_CHANNEL   1
#define BACK_LEFT_MOTOR_CHANNEL     0
#define BACK_RIGHT_MOTOR_CHANNEL    1

namespace platform
    {
    struct velocity_t
        {
        velocity_t()
        : x(0)
        , y(0)
        , t(0)
        {
        }

        velocity_t (double _x, double _y, double _t)
        : x(_x)
        , y(_y)
        , t(_t)
        {
        }

        double x;
        double y;
        double t;
        };

    class CPlatform
        {
        public:
            CPlatform()
            {
            }

            virtual ~CPlatform();

        public:
            void Build();
            void Test();

            // Speed and velocity
            
            void Move(velocity_t v);
            void Forward (double speed);
            void Backward (double speed);
            void RotateLeft(double speed);
            void RotateRight(double speed);
	        void Left(double speed);
	        void Right(double speed);
	        void Stop();
            
        private:
            CMotor::Ptr m_FrontLeftMotor;
            CMotor::Ptr m_FrontRightMotor;
            CMotor::Ptr m_BackLeftMotor;
            CMotor::Ptr m_BackRightMotor;
        };
    }

#endif