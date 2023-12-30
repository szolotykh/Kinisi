//*************************************************************
//
// File name: platform.h
//
//*************************************************************

#ifndef LIBPLATFORM_KINISIPLATFORM_H
#define LIBPLATFORM_KINISIPLATFORM_H

#include <memory>
#include <vector>
#include "platform.h"
#include "controller.h"


namespace platform
    {
    class CKinisiPlatform : public IPlatform
        {
        public:
            CKinisiPlatform() = default;
            ~CKinisiPlatform() override;

        public:
            bool Start() override;
            void Test();

            // Speed and velocity
            
            void Move(velocity_t v) override;
            void Forward (int speed) override;
            void Backward (int speed) override;
            void RotateLeft(int speed) override;
            void RotateRight(int speed) override;
	        void Left(int speed) override;
	        void Right(int speed) override;
	        void Stop() override;

        private:
            void InitPlatform();
            void SetVelocityInput(velocity_t v);

        private:
            void WriteMessage(std::vector<unsigned char>& msg);

        private:
            KinisiController controller;
        };
    }

#endif