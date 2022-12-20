/*
        vfterm
        Copyright (C) 2022 Cat (Ivan Epifanov)

        This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "../Ini/Section.h"
#include "../Logger.h"

namespace VFTerm
{
namespace Utils
{
namespace Ini
{

Section::Section(const std::string &name) : _name(name)
{
}

Section::~Section()
{
}

std::string Section::name()
{
    return _name;
}

void Section::_property(PropertyMapConstIterator iter, double &ret, double def)
{
    if (!_hasType(iter, Value::Tag::DOUBLE))
    {
        ret = def;
        return;
    }

    ret = iter->second._doubleVal;
}

void Section::_property(PropertyMapConstIterator iter, int &ret, int def)
{
    if (!_hasType(iter, Value::Tag::INTEGER))
    {
        ret = def;
        return;
    }

    ret = iter->second._integerVal;
}

void Section::_property(PropertyMapConstIterator iter, bool &ret, bool def)
{
    if (!_hasType(iter, Value::Tag::BOOLEAN))
    {
        ret = def;
        return;
    }

    ret = iter->second._booleanVal;
}

void Section::_property(PropertyMapConstIterator iter, std::string &ret, const std::string &def)
{
    if (!_hasType(iter, Value::Tag::STRING))
    {
        ret = def;
        return;
    }

    ret = iter->second._stringVal;
}

void Section::_property(PropertyMapConstIterator iter, std::vector<Value> &ret)
{
    std::vector<Value> def;
    if (!_hasType(iter, Value::Tag::ARRAY))
    {
        ret = def;
        return;
    }

    ret = iter->second._iniVal;
}

bool Section::_hasType(PropertyMapConstIterator iter, Value::Tag tag)
{
    if (iter->second._tag == tag) return true;
    return false;
}

void Section::setPropertyInt(const std::string &name, int value)
{
    _properties[name] = Value(value);
}

void Section::setPropertyDouble(const std::string &name, double value)
{
    _properties[name] = Value(value);
}

void Section::setPropertyBool(const std::string &name, bool value)
{
    _properties[name] = Value(value);
}

void Section::setPropertyString(const std::string &name, const std::string &value)
{
    _properties[name] = Value(value);
}

void Section::setPropertyArray(const std::string &name, const std::vector<Value> &value)
{
    _properties[name] = Value(value);
}

bool Section::hasProperty(const std::string &name) const
{
    return _properties.find(name) != _properties.end();
}

int Section::propertyInt(const std::string &name, int def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    };
    int ret;
    Section::_property(iter, ret, def);
    return ret;
}

double Section::propertyDouble(const std::string &name, double def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    };
    double ret;
    Section::_property(iter, ret, def);
    return ret;
}

bool Section::propertyBool(const std::string &name, bool def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    };
    bool ret;
    Section::_property(iter, ret, def);
    return ret;
}

std::string Section::propertyString(const std::string &name, const std::string &def)
{
    PropertyMapConstIterator iter = _properties.find(name);
    if (iter == _properties.end())
    {
        return def;
    };
    std::string ret;
    Section::_property(iter, ret, def);
    return ret;
}

std::vector<Value> Section::propertyArray(const std::string &name)
{
    PropertyMapConstIterator iter = _properties.find(name);
    std::vector<Value> def;
    if (iter == _properties.end())
    {
        return def;
    };
    std::vector<Value> ret;
    Section::_property(iter, ret);
    return ret;
}

Section::iterator Section::begin()
{
    return _properties.begin();
}

Section::const_iterator Section::begin() const
{
    return _properties.begin();
}

Section::iterator Section::end()
{
    return _properties.end();
}

Section::const_iterator Section::end() const
{
    return _properties.end();
}

}
}
}
