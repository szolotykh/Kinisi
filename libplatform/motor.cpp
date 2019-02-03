//*************************************************************
//
// File name: motor.cpp
//
//*************************************************************

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <phidget22.h>
#include "motor.h"

namespace
    {
    using namespace std;

    static void CCONV onAttachHandler(PhidgetHandle ph, void *ctx)
        {
        cout<<"onAttachHandler"<<endl;
        }
    static void CCONV onDetachHandler(PhidgetHandle ph, void *ctx)
        {
        cout<<"onDetachHandler"<<endl;   
        }

    static void CCONV onErrorHandler(PhidgetHandle ph, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString)
        {
        stringstream err;
	    err << "[Phidget Error Event] -> "<< errorString <<" ("<<errorCode<<")"<<endl;
        cerr << err.str();
        }

    static void CCONV onVelocityUpdateHandler(PhidgetDCMotorHandle ph, void *ctx, double velocity)
        {
	    //cout << "[Velocity Event] -> Velocity: " << velocity << endl;
        }
    }

namespace platform
    {
    // -------------------------------------------------------------------
    CMotor::CMotor(int serialNumber, int channel)
        : m_DCMotorHandle(0)
        , m_iSerialNumber(serialNumber)
        , m_iChannel(channel)
        , m_Direction(1.0)
        {
        PhidgetDCMotor_create(&m_DCMotorHandle);
        Phidget_setDeviceSerialNumber((PhidgetHandle)m_DCMotorHandle, m_iSerialNumber);
        Phidget_setChannel((PhidgetHandle)m_DCMotorHandle, m_iChannel);
        }

    // -------------------------------------------------------------------
    bool CMotor::Attach(uint32_t timeout)
        {
        // Evens hendlers
        Phidget_setOnAttachHandler((PhidgetHandle)m_DCMotorHandle, onAttachHandler, NULL);
        Phidget_setOnDetachHandler((PhidgetHandle)m_DCMotorHandle, onDetachHandler, NULL);
        Phidget_setOnErrorHandler((PhidgetHandle)m_DCMotorHandle, onErrorHandler, NULL);
        PhidgetDCMotor_setOnVelocityUpdateHandler(m_DCMotorHandle, onVelocityUpdateHandler, NULL);

        PhidgetReturnCode prc;
        prc = Phidget_openWaitForAttachment((PhidgetHandle)m_DCMotorHandle, timeout);
        if (prc != EPHIDGET_OK) {
            // TODO: Report error here
            return false;
        }

        double minVelocity;
        PhidgetDCMotor_getMinVelocity(m_DCMotorHandle, &minVelocity);
        double maxVelocity;
        PhidgetDCMotor_getMaxVelocity(m_DCMotorHandle, &maxVelocity);

        cout << "MinVelocity: " << minVelocity<< endl;
        cout << "MaxVelocity: " << maxVelocity<< endl;

        return true;
        }

    // -------------------------------------------------------------------
    void CMotor::SetVelocity(double speed)
        {
        if (speed > 1.0)
            {
            speed = 1.0;
            }

        if (speed < -1.0)
            {
            speed = -1.0;
            }

        PhidgetReturnCode prc;
        prc = PhidgetDCMotor_setTargetVelocity(m_DCMotorHandle, speed * m_Direction);
        }

    // -------------------------------------------------------------------
    CMotor::~CMotor()
        {
        PhidgetReturnCode prc;
        prc = PhidgetDCMotor_setOnVelocityUpdateHandler(m_DCMotorHandle, NULL, NULL);
        prc = Phidget_close((PhidgetHandle)m_DCMotorHandle);
        prc = PhidgetDCMotor_delete(&m_DCMotorHandle);
        }
    }