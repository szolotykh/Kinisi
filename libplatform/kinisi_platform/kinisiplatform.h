//*************************************************************
//
// File name: platform.h
//
//*************************************************************

#ifndef LIBPLATFORM_KINISIPLATFORM_H
#define LIBPLATFORM_KINISIPLATFORM_H

#include <memory>
#include "platform.h"

#define FRONT_DC_MC_SERIAL_NUM  487360
#define BACK_DC_MC_SERIAL_NUM   147360

#define FRONT_LEFT_MOTOR_CHANNEL    0
#define FRONT_RIGHT_MOTOR_CHANNEL   1
#define BACK_LEFT_MOTOR_CHANNEL     0
#define BACK_RIGHT_MOTOR_CHANNEL    1

// Commands
#define INITIALIZE_MOTOR 0x01
#define SET_MOTOR_SPEED 0x02

#define INITIALIZE_ENCODER 0x11
#define GET_ENCODER_VALUE 0x12

// GPIO
#define PIN_LOW 0x20
#define PIN_HIGH 0x21
#define PIN_TOGGLE 0x22

// Status LED
#define STATUS_LED_OFF 0x23
#define STATUS_LED_ON 0x24
#define STATUS_LED_TOGGLE 0x25

// Motor indexes
#define MOTOR_0 0x00
#define MOTOR_1 0x01
#define MOTOR_2 0x02
#define MOTOR_3 0x03

// Encoder indexes
#define ENCODER_0 0x00
#define ENCODER_1 0x01
#define ENCODER_2 0x02
#define ENCODER_3 0x03

namespace platform
    {
    class CKinisiPlatform : public IPlatform
        {
        public:
            CKinisiPlatform() = default;
            ~CKinisiPlatform() override;

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
            void InitMotor(uint8_t motorIndex);
            void SetMotorVelocity(uint8_t motorIndex, double velocity);
        
        private:
            int m_usb;
        };
    }

#endif