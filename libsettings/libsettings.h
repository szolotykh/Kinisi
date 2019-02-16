//*************************************************************
//
// File name: libsettings.h
//
//*************************************************************

#ifndef LIBSETTINGS_LIBSETTINGS_H
#define LIBSETTINGS_LIBSETTINGS_H

#include <string>
#include <variant>
#include <memory>
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
    using CPropertyGroupPtr = std::shared_ptr<CPropertyGroup>;


    bool LoadSettings(const std::string& fileName, CPropertyGroup group);

    class CProperty
        {
        public:
            using property_value_t = std::variant<std::string, int, CPropertyGroupPtr>;

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
            CPropertyGroupPtr GetPropertyGroup() {return std::get<CPropertyGroupPtr>(m_value);}

        private:
            std::string m_name;
            property_type_t m_type;
            property_value_t m_default_value;
            property_value_t m_value;
        };

    class CPropertyGroup : public std::iterator<
                        std::input_iterator_tag,   // iterator_category
                        CProperty,                      // value_type
                        CProperty,                      // difference_type
                        const CProperty*,               // pointer
                        CProperty>                       // reference
        {
        public:
            using property_map_t = std::unordered_map<std::string, CProperty>;

        public:
            CPropertyGroup() = default;

        public:
            class iterator: public std::iterator<
                                std::input_iterator_tag,   // iterator_category
                                CProperty,                      // value_type
                                CProperty,                      // difference_type
                                const CProperty*,               // pointer
                                CProperty&>                       // reference
                {
                public:
                    explicit iterator(property_map_t::iterator _it) : m_it(_it) {}
                    iterator& operator++() {m_it++; return *this;}
                    iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
                    bool operator==(iterator other) const {return m_it == other.m_it;}
                    bool operator!=(iterator other) const {return !(*this == other);}
                    reference operator*() const {return m_it->second;}
                
                private:
                    property_map_t::iterator m_it;
                };
                iterator begin() {return iterator(m_propertyMap.begin());}
                iterator end() {return iterator(m_propertyMap.end());}

        protected:
            void AddProperty(const CProperty& property)
                {
                m_propertyMap.insert({property.GetName(), property});
                }
            CProperty GetProperty(const std::string& name) {return m_propertyMap[name];}

        private:
            property_map_t m_propertyMap;
        };
    }

#endif