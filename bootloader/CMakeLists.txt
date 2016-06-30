cmake_minimum_required( VERSION 2.8 )

set(CMAKE_TOOLCHAIN_FILE ../library/tools/cmake/toolchain.cmake)

project( bootloader )
enable_language(ASM)
set(ASM arm-none-eabi-gcc)

set( BOARD servo-1 )

set( SOURCES
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../firmware/system/Terminal.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../firmware/system/Telemetry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../firmware/system/Thread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../firmware/driver/Flash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../firmware/system/usbcfg.c
	${CMAKE_CURRENT_SOURCE_DIR}/../firmware/board/${BOARD}/board.c
)
set( INCLUDE
	${CMAKE_CURRENT_SOURCE_DIR}/../firmware/system/include
	${CMAKE_CURRENT_SOURCE_DIR}/../firmware/driver/include
	${CMAKE_CURRENT_SOURCE_DIR}/../firmware/board/${BOARD}
)
include( ../library/chibios.cmake )

set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--script=\"${CMAKE_CURRENT_SOURCE_DIR}/../firmware/board/${BOARD}/STM32F405xG_bootloader.ld\"" )
add_definitions(-DCORTEX_VTOR_INIT=BOARD_FLASH_BOOTLOADER)


include_directories( ${INCLUDE} )
add_executable( ${PROJECT_NAME}.elf ${SOURCES} )
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_FILESIZE} ARGS ${PROJECT_NAME}.elf)
add_custom_target(Flash "C:/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe" "-c SWD -Rst -P \"${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex\" -Rst -Run")
