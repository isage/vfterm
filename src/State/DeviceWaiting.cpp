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

#include "../State/DeviceWaiting.h"

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
#include "../State/Terminal.h"

#if defined(__VITA__)
#include <libvf.h>
#endif

using namespace VFTerm::Graphics;

namespace VFTerm
{
    namespace State
    {
        DeviceWaiting::DeviceWaiting() : State()
        {
        }

        DeviceWaiting::~DeviceWaiting()
        {
        }

        void DeviceWaiting::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);
#if defined(__VITA__)
            libvf_start();
#endif
        }

        void DeviceWaiting::think(uint32_t delta)
        {
            auto game = Game::Game::getInstance();
            State::think(delta);

#if defined(__VITA__)
            if (libvf_has_ftdi())
                game->setState(new Terminal());
#else
            INC_PER_DELTA(_timer);
            if (_timer > 60.)
            {
                game->setState(new Terminal());
            }
#endif
        }

        void DeviceWaiting::render()
        {
            Renderer::getInstance()->clearScreen(VGA_COLORS[0x08]);
            Renderer::getInstance()->fillRect(0, 0, Renderer::getInstance()->screenWidth, 16, VGA_COLORS[0x1F]);

            Renderer::getInstance()->fillRect(0, Renderer::getInstance()->screenHeight-16, Renderer::getInstance()->screenWidth, Renderer::getInstance()->screenHeight, VGA_COLORS[0x1F]);

            int pzx = (Renderer::getInstance()->screenWidth / 2) - (212/2);

            Renderer::getInstance()->fillRect(pzx, 116, pzx+212, 116+64, VGA_COLORS[1]);
            Renderer::getInstance()->font.draw(pzx, 116+16*0, "╔═══════Waiting════════╗", VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*1, "║                      ║", VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*2, "║                      ║", VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx, 116+16*3, "╚══════════════════════╝", VGA_COLORS[0x0F]);

            Renderer::getInstance()->font.draw(pzx+48, 116+16*1, "Please connect", VGA_COLORS[0x0F]);
            Renderer::getInstance()->font.draw(pzx+80, 116+16*2, "device", VGA_COLORS[0x0F]);

            Renderer::getInstance()->font.draw(4, 0, "V", VGA_COLORS[0x04]);
            Renderer::getInstance()->font.draw(12, 0, "iTA FTDI TERMINAL v0.1", VGA_COLORS[0x15]);

            Renderer::getInstance()->font.draw(4, Renderer::getInstance()->screenHeight-16, "W", VGA_COLORS[0x04]);
            Renderer::getInstance()->font.draw(12, Renderer::getInstance()->screenHeight-16, "aiting for device...", VGA_COLORS[0x15]);
        }

        void DeviceWaiting::onKeyDown(Event::Keyboard* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->keyCode())
            {
                case SDLK_z:
                    game->pushState(new FadeOut(new Start()));
                    break;
                default:
                  break;
            }
        }

        void DeviceWaiting::onButtonDown(Event::Gamepad* event)
        {
            auto game = Game::Game::getInstance();

            switch (event->button())
            {
                case SDL_CONTROLLER_BUTTON_B:
                    game->pushState(new FadeOut(new Start()));
                    break;
                default:
                  break;
            }
        }

    }
}
