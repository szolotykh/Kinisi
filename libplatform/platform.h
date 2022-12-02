//*************************************************************
//
// File name: platform.h
//
//*************************************************************

#ifndef LIBPLATFORM_PLATFORM_H
#define LIBPLATFORM_PLATFORM_H

#include <memory>

namespace platform
    {
    enum platform_type_t
        {
        REAL,
        VIRTUAL
        };
    
    struct velocity_t
        {
        velocity_t()
        : x(0)
        , y(0)
        , t(0)
        {
        }

        velocity_t (char _x, char _y, char _t)
        : x(_x)
        , y(_y)
        , t(_t)
        {
        }

        double x;
        double y;
        double t;
        };

    class IPlatform
        {
        public:
            virtual ~IPlatform()
                {
                }

        public:
            virtual void Build() = 0;

            // Speed and velocity
            virtual void Move(velocity_t v) = 0;
            virtual void Forward (char speed) = 0;
            virtual void Backward (char speed) = 0;
            virtual void RotateLeft(char speed) = 0;
            virtual void RotateRight(char speed) = 0;
	        virtual void Left(char speed) = 0;
	        virtual void Right(char speed) = 0;
	        virtual void Stop() = 0;
        };

    using IPlatformPtr = std::shared_ptr<IPlatform>;
    IPlatformPtr BuildPlatform(platform_type_t platformType);
    }

#endif