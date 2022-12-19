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

        velocity_t (int _x, int _y, int _t)
        : x(_x)
        , y(_y)
        , t(_t)
        {
        }

        int x;
        int y;
        int t;
        };

    class IPlatform
        {
        public:
            virtual ~IPlatform()
                {
                }

        public:
            virtual bool Start() = 0;

            // Speed and velocity
            virtual void Move(velocity_t v) = 0;
            virtual void Forward (int speed) = 0;
            virtual void Backward (int speed) = 0;
            virtual void RotateLeft(int speed) = 0;
            virtual void RotateRight(int speed) = 0;
	        virtual void Left(int speed) = 0;
	        virtual void Right(int speed) = 0;
	        virtual void Stop() = 0;
        };

    using IPlatformPtr = std::shared_ptr<IPlatform>;
    IPlatformPtr BuildPlatform(platform_type_t platformType);
    }

#endif