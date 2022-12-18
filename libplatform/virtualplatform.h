//*************************************************************
//
// File name: virtualplatform.h
//
//*************************************************************

#ifndef LIBPLATFORM_VIRTUALPLATFORM_H
#define LIBPLATFORM_VIRTUALPLATFORM_H

#include "platform.h"

namespace platform
    {
    class CVirtualPlatform : public IPlatform
        {
        public:
            CVirtualPlatform() = default;
            ~CVirtualPlatform() override;

        public:
            void Build() override;

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

        };
    }

#endif