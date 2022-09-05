//*************************************************************
//
// File name: platform.h
//
//*************************************************************

#ifndef LIBPLATFORM_HWPLATFORM_H
#define LIBPLATFORM_HWPLATFORM_H

#include <phidget22.h>
#include <memory>
#include <motor.h>
#include "platform.h"

#define FRONT_DC_MC_SERIAL_NUM  487360
#define BACK_DC_MC_SERIAL_NUM   147360

#define FRONT_LEFT_MOTOR_CHANNEL    0
#define FRONT_RIGHT_MOTOR_CHANNEL   1
#define BACK_LEFT_MOTOR_CHANNEL     0
#define BACK_RIGHT_MOTOR_CHANNEL    1

namespace platform
    {
    class CHWPlatform : public IPlatform
        {
        public:
            CHWPlatform() = default;
            ~CHWPlatform() override;

        public:
            void Build() override;
            void Test();

            // Speed and velocity
            
            void Move(velocity_t v) override;
            void Forward (double speed) override;
            void Backward (double speed) override;
            void RotateLeft(double speed) override;
            void RotateRight(double speed) override;
	        void Left(double speed) override;
	        void Right(double speed) override;
	        void Stop() override;
            
        private:
            CMotor::Ptr m_FrontLeftMotor;
            CMotor::Ptr m_FrontRightMotor;
            CMotor::Ptr m_BackLeftMotor;
            CMotor::Ptr m_BackRightMotor;
        };
    }

#endif