//*************************************************************
//
// File name: platformcommands.cpp
//
//*************************************************************

#include "platformcommands.h"

namespace platform
    {
    using namespace std;
    using namespace vscommon;

    CMoveCommand::CMoveCommand(velocity_t velocity)
        :m_velocity(velocity)
        {
        }

    void CMoveCommand::Execute(ICommand::TargetPtr platform)
        {
        static_pointer_cast<IPlatform>(platform)->Move(m_velocity);
        }

    void CStopCommand::Execute(ICommand::TargetPtr platform)
        {
        static_pointer_cast<IPlatform>(platform)->Stop();
        }
    }