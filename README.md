# SmartSpeakerFirmware

Firmware for [SmartSpeaker]() written in C++ using SDL and libcurl.

[SmartSpeaker]() is a fully open source project of bringing a fully hackable and highly customizable smart speaker with lots and lots of features.

## Related Projects

 * [SmartSpeaker]() - The SmartSpeaker itself, it's PCBs, housings and design.
 * [SmartSpeakerBackend](https://github.com/jayadamsmorgan/SmartSpeakerBackend) - Backend server written in Swift for supporting additional features such as IoT and Voice Assistance.

## Prerequisites

The SmartSpeakerFirmware is intended to be run on a [SmartSpeaker]() which is running lightweight Linux distribution, for now it is supposed to be Armbian Debian.
OS installation steps will be available once the [SmartSpeaker]() is fully designed. 

Make sure you have libcurl installed (needed for communication with [SmartSpeakerBackend](https://github.com/jayadamsmorgan/SmartSpeakerBackend)):

```
    sudo apt install libcurl4
```

The goal is to get rid of installing SDL2 library too and building the submodule instead (to use the Linux framebuffer directly and run the project without a windowing system) but right now it also needs to be installed:

```
    sudo apt install libsdl2-dev libsdl2-2.0-0 libsdl-ttf2.0-dev libsdl-ttf2.0-0
```

## Builiding & Running

Clone the repository and run CMake:

```
    git clone https://github.com/jayadamsmorgan/SmartSpeakerFirmware
    cd SmartSpeakerFirmware
    cmake . && make
```

The executable is available inside `build` folder (sometimes it also requires `sudo` to run):

```
    ./build/ssf
```

## TODO

* Actual Smart Speaker itself
* Mostly everything else ;)
