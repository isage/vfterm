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

#ifndef INI_SECTION_H
#define INI_SECTION_H

#include <map>
#include <string>
#include <vector>

#include "../Ini/Value.h"

namespace VFTerm
{
namespace Utils
{
namespace Ini
{

class Section
{
public:
    using PropertyMap = std::map<std::string, Value>;
    using PropertyMapConstIterator = PropertyMap::const_iterator;
    using iterator = PropertyMap::iterator;
    using const_iterator = PropertyMap::const_iterator;

    Section(const std::string &name);
    ~Section();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    std::string name();

    int propertyInt(const std::string &name, int def);

    double propertyDouble(const std::string &name, double def);

    bool propertyBool(const std::string &name, bool def);

    std::string propertyString(const std::string &name, const std::string &def);

    std::vector<Value> propertyArray(const std::string &name);

    void setPropertyInt(const std::string &name, int value);

    void setPropertyDouble(const std::string &name, double value);

    void setPropertyBool(const std::string &name, bool value);

    void setPropertyString(const std::string &name, const std::string &value);

    void setPropertyArray(const std::string &name, const std::vector<Value> &value);

    bool hasProperty(const std::string &name) const;

private:

    PropertyMap _properties;
    std::string _name;

    static void _property(PropertyMapConstIterator iter, double &ret, double def);

    static void _property(PropertyMapConstIterator iter, int &ret, int def);

    static void _property(PropertyMapConstIterator iter, bool &ret, bool def);

    static void _property(PropertyMapConstIterator iter, std::string &ret, const std::string &def);

    static void _property(PropertyMapConstIterator iter, std::vector<Value> &ret);

    static bool _hasType(PropertyMapConstIterator iter, Value::Tag tag);

};

}
}
}
#endif // INI_SECTION_H
