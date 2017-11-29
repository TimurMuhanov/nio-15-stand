cmake_minimum_required( VERSION 2.8 )

set(BOARDNAME F415)

include(./board/${BOARDNAME}/board.cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/stm32-cmake/cmake/gcc_stm32.cmake)

project( firmware )
enable_language( ASM )

set(CHIBIOS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/ChibiOS)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/stm32-cmake/cmake)

set(CHIBIOS_PROCESS_STACK_SIZE 0x2400)
set(CHIBIOS_MAIN_STACK_SIZE 0x2400)
find_package(ChibiOS 3 COMPONENTS rt pal hal serial_usb usb adc chprintf REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} test_new.cpp driver/Link.cpp driver/Link.h)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ${BOARD_SOURCES}
        usbcfg.c
        driver/Led.cpp
        driver/Led.h
        driver/Battery.cpp
        driver/Battery.h
        system/Connection.cpp
        system/Connection.h
        driver/PWM.cpp
        driver/PWM.h)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${BOARD_INCLUDE_DIRS})

# ChibiOS
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ${ChibiOS_SOURCES}
        ../3rdparty/ChibiOS/os/various/cpp_wrappers/ch.cpp
        ../3rdparty/ChibiOS/os/various/cpp_wrappers/ch.hpp
        ../3rdparty/ChibiOS/os/various/cpp_wrappers/syscalls_cpp.cpp
        ../3rdparty/ChibiOS/os/various/cpp_wrappers/syscalls_cpp.hpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${ChibiOS_INCLUDE_DIRS} ../3rdparty/ChibiOS/os/various/cpp_wrappers/)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles --specs=nosys.specs")

# MAVLink
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mavlink ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/mavlink/nio15)



# build and flash targets

set(EXECUTABLE_NAME ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})

configure_file(./configs/gdb/gdb_load.txt.in ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.txt)
configure_file(./configs/gdb/gdb_debug.txt.in ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.txt)

add_custom_target(flash COMMAND ${TOOLCHAIN_PREFIX}/bin/arm-none-eabi-gdb -x ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.txt DEPENDS ${CMAKE_PROJECT_NAME})

set(STM32_LINKER_SCRIPT ${ChibiOS_LINKER_SCRIPT})
STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})
STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})
