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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "Base/Singleton.h"

namespace VFTerm
{

class Settings
{
public:
    static Settings *getInstance();


    bool save();
    bool load();

    bool changed() const;
    bool displayFps() const;

    uint32_t baud() const;
    void incbaud();
    void decbaud();

    uint32_t bits() const;
    void incbits();
    void decbits();

    uint32_t stopbits() const;
    void incstopbits();
    void decstopbits();

    std::string& parity();
    void incparity();
    void decparity();

    void apply();

protected:
    friend class Base::Singleton<Settings>;
    Settings();
    ~Settings();

    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;

private:
    bool _changed = true; // for startup

    bool _displayFps = false;

    // [port]
    std::vector<uint32_t> _bauds = {115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 600, 300 };
    std::vector<uint32_t> _bits = {8, 7};
    std::vector<uint32_t> _stopbits = {1, 2};
    std::vector<std::string> _parity = {"NONE", "ODD", "EVEN"};

    int8_t _curbaud = 0;
    int8_t _curbits = 0;
    int8_t _curparity = 0;
    int8_t _curstopbits = 0;
};

} // VFTerm

#endif // SETTINGS_H
