# vfterm - PSVita serial terminal

PSVita app for communicating via serial protocol through FTDI adapters.

## Building

* Install [libvf](https://github.com/isage/libvf)
* `mkdir build && cmake -DCMAKE_BUILD_TYPE=Release -DPLATFORM=vita .. && make`

## Usage

* Install `libvf.skprx`, install app.
* Run, connect FTDI dongle via powered Y-cable.
* Set up port parameters in settings and connect rs232 side to target device.

## License

GPLv3, see LICENSE.md
