//*************************************************************
//
// File name: libsettings.cpp
//
//*************************************************************
#include <iostream>
#include <fstream>
#include <streambuf>
#include <json11.hpp>

#include "settings.h"

using namespace std;
using namespace json11;

namespace
    {
    using namespace vssettings;
    
    void JsonToPropertyGroup(const Json& josn, CPropertyGroupPtr propertyGroup)
        {
        for(auto it = propertyGroup->begin(); it != propertyGroup->end(); it++)
            {
            auto& property = *it;

            // Check if propery in a json. if not set to default value.
            if(josn[property.GetName()] == Json())
                {
                property.SetValue(property.GetDefaultValue()); 
                }

            switch(property.GetType())
                {
                case property_type_t::STRING:
                    if (josn[property.GetName()].is_string())
                        {
                        property.SetValue(josn[property.GetName()].string_value());
                        }
                    else
                        {
                        property.SetValue(property.GetDefaultValue());
                        }
                    break;
                case property_type_t::INT:
                    if (josn[property.GetName()].is_number())
                        {
                        property.SetValue(josn[property.GetName()].int_value());
                        }
                    else
                        {
                        property.SetValue(property.GetDefaultValue());    
                        }
                        break;
                    case property_type_t::OBJECT:
                    if (josn[property.GetName()].is_object())
                        {
                        CPropertyGroupPtr spGroup = property.GetPropertyGroup();
                        JsonToPropertyGroup(josn[property.GetName()], spGroup);
                        }
                        break;
                default:
                    property.SetValue(property.GetDefaultValue());
                }
            }
        }

    bool _ReadFile(const std::string& fileName, std::string& strFile)
        {
        std::ifstream inputFile(fileName);

        if(!inputFile.is_open())
            return false;

        inputFile.seekg(0, std::ios::end);   
        strFile.reserve(inputFile.tellg());
        inputFile.seekg(0, std::ios::beg);

        strFile.assign((std::istreambuf_iterator<char>(inputFile)),
                    std::istreambuf_iterator<char>());

        return true;
        }
    }

namespace vssettings
    {
    bool LoadSettings(const std::string& fileName, CPropertyGroup group)
        {
        std::string strFile;
        if (!_ReadFile(fileName, strFile))
        {
            return false;
        }

        std::string err;
        json11::Json settings = json11::Json::parse(strFile, err);
        if (!err.empty())
        {
            return false;
        }

        if(settings.is_object())
            {
            JsonToPropertyGroup(settings, make_shared<CPropertyGroup>(group));
            }
        return true;
        }
    }