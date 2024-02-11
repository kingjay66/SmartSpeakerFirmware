# SmartSpeakerFirmware

Firmware for [SmartSpeaker]() written in C++ using SDL and libcurl.

[SmartSpeaker]() is a fully open source project of bringing a fully hackable and highly customizable smart speaker with lots and lots of features.

## Related Projects

- [SmartSpeaker]() - The SmartSpeaker itself, it's PCBs, housings and design.
- [SmartSpeakerBackend](https://github.com/jayadamsmorgan/SmartSpeakerBackend) - Backend server written in Swift for supporting additional features such as IoT and Voice Assistance.

## Prerequisites

The SmartSpeakerFirmware is intended to be run on a [SmartSpeaker]() which is running lightweight Linux distribution, for now it is supposed to be Armbian Debian.
OS installation steps will be available once the [SmartSpeaker]() is fully designed.

Make sure you have libcurl installed (needed for communication with [SmartSpeakerBackend](https://github.com/jayadamsmorgan/SmartSpeakerBackend)):

```
    sudo apt install libcurl4
```

Install SDL2-ttf library to support fonts:

```
    sudo apt install libsdl-ttf2.0-dev libsdl-ttf2.0-0
```

Clone the repository:

```
    git clone --recurse-submodules https://github.com/jayadamsmorgan/SmartSpeakerFirmware
    cd SmartSpeakerFirmware
```

Compile SDL2 library to work with DirectFB:

```
    cd SDL2
    ./configure --enable-video-directfb --disable-directfb-shared
    sudo make install
    cd ..
```

## Builiding & Running

Run CMake:

```
    cmake . && make
```

The executable is available inside `build` folder (sometimes it also requires `sudo` to run):

```
    ./build/ssf
```

## TODO

- Actual Smart Speaker itself
- Mostly everything else ;)
