cmake_minimum_required( VERSION 2.8 )

set(BOARDNAME F415)

include(./board/${BOARDNAME}/board.cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/stm32-cmake/cmake/gcc_stm32.cmake)

project( firmware )
enable_language( ASM )

set(CHIBIOS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/ChibiOS)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/stm32-cmake/cmake)

find_package(ChibiOS 3 COMPONENTS rt pal hal serial serial_usb usb REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} test_new.cpp usbcfg.c ${BOARD_SOURCES} ${ChibiOS_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${ChibiOS_INCLUDE_DIRS} ${BOARD_INCLUDE_DIRS})


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")
set(STM32_LINKER_SCRIPT ${ChibiOS_LINKER_SCRIPT})



# build and flash targets

set(EXECUTABLE_NAME ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME})

configure_file(./configs/gdb/gdb_load.txt.in ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.txt)
configure_file(./configs/gdb/gdb_debug.txt.in ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.txt)

add_custom_target(flash COMMAND ${TOOLCHAIN_PREFIX}/bin/arm-none-eabi-gdb -x ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.txt DEPENDS ${CMAKE_PROJECT_NAME})

STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})

STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})
