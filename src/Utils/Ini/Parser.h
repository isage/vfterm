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

#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <memory>
#include <string>
#include <vector>

namespace VFTerm
{
namespace Utils
{
namespace Ini
{

class File;
class Value;

class Parser
{
public:
    Parser(std::istream &stream);
    ~Parser();

    std::shared_ptr<File> parse();

private:
    std::istream &_stream;
    std::string  _section;

protected:
    void _trim(std::string &line);

    void _rtrim(std::string &line);

    void _ltrim(std::string &line);

    void _toLower(std::string &line);

    bool _tryBool(std::string &line, bool* val);

    int _tryDecimal(std::string &line, int* intval, double* doubleval);

    bool _parseBool(std::string &name, std::string &line, std::shared_ptr<File> ini);

    bool _parseDecimal(std::string &name, std::string &line, std::shared_ptr<File> ini);

    bool _parseArray(std::string &name, std::string &line, std::shared_ptr<File> ini);

    bool _parseArrayDecimal(std::vector<Value> &vec, std::string val);
    bool _parseArrayBool(std::vector<Value> &vec, std::string val);

};

}
}
}
#endif // INI_PARSER_H
