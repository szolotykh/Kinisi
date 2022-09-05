//*************************************************************
//
// File name: current_sensor.h
//
//*************************************************************

#ifndef PLATFORM_CURRENT_SENSOR_H
#define PLATFORM_CURRENT_SENSOR_H

#include <phidget22.h>
#include <memory>
#include <functional>

namespace platform
    {
    class CCurrentSensor
        {
        public:
            using Ptr = std::unique_ptr<CCurrentSensor>;
            using on_current_change_t = std::function<void(double)>;

        public:
            CCurrentSensor(int serialNumber, int channel);
            virtual ~CCurrentSensor();

        public:
            bool Attach(uint32_t timeout = 5000);
            double GetCurrent();
            void SetOnCurrentChange(on_current_change_t callback);

        private:
            PhidgetCurrentInputHandle m_SensorHandle;
            int m_iChannel;
            int m_iSerialNumber;
            on_current_change_t m_nCurrentChangeCallback;
        };
    }

#endif