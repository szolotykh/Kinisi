//*************************************************************
//
// File name: platformcommands.h
//
//*************************************************************

#ifndef LIBPLATFORM_PLATFORMCOMMANDS_H
#define LIBPLATFORM_PLATFORMCOMMANDS_H

#include <memory>
#include "platform.h"

namespace platform
    {
    class CCommand
        {
        public:
            using Ptr = std::unique_ptr<CCommand>;
        public:
            virtual void Execute(IPlatformPtr& platform) = 0;
        };

    class CMoveCommand : public CCommand
        {
        public:
            CMoveCommand(velocity_t velocity);
            void Execute(IPlatformPtr& platform);

        private:
            velocity_t m_velocity;
        };

    class CStopCommand : public CCommand
        {
        public:
            CStopCommand() = default;
            void Execute(IPlatformPtr& platform);
        };
    }
#endif