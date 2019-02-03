//*************************************************************
//
// File name: CPhidgetManager.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <phidget22.h>
#include "CPhidgetManager.h"

namespace
    {
    using namespace std;

    void CCONV _AttachHandlerManagerHandle(PhidgetManagerHandle manager, void *userptr, PhidgetHandle device)
        {
        int serialNumber;
        const char *name;

        Phidget_getDeviceName(device, &name);
        Phidget_getDeviceSerialNumber(device, &serialNumber);

        cout<<"Hello Device"<<name<<", Serial Number:" <<serialNumber<<endl;

        return;
        }

    void CCONV _DetachHandlerManagerHandle(PhidgetManagerHandle manager, void *userptr, PhidgetHandle device)
        {
        int serialNumber;
        const char *name;
        Phidget_getDeviceName(device, &name);
        Phidget_getDeviceSerialNumber(device, &serialNumber);
        cout<<"Goodbye Device"<<name<<"Serial Number: " << serialNumber<<endl;
        return;
        }
    }

namespace platform
    {
    void CPhidgetManager::Create()
        {
        PhidgetManager_create(&manager);
        PhidgetManager_setOnAttachHandler(manager, _AttachHandlerManagerHandle, NULL);
        PhidgetManager_setOnDetachHandler(manager, _DetachHandlerManagerHandle, NULL);
        PhidgetManager_open(manager);
        }

    CPhidgetManager::~CPhidgetManager()
        {
        PhidgetManager_close(manager);
        PhidgetManager_delete(&manager);
        }
    }