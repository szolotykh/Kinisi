//*************************************************************
//
// File name: platformcommands.cpp
//
//*************************************************************

#include "platformcommands.h"

namespace platform
    {
    CMoveCommand::CMoveCommand(velocity_t velocity)
        :m_velocity(velocity)
        {
        }

    void CMoveCommand::Execute(IPlatformPtr& platform)
        {
        platform->Move(m_velocity);
        }

    void CStopCommand::Execute(IPlatformPtr& platform)
        {
        platform->Stop();
        }
    }