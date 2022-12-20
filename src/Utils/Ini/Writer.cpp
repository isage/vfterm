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

#include "../Ini/Writer.h"

#include "../Ini/File.h"

namespace VFTerm
{
namespace Utils
{
namespace Ini
{

Writer::Writer(const File &ini) : _ini(ini)
{
}

Writer::~Writer()
{
}

void Writer::write(std::ostream &stream)
{
    stream << "# This file contains default configuration for the vfterm." << std::endl;

    for (auto &section : _ini)
    {
        stream << "[" << section.first << "]" << std::endl;

        for (auto &properties : *section.second)
        {
            stream << properties.first <<  "=" << properties.second.value() << std::endl;
        }

        stream << std::endl;
    }
}

}
}
}
