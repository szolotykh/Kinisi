//*************************************************************
//
// File name: settings.h
//
//*************************************************************

#ifndef ROBOT_SETTINGS_H
#define ROBOT_SETTINGS_H

#include <memory>
#include <libsettings.h>

namespace robot
    {
    class CConnectionSettings : public vssettings::CPropertyGroup
        {
        public:
            CConnectionSettings()
                {
                AddProperty(vssettings::CProperty("protocol",   vssettings::property_type_t::STRING,    "tcp"));
                AddProperty(vssettings::CProperty("host",       vssettings::property_type_t::STRING,    "localhost"));
                AddProperty(vssettings::CProperty("port",       vssettings::property_type_t::INT,       8883));
                AddProperty(vssettings::CProperty("username",   vssettings::property_type_t::STRING,    "empty"));
                AddProperty(vssettings::CProperty("password",   vssettings::property_type_t::STRING,    ""));
                }

        public:
            std::string GetProtocol(){ return GetProperty("protocol").GetString(); }
            void SetProtocol(const std::string& host){ GetProperty("protocol").SetValue(host);}

            std::string GetHost(){ return GetProperty("host").GetString(); }
            void SetHost(const std::string& host){ GetProperty("host").SetValue(host);}

            int GetPort(){ return GetProperty("port").GetInt(); }
            void SetPort(const std::string& host){ GetProperty("port").SetValue(host); }

            std::string GetUsername(){ return GetProperty("username").GetString(); }
            void SetUsername(const std::string& host){ GetProperty("username").SetValue(host); }

            std::string GetPassword(){ return GetProperty("password").GetString();}
            void SetPassword(const std::string& host){ GetProperty("password").SetValue(host); }
        };

    using CConnectionSettingsPtr = std::shared_ptr<CConnectionSettings>;

    class CRobotSettings : public vssettings::CPropertyGroup
        {
        public:
            CRobotSettings()
                {
                AddProperty(vssettings::CProperty("connection",   vssettings::property_type_t::OBJECT,    std::make_shared<CConnectionSettings>()));
                }

        public:
            CConnectionSettingsPtr GetConnectionSettings(){ return std::static_pointer_cast<CConnectionSettings>(GetProperty("connection").GetPropertyGroup()); }
            void GetConnectionSettings(const CConnectionSettingsPtr group){ GetProperty("connection").SetValue(group);}
        };

    using CRobotSettingsPtr = std::shared_ptr<CRobotSettings>;
    }
#endif