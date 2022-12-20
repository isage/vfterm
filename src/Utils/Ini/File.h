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

#ifndef INI_FILE_H
#define INI_FILE_H

#include <fstream>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <algorithm>

#include "../Ini/Parser.h"
#include "../Ini/Section.h"


namespace VFTerm
{
namespace Utils
{

namespace Ini
{

class File
{
public:
    using iterator = std::map<std::string, std::shared_ptr<Section>>::iterator;
    using const_iterator = std::map<std::string, std::shared_ptr<Section>>::const_iterator;

    File();
    ~File();
    std::shared_ptr<Section> section(const std::string &name);
    std::map<std::string, std::shared_ptr<Section>>* sections();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    bool hasSection(const std::string &name) const;

private:
    std::map<std::string, std::shared_ptr<Section>> _sections;

};

}
}
}
#endif	// INI_FILE_H
