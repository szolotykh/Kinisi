//*************************************************************
//
// File name: command_manager.c
//
//*************************************************************

#ifndef LIBCOMMON_COMMANDS_H
#define LIBCOMMON_COMMANDS_H

#include <memory>

namespace vscommon
    {
    class ICommand
        {
        public:
            using Ptr = std::unique_ptr<ICommand>;
            using TargetPtr = std::shared_ptr<void>;
            
        public:
            virtual void Execute(TargetPtr target) = 0;
        };
    }

#endif