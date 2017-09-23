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

2. Download and install [GNU ARM Embedded Toolchain](https://launchpad.net/gcc-arm-embedded). Don't put path to `/bin` directory to the `PATH` environment variable.

3. Download and install [MinGW w64](https://sourceforge.net/projects/mingw-w64/) toolchain. Don't put path to `/bin` directory to the `PATH` environment variable.

4. IDE:
	- CLion:
	    - Download and install CLion IDE, set path to the `/bin` directory of MinGW w64 in CLion settings.
	    - Set CMake option `-DTOOLCHAIN_PREFIX="path/to/arm_toolchain"`

5. Git:
    - Setting in terminal "git config --global core.autocrlf true" for correct CRLF handling.
    
#### Unix

1. Install build tools from package manager.

2. Install [CMake](https://cmake.org) from package manager.

3. Install [GNU ARM Embedded Toolchain](https://launchpad.net/gcc-arm-embedded) from package manager. Don't put path to `/bin` directory to the `PATH` environment variable.

4. IDE:
	- CLion:
	    - Download and install CLion IDE.
	    - Set CMake option `-DTOOLCHAIN_PREFIX="path/to/arm_toolchain"`
	    
### Build process

#### Building with IDE.
Just build target `firmware`

#### Building from terminal.

1. Create the building directory:

	`mkdir firmware-build`
	
2. Go to the build directory:
    `cd firmware-build`

3. Run the `cmake` command to configure make files:
    - Windows:
    
	    `"C:\path\to\cmake.exe" -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM="C:\path\to\mingw64\bin\mingw32-make.exe" -DTOOLCHAIN_PREFIX="C:\path\to\arm_toolchain" C:\path\to\firmware\directory`
	    
	- Unix:
	    
        `cmake -DTOOLCHAIN_PREFIX="/path/to/arm_toolchain" /path/to/firmware/directory`
        
4. Run `make` command:
    - Windows:
    
	    `"C:\path\to\mingw64\bin\mingw32-make.exe" firmware`
	
	- Unix:
	
	    `make firmware`

### Firmware load process

#### Loading with IDE.
Just build target `flash`.

#### Loading from terminal.
Run `make flash` command:
- Windows:

    `"C:\path\to\mingw64\bin\mingw32-make.exe" flash`
- Unix:

    `make flash`