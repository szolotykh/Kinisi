//*************************************************************
//
// File name: CPhidgetManager.h
//
//*************************************************************

#ifndef PLATFORM_CPHIDGET_MANAGER_H
#define PLATFORM_CPHIDGET_MANAGER_H

#include <phidget22.h>

namespace platform
    {
    class CPhidgetManager
        public:
            CPhidgetManager()
            : m_manager(0)
            {
            }

            ~CPhidgetManager();

        public:
            void Create();
            
        private:
            PhidgetManagerHandle m_manager;
        };
    }

#endif