//*************************************************************
//
// File name: platform.cpp
//
//*************************************************************
#include <memory>
#include "platform.h"
#include "hwplatform.h"
#include "virtualplatform.h"

using namespace std;

namespace platform
    {
    IPlatformPtr BuildPlatform(platform_type_t platformType)
        {
        IPlatformPtr upPlatform;
        if(platformType == platform_type_t::REAL)
            {
            upPlatform = make_unique<CHWPlatform>();
            }
        else
            {
            upPlatform = make_unique<CVirtualPlatform>();
            }
        upPlatform->Build();
        return upPlatform;
        }
    }
