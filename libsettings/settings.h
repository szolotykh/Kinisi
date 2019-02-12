//*************************************************************
//
// File name: settings.h
//
//*************************************************************

#ifndef ROBOT_SETTINGS_H
#define ROBOT_SETTINGS_H

#include <string>
#include <variant>
#include <unordered_map>

namespace vssettings
    {
    enum property_type_t
        {
        STRING,
        NUM,
        INT,
        ARRAY,
        OBJECT
        };

    class CPropertyGroup;
    class CProperty
        {
        public:
            using property_value_t = std::variant<std::string, int>;

        public:
            CProperty() = default;

            CProperty(const std::string& name, property_type_t type, property_value_t defaultValue)
            : m_name(name)
            , m_type(type)
            , m_default_value(defaultValue)
            , m_value(defaultValue)
            {
            }             

        public:
            std::string GetName() const {return m_name;}
            property_type_t GetType() const {return m_type;}
            property_value_t GetDefaultValue() const {return m_default_value;}

            void SetValue(property_value_t value){m_value = value;}
            property_value_t GetValue() const {return m_value;}

            std::string GetString() const {return std::get<std::string>(m_value);}
            int GetInt() const {return std::get<int>(m_value);}

        private:
            std::string m_name;
            property_type_t m_type;
            property_value_t m_default_value;
            property_value_t m_value;
        };

    class CPropertyGroup
        {
        public:
            CPropertyGroup() = default;
        
        public:
            bool ReadFile(const std::string& fileName, std::string& strFile);
            bool LoadSettings(const std::string& fileName);

        protected:
            void AddProperty(const CProperty& property)
                {
                m_propertyMap.insert({property.GetName(), property});
                }
            CProperty GetProperty(const std::string& name) {return m_propertyMap[name];}

        private:
            std::unordered_map<std::string, CProperty> m_propertyMap;
        };
    }

#endif