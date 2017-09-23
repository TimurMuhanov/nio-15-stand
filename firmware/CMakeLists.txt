cmake_minimum_required( VERSION 2.8 )

set(BOARDNAME NoNameChina_STM32F103)

#set(STM32_CHIP STM32F415RG)

include(./board/${BOARDNAME}/board.cmake)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/stm32-cmake/cmake/gcc_stm32.cmake)

project( firmware )
enable_language( ASM )

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")

set(CHIBIOS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/ChibiOS)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/stm32-cmake/cmake)

FIND_PACKAGE(ChibiOS 3 COMPONENTS rt pal hal serial REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} test.cpp ${BOARD_SOURCES} ${ChibiOS_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${ChibiOS_INCLUDE_DIRS} ${BOARD_INCLUDE_DIRS})

set(STM32_LINKER_SCRIPT ${ChibiOS_LINKER_SCRIPT})

set(EXECUTABLE_NAME ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})

configure_file(./configs/gdb/gdb_load.txt.in ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.txt)

add_custom_target(flash COMMAND ${TOOLCHAIN_PREFIX}/bin/arm-none-eabi-gdb -x ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.txt DEPENDS ${CMAKE_PROJECT_NAME})

STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})

STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})

#
#set( BOARD servo-1 )
#
#set( SOURCES
#    main.cpp
#    app/Imu.cpp
#    app/Encoder.cpp
#    app/Servo.cpp
#    app/user_func_RBF_127_150819.cpp
#    system/Terminal.cpp
#    system/Telemetry.cpp
#    system/FileSystem.cpp
#    system/Log.cpp
#    system/Settings.cpp
#    system/Thread.cpp
#    system/Control.cpp
#    system/Connection.cpp
#    system/PubSub.cpp
#    system/usbcfg.c
#    driver/Battery.cpp
#    driver/Led.cpp
#    driver/Ls7366.cpp
#    driver/Adis16488.cpp
#    board/${BOARD}/board.c
#)
#set( INCLUDE
#    app/include
#    system/include
#    driver/include
#    board/${BOARD}
#    ../library/g_matrix
#    ../library/mavlink
#    ../library/mavlink/nio15
#)
#include( ../library/chibios.cmake )
#
#set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--script=\"${CMAKE_CURRENT_SOURCE_DIR}/board/${BOARD}/STM32F405xG.ld\"" )
#add_definitions(-DCORTEX_VTOR_INIT=BOARD_FLASH_FIRMWARE)
#
#
#include_directories( ${INCLUDE} )
#add_executable( ${PROJECT_NAME}.elf ${SOURCES} )
#add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
#add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
#add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_FILESIZE} ARGS ${PROJECT_NAME}.elf)
#add_custom_target(Flash "C:/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe" "-c SWD -Rst -P \"${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex\" -Rst -Run" DEPENDS ${PROJECT_NAME}.elf)
