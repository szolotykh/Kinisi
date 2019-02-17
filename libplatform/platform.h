//*************************************************************
//
// File name: platform.h
//
//*************************************************************

#ifndef LIBPLATFORM_PLATFORM_H
#define LIBPLATFORM_PLATFORM_H

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

    class IPlatform
        {
        public:
            virtual ~IPlatform()
                {
                }

        public:
            virtual void Build() = 0;
            virtual void Test() = 0;

            // Speed and velocity
            
            virtual void Move(velocity_t v) = 0;
            virtual void Forward (double speed) = 0;
            virtual void Backward (double speed) = 0;
            virtual void RotateLeft(double speed) = 0;
            virtual void RotateRight(double speed) = 0;
	        virtual void Left(double speed) = 0;
	        virtual void Right(double speed) = 0;
	        virtual void Stop() = 0;
        };
    }

#endif