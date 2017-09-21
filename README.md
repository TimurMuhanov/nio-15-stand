# NIO-15


### Project structure:
- 3rdparty
	- ChibiOS - Realtime embedded operation system.
	- stm32-cmake - cmake toolchain files.
- documentation - documentation for hardware.
- firmware - source code for hardware

## Firmware

### Build environment preparation

#### Windows

1. Download and install [CMake](https://cmake.org). Don't put path to `/bin` directory to the `PATH` environment variable.

1. Download and install [GNU ARM Embedded Toolchain](https://launchpad.net/gcc-arm-embedded). Don't put path to `/bin` directory to the `PATH` environment variable.

2. Download and install [MinGW w64](https://sourceforge.net/projects/mingw-w64/) toolchain. Don't put path to `/bin` directory to the `PATH` environment variable.

3. IDE:
	- CLion:
	    - Download and install CLion IDE, set path to the `/bin` directory of MinGW w64 in CLion settings.
	    - Set CMake option `-DTOOLCHAIN_PREFIX="path/to/arm_toolchain"`

4. Git:
    - Setting in terminal "git config --global core.autocrlf true" for correct CRLF handling.


### Build process

#### Building with IDE.
Just build target `firmware.hex` or `firmware.bin`

#### Building from terminal.

1. Create the building directory:

	`mkdir firmware-build`

2. Run the `cmake` command with `MinGW Makefiles` as parameter:

	`C:\path\to\cmake.exe -G "MinGW Makefiles" -DTOOLCHAIN_PREFIX="path/to/arm_toolchain" C:\path\to\firmware\directory`

3. Run `make` command:

	`C:\path\to\mingw64\bin\mingw32-make.exe`


