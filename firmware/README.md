<pre>
      _/_/_/                                                    _/            _/_/        _/_/_/    
   _/             _/_/_/  _/_/        _/_/_/      _/  _/_/   _/_/_/_/      _/    _/      _/    _/   
    _/_/         _/    _/    _/    _/    _/      _/_/         _/          _/_/_/_/      _/_/_/      
       _/       _/    _/    _/    _/    _/      _/           _/          _/    _/      _/           
_/_/_/         _/    _/    _/      _/_/_/      _/             _/_/      _/    _/      _/            

	@details
	Necessary tools:
		- GNU Tools for ARM Embedded Processors https://launchpad.net/gcc-arm-embedded/; add bin folder to PATH variable
		- GDB with arm and python support https://yadi.sk/d/inoglwHOP5GHR
		- Yagarto-Tools https://code.google.com/p/csud/downloads/detail?name=yagarto-tools-20121018-setup.exe&can=2&q=  add bin folder to PATH variable
		- OpenOCD http://sourceforge.net/projects/openocd/
	IDE:
		- Qt Creator
			- Enable Bare Metal plugin (Help->About Plugins...->Device Support-> BareMetal)
			- Add GDB debugger (Tools->Options...->Build & Run->Debuggers->Add; Name: GDB ARM; Path: path to gdb-arm-none-eabi.exe)
			- Add GDB server (Tools->Options...->BareMetal->Add->OpenOCD; Startup Mode: Startap in pipe mode; Executable fiel: path to openocd.exe; Configuration file: in board/smartap-vx/openocd.cfg)
			- Add GCC compiler (Tools->Options...->Build & Run->Compilers->Add->GCC; Name: GCC ARM; Path: path to arm-none-eabi-gcc.exe, no flags)
			- Add STM32 device (Tools->Options...->Devices->Add->Bare Metal Device; Name: STM32; GDB server provider: OpenOCD)
			- Add STM32 kit (Tools->Options...->Build & Run->Add; Name: STM32; Device type: Bare Metal Device; Device: STM32; Compiler: GCC ARM; Debugger: GDB ARM; Qt version: none)
			- Open project smartap.creator
			- In project configuration select STM32 kit and delete default. In run configuration: Run on GDB server or hardware debugger and set path to .elf exutable.
			- It's work!
	ChibiOS:
		change in file chibios/os/hal/ports/STM32/LLD/OTGv1/usb_lld.h definitions:
		#define usb_lld_connect_bus(usbp) ((usbp)->otg->GCCFG |= GCCFG_VBUSBSEN)
		and
		#define usb_lld_disconnect_bus(usbp) ((usbp)->otg->GCCFG &= ~GCCFG_VBUSBSEN)
		to
		#define usb_lld_connect_bus(usbp) ((usbp)->otg->GCCFG |= GCCFG_NOVBUSSENS)
		and
		#define usb_lld_disconnect_bus(usbp) ((usbp)->otg->GCCFG &= ~GCCFG_NOVBUSSENS)
		bacause in SmartAP v2 vbus doesn't connected to the PA 9
		
		add u8, u16 .. to \chibios\os\rt\ports\ARMCMx\compilers\RVCT\chtypes.h
	
	Project are consist of two layers. First one is service layer which is divided into three blocks:
	-	system - hardware-undependent block to access general-purpose features
		-	 IO - Input-Output, in fact only output to the system console
		-	 SHELL - system shell module, it process input stream and run commands according it
		-	 SIGNALS
		-	 SENSOR - module to manage sesors, it provides uniform access to the sensor data
		-	 TASK - it provides task management features
		-	 TIME - module contains information about current time (not finished yet)
		-	 FS	- File System module, it only mounts Fat file system and provides simple funcitons to work with FS
		-	 PARAM - module which can save parameters in external memory and read it anter reboot
		-	 LOG - module to write log
	-	driver - external devices driver block
		-	 BUTTONS - detects button press
		-	 LEDS - it lights up/down the led
		-	 PIEZO - piezo buzzer driver
		-	 SD - SD card driver
		-	 MPU9150 - MPU 9150 gyroscope, accelerometer, magnetometer and thermometer driver
		-	 HMC5883 - HMC 5883L magnetometer driver
		-	 MS5611 - MS5611-01BA01 barometer driver
	-	pripheral - hardware-dependent block (this version of SmartAP is for STM32F405/7 family)
		-	 ADC - Analog-to-Digital Converter
		-	 EXTI - EXTernal Interupt module - it detects logical value chnging on the pin
		-	 GPIO - General Purpose Input/Output - it configure pins.
		-	 I2C - Inter-Integrated Circuit - communication module
		-	 RCC - Reset and Clock Control - actually only clock control
		-	 TIM - TIMers control mosule
		-	 USART - Universal Asynchronous Receiver/Transmitter - communication module
		-	 DMA - Direct Memory Access - very useful module, which can sends/receives data withot main proccessor
		-	 SPI - Serial Peripheral Interface - communication module
		-	 CRC - Cyclic Redundancy Check calculation module
		
	Another layer is main flight logic, consist of only one block:
	-	app - block with flight control algorythms
		-	 CONTROL - calculates board action to stabilize and motion
		-	 IMU - Inertial Measurement Unit, module to calculate board attitude
		-	 COMMANDS - it sends commands to the modules
		-	 RADIO - it gets user control through radio channal
		-	 PID - Proportional-Integral-Derivative controller.
		-	 EKF - Extended Kalman Filter
		
	The scheme of application layer (main part):
		╔═════╗ ╔══════════╗ ╔═════╗	╔═══════╗
		║ IMU ║ ║ ALTITUDE ║ ║ NAV ║	║ RADIO	║
		╚══╤══╝ ╚════╤═════╝ ╚══╤══╝	╚═══╤═══╝
		   └─────────┼──────────┘			│
					 │						│
				  position				 control
				   input				  input
					 │						│
					 ▼						▼
				╔═══════════════════════════════╗			╔═════╗
				║			CONTROL				║◄──────────╢ PID ║
				╚══════════════╤════════════════╝			╚═════╝
							   │
							control
							output
							   │
							   ▼
						  ╔════════╗
						  ║ MOTORS ║
						  ╚════════╝

	Also, in this project uses number of libraries:
		-	CMSIS - Cortex Microcontroller Software Interface Standard. It placed in /library and /library/core directories.
		-	SPD - Standard Peripheral Library.
		-	FreeRTOS - for task management in  TASK module. It placed in the /library/freertos directory.
		
Description:
	Each module module consist of two files:
		-	module_name.h - this file is to include module to another one. It should consist of:
			-	doxygen description. In this part describes how to use this module.
			-	list of included modules
			-	defines, which configure the module
			-	module's return values
			-	decloration of module's structures and extern variables
			-	decloration of module's extern functions
		-	module_name.c - this file is to describe functions and variables
	
Editor configuration:
	tab size is 4 character, don't replace it with spaces
	encoding - utf8

				
	

?Main loop function?
</pre>