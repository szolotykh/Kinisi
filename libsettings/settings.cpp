//*************************************************************
//
// File name: settings.cpp
//
//*************************************************************
#include <iostream>
#include <fstream>
#include <streambuf>
#include <json11.hpp>

#include "settings.h"


namespace vssettings
    {
    using namespace std;
    using namespace json11;
    
    bool CPropertyGroup::ReadFile(const std::string& fileName, std::string& strFile)
        {
        std::ifstream inputFile(fileName);

        inputFile.seekg(0, std::ios::end);   
        strFile.reserve(inputFile.tellg());
        inputFile.seekg(0, std::ios::beg);

        strFile.assign((std::istreambuf_iterator<char>(inputFile)),
                    std::istreambuf_iterator<char>());

        return true;
        }

    bool CPropertyGroup::LoadSettings(const std::string& fileName)
        {
        string strFile;
        ReadFile(fileName, strFile);

        string err;
        Json settings = Json::parse(strFile, err);

        if(settings.is_object())
            {
            for(auto it = m_propertyMap.begin(); it != m_propertyMap.end(); it++)
                {
                auto& property = it->second;

                // Check if propery in a json. if not set to default value.
                if(settings[property.GetName()] == Json())
                    {
                    property.SetValue(property.GetDefaultValue()); 
                    }

                switch(property.GetType())
                    {
                    case property_type_t::STRING:
                        if (settings[property.GetName()].is_string())
                            {
                            property.SetValue(settings[property.GetName()].string_value());
                            }
                        else
                            {
                            property.SetValue(property.GetDefaultValue());
                            }
                        break;
                    case property_type_t::INT:
                        if (settings[property.GetName()].is_number())
                            {
                            property.SetValue(settings[property.GetName()].int_value());
                            }
                        else
                            {
                            property.SetValue(property.GetDefaultValue());    
                            }
                            break;
                    default:
                        property.SetValue(property.GetDefaultValue());
                    }
                }
            }
        return true;
        }
    }