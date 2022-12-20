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

#ifndef INI_VALUE_H
#define INI_VALUE_H

#include <string>
#include <iosfwd>
#include <vector>

namespace VFTerm
{
namespace Utils
{
namespace Ini
{

class Value
{
public:
    enum class Tag
    {
        DOUBLE,
        INTEGER,
        BOOLEAN,
        STRING,
        ARRAY
    };

    Value();
    Value(double doubleVal);
    Value(int integerVal);
    Value(bool booleanVal);
    Value(const std::string& stringVal);
    Value(const Value &rhs);
    Value(std::vector<Value> iniVal);
    ~Value();

    Value & operator=(const Value &rhs);

    Value::Tag tag() const;
    static std::string tagString(Value::Tag tag);
    std::string value() const;
    int intValue() const;
    bool boolValue() const;
    double doubleValue() const;

    friend class Section;
private:
    Tag _tag;

    union
    {
        double _doubleVal;
        int _integerVal;
        bool _booleanVal;
        std::string _stringVal;
        std::vector<Value> _iniVal;
    };
};

}
}
}
#endif // INI_VALUE_H
