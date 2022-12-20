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

#ifndef STATE_SETTINGS_H
#define STATE_SETTINGS_H

#include "../State/State.h"

namespace VFTerm
{
    namespace State
    {
        class Settings : public State
        {
            public:
                Settings();
                ~Settings() override;

                void think(uint32_t delta) override;
                void init() override;
                void render() override;
                void onKeyDown(Event::Keyboard* event) override;
                void onButtonDown(Event::Gamepad* event) override;

            protected:
                int8_t _menuPos = 0;
                std::vector<uint32_t> _parity = {0, 1, 2};
                int8_t _curParity = 0;
        };
    }
}
#endif // STATE_SETTINGS_H
