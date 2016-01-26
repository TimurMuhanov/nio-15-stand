# Chibios
set( SOURCES
	${SOURCES}

	# startup
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/common/ports/ARMCMx/compilers/GCC/crt1.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/common/ports/ARMCMx/compilers/GCC/vectors.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/common/ports/ARMCMx/compilers/GCC/crt0_v7m.s

    # hal
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/hal.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/st.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/hal_queues.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/hal_mmcsd.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/hal.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/hal_queues.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/hal_mmcsd.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/ext.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/gpt.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/i2c.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/i2s.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/icu.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/mac.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/pal.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/pwm.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/rtc.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/sdc.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/serial.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/serial_usb.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/spi.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/st.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/uart.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/src/usb.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/common/ARMCMx/nvic.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx/stm32_dma.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx/hal_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/TIMv1/st_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/common/ARMCMx/nvic.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx/stm32_dma.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx/hal_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx/adc_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx/ext_lld_isr.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/ext_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/mac_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/sdc_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/GPIOv2/pal_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/I2Cv1/i2c_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/OTGv1/usb_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/RTCv2/rtc_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/SPIv1/i2s_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/SPIv1/spi_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/TIMv1/gpt_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/TIMv1/icu_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/TIMv1/pwm_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/TIMv1/st_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/USARTv1/serial_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/USARTv1/uart_lld.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/osal/rt/osal.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/lib/streams/chprintf.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/lib/streams/memstreams.c

	# rt
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chsys.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chdebug.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chvt.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chschd.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chthreads.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chsys.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chdebug.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chvt.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chschd.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chthreads.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chtm.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chstats.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chdynamic.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chregistry.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chsem.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chmtx.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chcond.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chevents.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chmsg.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chmboxes.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chqueues.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chmemcore.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chheap.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/src/chmempools.c
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/ports/ARMCMx/chcore.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/ports/ARMCMx/chcore_v7m.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/ports/ARMCMx/compilers/GCC/chcoreasm_v7m.s

    # fatfs
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/various/fatfs_bindings/fatfs_diskio.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/various/fatfs_bindings/fatfs_syscall.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/ext/fatfs/src/ff.c
    ${CMAKE_CURRENT_LIST_DIR}/chibios/ext/fatfs/src/option/unicode.c

    # cpp wrappers
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/various/cpp_wrappers/syscalls_cpp.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/various/cpp_wrappers/ch.cpp 

    # test
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/various/cpp_wrappers/ch.cpp 
)

set( INCLUDE 
	${INCLUDE}

	# startup
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/common/ports/ARMCMx/devices/STM32F4xx
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/ext/CMSIS/include
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/ext/CMSIS/ST
	
	# hal
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/include
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/common/ARMCMx
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/STM32F4xx
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/DACv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/GPIOv2
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/I2Cv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/OTGv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/RTCv2
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/SPIv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/TIMv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/USARTv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/ports/STM32/LLD/FSMCv1
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/osal/rt
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/hal/lib/streams

	# fatfs
	${CMAKE_CURRENT_LIST_DIR}/chibios/ext/fatfs/src

	# rt
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/include
	${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/ports/ARMCMx
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/rt/ports/ARMCMx/compilers/GCC
    ${CMAKE_CURRENT_LIST_DIR}/chibios/os/various/cpp_wrappers

)

set(CMAKE_EXE_LINKER_FLAGS
	"${CMAKE_EXE_LINKER_FLAGS} -Wl,--library-path=\"${CMAKE_CURRENT_LIST_DIR}/chibios/os/common/ports/ARMCMx/compilers/GCC\"")
