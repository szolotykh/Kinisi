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
            void Forward (double speed) override;
            void Backward (double speed) override;
            void RotateLeft(double speed) override;
            void RotateRight(double speed) override;
	        void Left(double speed) override;
	        void Right(double speed) override;
	        void Stop() override;
            
        private:

        };
    }

#endif