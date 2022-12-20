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

#include <fstream>
#include <string>
#include <stdexcept>

#include "ResourceManager.h"
#include "Utils/Logger.h"
#include "Utils/Ini/File.h"
#include "Utils/Ini/Section.h"
#include "Utils/Ini/Writer.h"
#include "Settings.h"
#if defined(__VITA__)
#include <libvf.h>
#endif

namespace VFTerm
{

Settings *Settings::getInstance()
{
  return Base::Singleton<Settings>::get();
}


Settings::Settings()
{
    if (!load())
    {
        save();
    }
}

Settings::~Settings()
{
}

bool Settings::save()
{
    std::string configFile = ResourceManager::getInstance()->getPrefPath("config.ini");
    std::ofstream stream(configFile);

    LOG_DEBUG("Saving config to {}", configFile);

    if (!stream)
    {
        LOG_WARNING("Cannot open config file at `{}`", configFile);
        return false;
    }

    Utils::Ini::File file;

    auto port = file.section("port");
    port->setPropertyInt("baudrate", _bauds[_curbaud]);
    port->setPropertyInt("bits", _bits[_curbits]);
    port->setPropertyInt("stopbits", _stopbits[_curstopbits]);
    port->setPropertyString("parity", _parity[_curparity]);

    auto game = file.section("debug");
    game->setPropertyBool("display_fps", _displayFps);

    Utils::Ini::Writer writer(file);
    writer.write(stream);

    return true;
}


bool Settings::load()
{
    std::string configFile = ResourceManager::getInstance()->getPrefPath("config.ini");
    std::ifstream stream(configFile);

    LOG_DEBUG("Loading config from {}", configFile);

    if (!stream)
    {
        LOG_WARNING("Cannot open config file at `{}`", configFile);
        return false;
    }

    Utils::Ini::Parser parser(stream);
    auto file = parser.parse();

    auto port = file->section("port");
    if (port)
    {
        uint32_t baud = port->propertyInt("baudrate", _bauds[_curbaud]);
        for (int8_t index = 0; index < (int8_t)_bauds.size(); ++index)
        {
            if (_bauds[index] == baud)
            {
                _curbaud = index;
            }
        }

        uint32_t bits = port->propertyInt("bits", _bits[_curbits]);
        for (int8_t index = 0; index < (int8_t)_bits.size(); ++index)
        {
            if (_bits[index] == bits)
            {
                _curbits = index;
            }
        }

        uint32_t stopbits = port->propertyInt("stopbits", _stopbits[_curstopbits]);
        for (int8_t index = 0; index < (int8_t)_stopbits.size(); ++index)
        {
            if (_stopbits[index] == stopbits)
            {
                _curstopbits = index;
            }
        }

        std::string parity = port->propertyString("parity", _parity[_curparity]);
        for (int8_t index = 0; index < (int8_t)_parity.size(); ++index)
        {
            if (_parity[index] == parity)
            {
                _curparity = index;
            }
        }

    }

    auto game = file->section("debug");
    if (game)
    {
        _displayFps = game->propertyBool("display_fps", _displayFps);
    }

    return true;
}

void Settings::apply()
{
    if (_changed)
    {
        save();
        _changed = false;
#if defined(__VITA__)
        libvf_set_baudrate(baud());
        libvf_set_line_property(_curbits == 0 ? BITS_8 : BITS_7, _curstopbits == 0 ? STOP_BIT_1 : STOP_BIT_2, _curparity == 0 ? PARITY_NONE : (_curparity == 1 ? PARITY_ODD : PARITY_EVEN), BREAK_OFF);
        libvf_tcioflush();
#endif
    }
}

bool Settings::changed() const
{
    return _changed;
}

uint32_t Settings::baud() const
{
    return _bauds[_curbaud];
}

void Settings::incbaud()
{
    _curbaud++;
    if (_curbaud > (int8_t)_bauds.size()-1) _curbaud = 0;
    _changed = true;
}

void Settings::decbaud()
{
    _curbaud--;
    if (_curbaud < 0) _curbaud = _bauds.size()-1;
    _changed = true;
}

uint32_t Settings::bits() const
{
    return _bits[_curbits];
}

void Settings::incbits()
{
    _curbits++;
    if (_curbits > (int8_t)_bits.size()-1) _curbits = 0;
    _changed = true;
}

void Settings::decbits()
{
    _curbits--;
    if (_curbits < 0) _curbits = _bits.size()-1;
    _changed = true;
}

uint32_t Settings::stopbits() const
{
    return _stopbits[_curstopbits];
}

void Settings::incstopbits()
{
    _curstopbits++;
    if (_curstopbits > (int8_t)_stopbits.size()-1) _curstopbits = 0;
    _changed = true;
}

void Settings::decstopbits()
{
    _curstopbits--;
    if (_curstopbits < 0) _curstopbits = _stopbits.size()-1;
    _changed = true;
}

std::string& Settings::parity()
{
    return _parity[_curparity];
}

void Settings::incparity()
{
    _curparity++;
    if (_curparity > (int8_t)_parity.size()-1) _curparity = 0;
    _changed = true;
}

void Settings::decparity()
{
    _curparity--;
    if (_curparity < 0) _curparity = _parity.size()-1;
    _changed = true;
}


bool Settings::displayFps() const
{
    return _displayFps;
}

}
