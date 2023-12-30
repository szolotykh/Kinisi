//*************************************************************
//
// File name: controller.h
//
//*************************************************************

#ifndef LIBPLATFORM_CONTROLLER_H
#define LIBPLATFORM_CONTROLLER_H

#include <string>
#include "kinisicommands.h"

namespace platform
{
    class KinisiController : public KinisiCommands
    {
    public:
        KinisiController() = default;
        ~KinisiController();

    public:
        bool connect(std::string port);

        int read(unsigned int lenght);

        int write(unsigned char* cmd, unsigned int size);

    private:
        int m_usb;
    };
}
#endif