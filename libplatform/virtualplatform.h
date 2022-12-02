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
            void Forward (char speed) override;
            void Backward (char speed) override;
            void RotateLeft(char speed) override;
            void RotateRight(char speed) override;
	        void Left(char speed) override;
	        void Right(char speed) override;
	        void Stop() override;
            
        private:

        };
    }

#endif