//*************************************************************
//
// File name: motor.h
//
//*************************************************************

#ifndef PLATFORM_MOTOR_H
#define PLATFORM_MOTOR_H

#include <phidget22.h>
#include <memory>

namespace platform
    {
    class CMotor
        {
        public:
            using Ptr = std::unique_ptr<CMotor>;

        public:
            CMotor(int serialNumber, int channel);
            virtual ~CMotor();

        public:
            bool Attach(uint32_t timeout = 5000);

            // Set target speed for the motor
            void SetVelocity(double speed);

            // Motor direction
            void SetNormalDirection() { m_Direction = 1.0; }
            void SetReverseDirection() { m_Direction = -1.0; }
            bool GetDirection() const { return m_Direction; }

        private:
            PhidgetDCMotorHandle m_DCMotorHandle;
            int m_iChannel;
            int m_iSerialNumber;
            double m_Direction;
        };
    }

#endif