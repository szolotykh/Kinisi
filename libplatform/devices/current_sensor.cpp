//*************************************************************
//
// File name: current_sensor.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <phidget22.h>
#include "current_sensor.h"

namespace platform
    {
    using namespace std;

    CCurrentSensor::CCurrentSensor(int serialNumber, int channel)
        : m_SensorHandle(0)
        , m_iSerialNumber(serialNumber)
        , m_iChannel(channel)
        {
        PhidgetCurrentInput_create(&m_SensorHandle);
        Phidget_setDeviceSerialNumber((PhidgetHandle)m_SensorHandle, m_iSerialNumber);
        Phidget_setChannel((PhidgetHandle)m_SensorHandle, m_iChannel);
        }
    

    bool CCurrentSensor::Attach(uint32_t timeout)
        {
        PhidgetReturnCode prc;
        prc = Phidget_openWaitForAttachment((PhidgetHandle)m_SensorHandle, timeout);
        if (prc != EPHIDGET_OK) {
            // TODO: Report error here
            return false;
        }
        return true;
        }

    double CCurrentSensor::GetCurrent()
        {
        double current = 0;
        PhidgetCurrentInput_getCurrent(m_SensorHandle, &current);
        return current;
        }
    
    void CCurrentSensor::SetOnCurrentChange(on_current_change_t callback)
        {
        m_nCurrentChangeCallback = callback;
        PhidgetCurrentInput_setOnCurrentChangeHandler(
            m_SensorHandle, 
            [](PhidgetCurrentInputHandle ch, void *ctx, double current)
                {
                static_cast<CCurrentSensor*>(ctx)->m_nCurrentChangeCallback(current);
                },
            this);
        }


    CCurrentSensor::~CCurrentSensor()
        {
        PhidgetReturnCode prc;
        prc = Phidget_close((PhidgetHandle)m_SensorHandle);
        prc = PhidgetCurrentInput_delete(&m_SensorHandle);
        }
    }