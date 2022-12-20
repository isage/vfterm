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

#include "../State/Settings.h"

#include <ctime>
#include <string>
#include <vector>
#include <memory>

#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../Utils/Logger.h"
#include "../State/FadeOut.h"
#include "../State/Exit.h"
#include "../State/DeviceWaiting.h"


using namespace VFTerm::Graphics;

namespace VFTerm
{
    namespace State
    {
        Settings::Settings() : State()
        {
        }

        Settings::~Settings()
        {
        }

        void Settings::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);
        }

        void Settings::think(uint32_t delta)
        {
            State::think(delta);
        }

        void Settings::render()
        {
            int pzx = (Renderer::getInstance()->screenWidth / 2) - (243/2);

            Renderer::getInstance()->fillRect(pzx, 116, pzx+243, 116+144, VGA_COLORS[1]);
            Renderer::getInstance()->font.draw(pzx, 116+16*0, "╔═══════ SETTINGS ════════╗", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*1, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*2, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*3, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*4, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*5, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*6, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*7, "║                         ║", VGA_COLORS[0x1F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*8, "╚═════════════════════════╝", VGA_COLORS[0x1F]);

            Renderer::getInstance()->font.draw(pzx+27, 116+16*1, "Baud:", _menuPos == 0 ? VGA_COLORS[0x04] : VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+27, 116+16*2, "Bits:", _menuPos == 1 ? VGA_COLORS[0x04] : VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+27, 116+16*3, "Parity:", _menuPos == 2 ? VGA_COLORS[0x04] : VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+27, 116+16*4, "Stop bits:", _menuPos == 3 ? VGA_COLORS[0x04] : VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+27, 116+16*6, "APPLY", _menuPos == 4 ? VGA_COLORS[0x04] : VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+27, 116+16*7, "CANCEL", _menuPos == 5 ? VGA_COLORS[0x04] : VGA_COLORS[0x0F]);

            switch (_menuPos)
            {
              case 0:
              default:
                Renderer::getInstance()->font.draw(pzx+9, 116+16*1, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+144, 116+16*1, "\x11", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+225, 116+16*1, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->fillRect(pzx+144+18, 116+16*1, pzx+144+72, 116+16*2, VGA_COLORS[0x09]);
                break;
              case 1:
                Renderer::getInstance()->font.draw(pzx+9, 116+16*2, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+144, 116+16*2, "\x11", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+225, 116+16*2, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->fillRect(pzx+144+18, 116+16*2, pzx+144+72, 116+16*3, VGA_COLORS[0x09]);
                break;
              case 2:
                Renderer::getInstance()->font.draw(pzx+9, 116+16*3, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+144, 116+16*3, "\x11", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+225, 116+16*3, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->fillRect(pzx+144+18, 116+16*3, pzx+144+72, 116+16*4, VGA_COLORS[0x09]);
                break;
              case 3:
                Renderer::getInstance()->font.draw(pzx+9, 116+16*4, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+144, 116+16*4, "\x11", VGA_COLORS[0x0F]);
                Renderer::getInstance()->font.draw(pzx+225, 116+16*4, "\x10", VGA_COLORS[0x0F]);
                Renderer::getInstance()->fillRect(pzx+144+18, 116+16*4, pzx+144+72, 116+16*5, VGA_COLORS[0x09]);
                break;
              case 4:
                Renderer::getInstance()->font.draw(pzx+9, 116+16*6, "\x10", VGA_COLORS[0x0F]);
                break;
              case 5:
                Renderer::getInstance()->font.draw(pzx+9, 116+16*7, "\x10", VGA_COLORS[0x0F]);
                break;
            }

            std::string baud = fmt::format("{:>6}", ::VFTerm::Settings::getInstance()->baud());
            std::string bits = fmt::format("{}", ::VFTerm::Settings::getInstance()->bits());
            std::string parity = fmt::format("{:>4}", ::VFTerm::Settings::getInstance()->parity());
            std::string stopbits = fmt::format("{}", ::VFTerm::Settings::getInstance()->stopbits());
            Renderer::getInstance()->font.draw(pzx+162, 116+16*1, baud, VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+207, 116+16*2, bits, VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+180, 116+16*3, parity, VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+207, 116+16*4, stopbits, VGA_COLORS[0x0F]);
        }

        void Settings::onKeyDown(Event::Keyboard* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->keyCode())
            {
                case SDLK_z:
                    switch(_menuPos)
                    {
                        case 4:
                          ::VFTerm::Settings::getInstance()->apply();
                          game->popState();
                          break;
                        case 5:
                          game->popState();
                          break;
                    }
                    break;
                case SDLK_DOWN:
                    _menuPos++;
                    if (_menuPos > 5) _menuPos = 0;
                    break;
                case SDLK_UP:
                    _menuPos--;
                    if (_menuPos <0) _menuPos = 5;
                    break;
                case SDLK_LEFT:
                    switch(_menuPos)
                    {
                        case 0:
                            ::VFTerm::Settings::getInstance()->incbaud();
                            break;
                        case 1:
                            ::VFTerm::Settings::getInstance()->incbits();
                            break;
                        case 2:
                            ::VFTerm::Settings::getInstance()->incparity();
                            break;
                        case 3:
                            ::VFTerm::Settings::getInstance()->incstopbits();
                            break;
                    }
                    break;
                case SDLK_RIGHT:
                    switch(_menuPos)
                    {
                        case 0:
                            ::VFTerm::Settings::getInstance()->decbaud();
                        break;
                        case 1:
                            ::VFTerm::Settings::getInstance()->decbits();
                        break;
                        case 2:
                            ::VFTerm::Settings::getInstance()->decparity();
                        break;
                        case 3:
                            ::VFTerm::Settings::getInstance()->decstopbits();
                        break;
                    }
                    break;
                default:
                  break;
            }
        }

        void Settings::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_A:
                    switch(_menuPos)
                    {
                        case 4:
                          ::VFTerm::Settings::getInstance()->apply();
                          game->popState();
                          break;
                        case 5:
                          game->popState();
                          break;
                    }
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    _menuPos++;
                    if (_menuPos > 5) _menuPos = 0;
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    _menuPos--;
                    if (_menuPos < 0) _menuPos = 5;
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    switch(_menuPos)
                    {
                        case 0:
                            ::VFTerm::Settings::getInstance()->incbaud();
                            break;
                        case 1:
                            ::VFTerm::Settings::getInstance()->incbits();
                            break;
                        case 2:
                            ::VFTerm::Settings::getInstance()->incparity();
                            break;
                        case 3:
                            ::VFTerm::Settings::getInstance()->incstopbits();
                            break;
                    }
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                    switch(_menuPos)
                    {
                        case 0:
                            ::VFTerm::Settings::getInstance()->decbaud();
                        break;
                        case 1:
                            ::VFTerm::Settings::getInstance()->decbits();
                        break;
                        case 2:
                            ::VFTerm::Settings::getInstance()->decparity();
                        break;
                        case 3:
                            ::VFTerm::Settings::getInstance()->decstopbits();
                        break;
                    }
                    break;
                default:
                  break;
            }
        }

    }
}
