//*************************************************************
//
// File name: platform.cpp
//
//*************************************************************
#include <memory>
#include "platform.h"
#include "kinisi_platform/kinisiplatform.h"
#include "virtualplatform.h"

using namespace std;

namespace platform
    {
    IPlatformPtr BuildPlatform(platform_type_t platformType)
        {
        IPlatformPtr upPlatform;
        if(platformType == platform_type_t::REAL)
            {
            upPlatform = make_shared<CKinisiPlatform>();
            }
        else
            {
            upPlatform = make_unique<CVirtualPlatform>();
            }
        return upPlatform;
        }
    }
