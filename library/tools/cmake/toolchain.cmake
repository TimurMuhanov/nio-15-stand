INCLUDE(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

SET(CMAKE_OBJCOPY arm-none-eabi-objcopy CACHE INTERNAL "objcopy" FORCE)
SET(CMAKE_OBJDUMP arm-none-eabi-objdump CACHE INTERNAL "objdump" FORCE)
SET(CMAKE_FILESIZE arm-none-eabi-size CACHE INTERNAL "filesize" FORCE)

SET(MCU_FLAGS "-mcpu=cortex-m4    -mthumb -DTHUMB -DTHUMB_PRESENT     -mno-thumb-interwork -DTHUMB_NO_INTERWORKING    -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DCORTEX_USE_FPU=TRUE")
SET(RELEASE_FLAGS "-flto -O2" )
SET(DEBUG_FLAGS "-ggdb" )
SET(WARNING_FLAGS "-Wall -Wextra -Wno-unused-parameter")
SET(CMAKE_C_FLAGS "${MCU_FLAGS} ${WARNING_FLAGS} ${RELEASE_FLAGS}"  CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "${MCU_FLAGS} ${WARNING_FLAGS} ${RELEASE_FLAGS} -std=c++11"  CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS "-x assembler-with-cpp ${MCU_FLAGS} ${RELEASE_FLAGS}" CACHE INTERNAL "asm compiler flags")

SET(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} ${RELEASE_FLAGS} -nostartfiles --specs=nosys.specs -Wl,--gc-sections,-lnosys,--defsym=__process_stack_size__=0x400,--defsym=__main_stack_size__=0x400" CACHE INTERNAL "exe link flags")
