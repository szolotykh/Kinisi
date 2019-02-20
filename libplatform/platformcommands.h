//*************************************************************
//
// File name: platformcommands.h
//
//*************************************************************

#ifndef LIBPLATFORM_PLATFORMCOMMANDS_H
#define LIBPLATFORM_PLATFORMCOMMANDS_H

#include <memory>
#include "commands.h"
#include "platform.h"

namespace platform
    {
    class CMoveCommand : public vscommon::ICommand
        {
        public:
            CMoveCommand(velocity_t velocity);
            void Execute(vscommon::ICommand::TargetPtr platform);

        private:
            velocity_t m_velocity;
        };

    class CStopCommand : public vscommon::ICommand
        {
        public:
            CStopCommand() = default;
            void Execute(vscommon::ICommand::TargetPtr platform);
        };
    }
#endif