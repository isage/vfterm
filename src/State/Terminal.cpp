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

#include "../State/Terminal.h"

#include <ctime>
#include <string>
#include <vector>
#include <memory>

#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../Utils/Logger.h"
#include "../State/Start.h"
#include "../State/FadeOut.h"
#include "../State/Settings.h"

#if defined(__VITA__)
#include <libvf.h>
#endif

using namespace VFTerm::Graphics;

namespace VFTerm
{
    namespace State
    {
        Terminal::Terminal() : State()
        {
        }

        Terminal::~Terminal()
        {
        }

        void Terminal::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);
            ::VFTerm::Settings::getInstance()->apply();

        }

        void Terminal::think(uint32_t delta)
        {
//            auto game = Game::Game::getInstance();
            State::think(delta);

            // receive and output
#if defined(__VITA__)
            unsigned char ch;
            int cnt = libvf_read_data(&ch,1);
            if (cnt > 0)
            {
                if (_buffer.size() == 0 || _buffer.back().first == 1)
                {
                    _buffer.push_back({0, ""});
                }
                if (ch == 13 || ch == 10)
                {
                    _buffer.push_back({0, ""});
                } else
                {
                    _buffer.back().second += ch;
                }
            }
#endif
            while (_buffer.size() > 512)
            {
                _buffer.pop_front();
            }


        }

        void Terminal::render()
        {
            Renderer::getInstance()->clearScreen(VGA_COLORS[0x11]);
            Renderer::getInstance()->fillRect(0, 0, Renderer::getInstance()->screenWidth, 16, VGA_COLORS[0x1F]);

            Renderer::getInstance()->fillRect(0, Renderer::getInstance()->screenHeight-16, Renderer::getInstance()->screenWidth, Renderer::getInstance()->screenHeight, VGA_COLORS[0x1F]);

            Renderer::getInstance()->fillRect(0, 16, 9, Renderer::getInstance()->screenHeight-16, VGA_COLORS[0x1F]);


            Renderer::getInstance()->font.draw(4, 0, "V", VGA_COLORS[0x04]);
            Renderer::getInstance()->font.draw(12, 0, "iTA FTDI TERMINAL v0.1", VGA_COLORS[0x15]);

            std::string settings_text = fmt::format("{} {}-{}-{}", ::VFTerm::Settings::getInstance()->baud(), ::VFTerm::Settings::getInstance()->bits(), ::VFTerm::Settings::getInstance()->parity(), ::VFTerm::Settings::getInstance()->stopbits());
            Renderer::getInstance()->font.draw(4, Renderer::getInstance()->screenHeight-16, settings_text, VGA_COLORS[0x15]);


            Renderer::getInstance()->font.draw(560-4, Renderer::getInstance()->screenHeight-16, "│", VGA_COLORS[0x15]);
            Renderer::getInstance()->font.draw(560+4, Renderer::getInstance()->screenHeight-16, "x", VGA_COLORS[0x09]);
            Renderer::getInstance()->font.draw(560+12, Renderer::getInstance()->screenHeight-16, " - input text ,", VGA_COLORS[0x15]);

            Renderer::getInstance()->font.draw(560+152, Renderer::getInstance()->screenHeight-16, "o", VGA_COLORS[0x0C]);
            Renderer::getInstance()->font.draw(560+160, Renderer::getInstance()->screenHeight-16, " - exit ,", VGA_COLORS[0x15]);

            Renderer::getInstance()->font.draw(560+250, Renderer::getInstance()->screenHeight-16, "\x1e", VGA_COLORS[0x02]);
            Renderer::getInstance()->font.draw(560+258, Renderer::getInstance()->screenHeight-16, " - settings", VGA_COLORS[0x15]);

            if (_buffer.size() > 0)
            {
                int line = 0;
                auto begin = std::next(_buffer.rbegin(), _offset);

                for (auto linepair = begin; linepair != _buffer.rend(); ++linepair)
                {
                    Renderer::getInstance()->font.draw(2,  16+16*(31-line), (*linepair).first == 0 ? "\x11" : "\x10", VGA_COLORS[0x10]);
                    Renderer::getInstance()->font.draw(12, 16+16*(31-line), (*linepair).second, VGA_COLORS[0x0f]);
                    line++;
                    if (line >= 32) break;
                }
            }

        }

        void Terminal::onKeyDown(Event::Keyboard* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->keyCode())
            {
                case SDLK_x:
                    game->pushState(new FadeOut(new Start()));
                    break;
                case SDLK_c:
                    game->pushState(new Settings());
                    break;
                case SDLK_z:
                    SDL_StartTextInput();
                    break;
                case SDLK_UP:
                    _offset++;
                    if (_offset > _buffer.size() - 1 ) _offset = _buffer.size() -1;
                    break;
                case SDLK_DOWN:
                    _offset--;
                    if (_offset < 0 ) _offset = 0;
                    break;
                case SDLK_RETURN:
#if defined(__VITA__)
                    libvf_write_data((const unsigned char*)_cr, 2);
#else
                    _buffer.push_back({1, ""});
#endif
                    break;
                default:
                  break;
            }
        }

        void Terminal::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_Y:
                    game->pushState(new Settings());
                    break;
                case SDL_CONTROLLER_BUTTON_B:
                    game->pushState(new FadeOut(new Start()));
                    break;
                case SDL_CONTROLLER_BUTTON_A:
                    SDL_StartTextInput();
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    _offset++;
                    if (_offset > _buffer.size() - 1 ) _offset = _buffer.size() -1;
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    _offset--;
                    if (_offset < 0 ) _offset = 0;
                    break;
                default:
                  break;
            }
        }

        void Terminal::onTextInput(Event::Text* event)
        {
#if defined(__VITA__)
            _buffer.push_back({1, event->text()});

            while (_buffer.size() > 512)
            {
                _buffer.pop_front();
            }
            SDL_StopTextInput();
            libvf_write_data((const unsigned char*)event->text().c_str(), event->text().length());
#else
            if (_buffer.size() == 0)
            {
                _buffer.push_back({1, ""});
            }
            _buffer.back().second += event->text();
#endif

        }

        void Terminal::onStateDeactivate(Event::State* event)
        {
#if defined(__VITA__)
            libvf_stop();
#endif
        }


    }
}
