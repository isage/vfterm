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

#ifndef STATE_TERMINAL_H
#define STATE_TERMINAL_H

#include "../State/State.h"
#include <list>

namespace VFTerm
{
    namespace State
    {
        class Terminal : public State
        {
            public:
                Terminal();
                ~Terminal() override;

                void think(uint32_t delta) override;
                void init() override;
                void render() override;
                void onKeyDown(Event::Keyboard* event) override;
                void onButtonDown(Event::Gamepad* event) override;

                void onTextInput(Event::Text* event) override;
                void onStateDeactivate(Event::State* event) override;

            private:
                std::list<std::pair<uint8_t, std::string>> _buffer;
                int _offset = 0;
                const char* _cr = "\r\n";
        };
    }
}
#endif // STATE_TERMINAL_H
