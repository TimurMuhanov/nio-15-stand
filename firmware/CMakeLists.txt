cmake_minimum_required( VERSION 2.8 )

set(CMAKE_TOOLCHAIN_FILE ../library/tools/cmake/toolchain.cmake)

project( firmware )
enable_language(ASM)
set(ASM arm-none-eabi-gcc)

set( BOARD servo-1 )

set( SOURCES
	main.c
	app/imu.c
	app/encoder.c
	app/servo.c
	app/user_func_RBF_127_150819.c
	system/control.c
	system/gcs.c
	system/io.c
	system/usbcfg.c
	system/parameter.cpp
	driver/led.c
	driver/ls7366.c
	driver/adis16488.c
	board/${BOARD}/board.c
)
set( INCLUDE
	app/include
	system/include
	driver/include
	board/${BOARD}
	../library/mavlink
	../library/mavlink/nio15_1
)
include( ../library/chibios.cmake )

set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--script=\"${CMAKE_CURRENT_SOURCE_DIR}/board/${BOARD}/STM32F405xG.ld\"" )


include_directories( ${INCLUDE} )
add_executable( ${PROJECT_NAME}.elf ${SOURCES} )
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_FILESIZE} ARGS ${PROJECT_NAME}.elf)
add_custom_target(Flash "C:/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe" "-c SWD -Rst -P \"${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex\" -Rst -Run")
