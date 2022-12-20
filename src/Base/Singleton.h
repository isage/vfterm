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

#ifndef BASE_SINGLETON_H
#define BASE_SINGLETON_H

#include <new>

namespace VFTerm
{
namespace Base
{

template <typename Type>
class Singleton
{
private:
    friend Type* Type::getInstance();

    static Type* get()
    {
        if (!_instance)
        {
            _instance = new Type();
        }

        return _instance;
    }

    static Type* _instance;
};

template <typename Type>
Type* Singleton<Type>::_instance = nullptr;

}
}
#endif //BASE_SINGLETON_H
