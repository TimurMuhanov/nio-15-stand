/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics STM32F4-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_STM32F4_DISCOVERY
#define BOARD_NAME                  "STMicroelectronics STM32F4-Discovery"


/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F415xx


#define BOARD_FLASH_SECTOR_0		0x08000000		/* 0x08003FFF 16 Kbytes */
#define BOARD_FLASH_SECTOR_1		0x08004000		/* 0x08007FFF 16 Kbytes */
#define BOARD_FLASH_SECTOR_2		0x08008000		/* 0x0800BFFF 16 Kbytes */
#define BOARD_FLASH_SECTOR_3		0x0800C000		/* 0x0800FFFF 16 Kbytes */
#define BOARD_FLASH_SECTOR_4		0x08010000		/* 0x0801FFFF 64 Kbytes */
#define BOARD_FLASH_SECTOR_5		0x08020000		/* 0x0803FFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_6		0x08040000		/* 0x0805FFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_7		0x08060000		/* 0x0807FFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_8		0x08080000		/* 0x0809FFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_9		0x080A0000		/* 0x080BFFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_10		0x080C0000		/* 0x080DFFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_11		0x080E0000		/* 0x080FFFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_11		0x080E0000		/* 0x080FFFFF 128 Kbytes */
#define BOARD_FLASH_SECTOR_END		0x08100000

#define BOARD_ADDRESS_TO_SECTOR(address)	(	(address >= BOARD_FLASH_SECTOR_0) ? (\
												(address < BOARD_FLASH_SECTOR_1) ? (0) : ( \
												(address < BOARD_FLASH_SECTOR_2) ? (1) : ( \
												(address < BOARD_FLASH_SECTOR_3) ? (2) : ( \
												(address < BOARD_FLASH_SECTOR_4) ? (3) : ( \
												(address < BOARD_FLASH_SECTOR_5) ? (4) : ( \
												(address < BOARD_FLASH_SECTOR_6) ? (5) : ( \
												(address < BOARD_FLASH_SECTOR_7) ? (6) : ( \
												(address < BOARD_FLASH_SECTOR_8) ? (7) : ( \
												(address < BOARD_FLASH_SECTOR_9) ? (8) : ( \
												(address < BOARD_FLASH_SECTOR_10) ? (9) : ( \
												(address < BOARD_FLASH_SECTOR_11) ? (10) : ( \
												(address < BOARD_FLASH_SECTOR_END) ? (11) : ( 11 ) \
											) ) ) ) ) ) ) ) ) ) ) ) : (11) )

#define BOARD_IS_ADRESS_CORRECT(address)	( ( (address)>=BOARD_FLASH_FIRMWARE ) && ((address)<BOARD_FLASH_SECTOR_END) ? true : false )


#define BOARD_FLASH_BOOTLOADER		0x08000000
#define BOARD_FLASH_FIRMWARE		0x08040000
/** estimating up flash size */
#define BOARD_FLASH_FIRMWARE_SIZE	0x00050000

#define JUMP_TO(address) boardStop(); \
						 int h; \
						 for(h=0; h<8; h++) \
							NVIC->ICER[h] = NVIC->IABR[h]; \
						 SCB->VTOR = address; \
						 __set_CONTROL(0); \
						 __set_MSP( (u32) (((u32*) address)[0]) ); \
						 ( (void (*)(void)) (((u32*) address)[1]) )();

/*
 * Drivers and interfaces map
 */
#define BOARD_RADIO_DEVICE			SD1
#define BOARD_RS422_DEVICE			SD3
#define BOARD_USB_DEVICE			SDU1
#define BOARD_BLUETOOTH_DEVICE		UARTD2

#define BOARD_PITE_PORT				GPIOC
#define BOARD_PITE_PIN				13
#define BOARD_PITS_PORT				GPIOC
#define BOARD_PITS_PIN				14

#define BOARD_LED1_PORT				GPIOD
#define BOARD_LED1_PIN				13
#define BOARD_LED2_PORT				GPIOD
#define BOARD_LED2_PIN				14
#define BOARD_LED3_PORT				GPIOD
#define BOARD_LED3_PIN				15

#define BOARD_ADIS16488_DEVICE		SPID1
#define BOARD_ADIS16488_CS_PORT		GPIOA
#define BOARD_ADIS16488_CS_PIN		4
#define BOARD_ADIS16488_RSTI_PORT	GPIOD
#define BOARD_ADIS16488_RSTI_PIN	15
#define BOARD_ADIS16488_SINK_PORT	GPIOC
#define BOARD_ADIS16488_SINK_PIN	4
#define BOARD_ADIS16488_RDY_PORT	GPIOC
#define BOARD_ADIS16488_RDY_PIN		5

#define BOARD_LS7366R_DEVICE		SPID2
#define BOARD_LS7366R_CS2_PORT		GPIOB
#define BOARD_LS7366R_CS2_PIN		12
#define BOARD_LS7366R_ESS_PORT		GPIOE
#define BOARD_LS7366R_ESS1_PIN		0
#define BOARD_LS7366R_ESS2_PIN		1
#define BOARD_LS7366R_ESS3_PIN		8
#define BOARD_LS7366R_ESS4_PIN		3
#define BOARD_LS7366R_ESS5_PIN		2
#define BOARD_LS7366R_ESS6_PIN		4
#define BOARD_LS7366R_ESS7_PIN		6
#define BOARD_LS7366R_ESS8_PIN		5
#define BOARD_LS7366R_ESS9_PIN		7

#define BOARD_EXTERNAL_SPI_DEVICE	SPID2
#define BOARD_EXTERNAL_SPI_CS_PORT	GPIOD
#define BOARD_EXTERNAL_SPI_CS_PIN	10

#define BOARD_PWM_DEVICE1			PWMD2
#define BOARD_PWM_DEVICE2			PWMD3

#define BOARD_PWM_ENABLE_PORT		GPIOD
#define BOARD_PWM_ENABLE_PIN		13

#define BOARD_SD_CARD_DEVICE		SDCD1

/*
 * Interfaces configuration
 */
#define BOARD_USART1_BAUD			115200
#define BOARD_USART1_TX_PORT		GPIOB
#define BOARD_USART1_TX_PIN			6
#define BOARD_USART1_RX_PORT		GPIOB
#define BOARD_USART1_RX_PIN			7


#define BOARD_USART2_BAUD			460800
#define BOARD_USART2_TX_PORT		GPIOD
#define BOARD_USART2_TX_PIN			5
#define BOARD_USART2_RX_PORT		GPIOD
#define BOARD_USART2_RX_PIN			6
#define BOARD_USART2_CTS_PORT		GPIOD
#define BOARD_USART2_CTS_PIN		3
#define BOARD_USART2_RTS_PORT		GPIOD
#define BOARD_USART2_RTS_PIN		4

#define BOARD_USART3_BAUD			115200
#define BOARD_USART3_TX_PORT		GPIOB
#define BOARD_USART3_TX_PIN			10
#define BOARD_USART3_RX_PORT		GPIOB
#define BOARD_USART3_RX_PIN			11

#define BOARD_SPI1_CLK_PORT			GPIOA
#define BOARD_SPI1_CLK_PIN			5
#define BOARD_SPI1_MOSI_PORT		GPIOA
#define BOARD_SPI1_MOSI_PIN			7
#define BOARD_SPI1_MISO_PORT		GPIOA
#define BOARD_SPI1_MISO_PIN			6

#define BOARD_SPI2_CLK_PORT			GPIOB
#define BOARD_SPI2_CLK_PIN			13
#define BOARD_SPI2_MOSI_PORT		GPIOB
#define BOARD_SPI2_MOSI_PIN			15
#define BOARD_SPI2_MISO_PORT		GPIOB
#define BOARD_SPI2_MISO_PIN			14

#define BOARD_TIM2_CH1_PORT			GPIOA
#define BOARD_TIM2_CH1_PIN			0
#define BOARD_TIM2_CH2_PORT			GPIOA
#define BOARD_TIM2_CH2_PIN			1
#define BOARD_TIM2_CH3_PORT			GPIOA
#define BOARD_TIM2_CH3_PIN			2
#define BOARD_TIM2_CH4_PORT			GPIOA
#define BOARD_TIM2_CH4_PIN			3

#define BOARD_TIM3_CH1_PORT			GPIOC
#define BOARD_TIM3_CH1_PIN			6
#define BOARD_TIM3_CH2_PORT			GPIOC
#define BOARD_TIM3_CH2_PIN			7
#define BOARD_TIM3_CH3_PORT			GPIOB
#define BOARD_TIM3_CH3_PIN			0
#define BOARD_TIM3_CH4_PORT			GPIOB
#define BOARD_TIM3_CH4_PIN			1

#define BOARD_SDIO_D0_PORT			GPIOC
#define BOARD_SDIO_D0_PIN			8
#define BOARD_SDIO_D1_PORT			GPIOC
#define BOARD_SDIO_D1_PIN			9
#define BOARD_SDIO_D2_PORT			GPIOC
#define BOARD_SDIO_D2_PIN			10
#define BOARD_SDIO_D3_PORT			GPIOC
#define BOARD_SDIO_D3_PIN			11
#define BOARD_SDIO_CMD_PORT			GPIOD
#define BOARD_SDIO_CMD_PIN			2
#define BOARD_SDIO_CLK_PORT			GPIOC
#define BOARD_SDIO_CLK_PIN			12

/*
 * IO pins assignments.
 */
#define GPIOA_BUTTON                0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_PIN3                  3U
#define GPIOA_LRCK                  4U
#define GPIOA_SPC                   5U
#define GPIOA_SDO                   6U
#define GPIOA_SDI                   7U
#define GPIOA_PIN8                  8U
#define GPIOA_VBUS_FS               9U
#define GPIOA_OTG_FS_ID             10U
#define GPIOA_OTG_FS_DM             11U
#define GPIOA_OTG_FS_DP             12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_PIN0                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_SWO                   3U
#define GPIOB_PIN4                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_SCL                   6U
#define GPIOB_PIN7                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_SDA                   9U
#define GPIOB_CLK_IN                10U
#define GPIOB_PIN11                 11U
#define GPIOB_PIN12                 12U
#define GPIOB_PIN13                 13U
#define GPIOB_PIN14                 14U
#define GPIOB_PIN15                 15U

#define GPIOC_OTG_FS_POWER_ON       0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PDM_OUT               3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_MCLK                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_SCLK                  10U
#define GPIOC_PIN11                 11U
#define GPIOC_SDIN                  12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_RESET                 4U
#define GPIOD_OVER_CURRENT          5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_LED4                  12U
#define GPIOD_LED3                  13U
#define GPIOD_LED5                  14U
#define GPIOD_LED6                  15U

#define GPIOE_INT1                  0U
#define GPIOE_INT2                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_CS_SPI                3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2U))
#define PIN_OSPEED_25M(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_50M(n)           (2U << ((n) * 2U))
#define PIN_OSPEED_100M(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - BUTTON                    (input floating).
 * PA1  - PIN1                      (input pullup).
 * PA2  - PIN2                      (input pullup).
 * PA3  - PIN3                      (input pullup).
 * PA4  - LRCK                      (alternate 6).
 * PA5  - SPC                       (alternate 5).
 * PA6  - SDO                       (alternate 5).
 * PA7  - SDI                       (alternate 5).
 * PA8  - PIN8                      (input pullup).
 * PA9  - VBUS_FS                   (input floating).
 * PA10 - OTG_FS_ID                 (alternate 10).
 * PA11 - OTG_FS_DM                 (alternate 10).
 * PA12 - OTG_FS_DP                 (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - PIN15                     (input pullup).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_BUTTON) |         \
                                     PIN_MODE_INPUT(GPIOA_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOA_PIN3) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_LRCK) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_SPC) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_SDO) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_SDI) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_VBUS_FS) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_ID) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_INPUT(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_BUTTON) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LRCK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPC) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SDO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SDI) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_VBUS_FS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_ID) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DP) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_100M(GPIOA_BUTTON) |        \
                                     PIN_OSPEED_100M(GPIOA_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOA_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOA_PIN3) |          \
                                     PIN_OSPEED_100M(GPIOA_LRCK) |          \
                                     PIN_OSPEED_50M(GPIOA_SPC) |            \
                                     PIN_OSPEED_50M(GPIOA_SDO) |            \
                                     PIN_OSPEED_50M(GPIOA_SDI) |            \
                                     PIN_OSPEED_100M(GPIOA_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOA_VBUS_FS) |       \
                                     PIN_OSPEED_100M(GPIOA_OTG_FS_ID) |     \
                                     PIN_OSPEED_100M(GPIOA_OTG_FS_DM) |     \
                                     PIN_OSPEED_100M(GPIOA_OTG_FS_DP) |     \
                                     PIN_OSPEED_100M(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_100M(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_100M(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_BUTTON) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_LRCK) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_SPC) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_SDO) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_SDI) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_VBUS_FS) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_ID) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DP) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_BUTTON) |           \
                                     PIN_ODR_HIGH(GPIOA_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOA_LRCK) |             \
                                     PIN_ODR_HIGH(GPIOA_SPC) |              \
                                     PIN_ODR_HIGH(GPIOA_SDO) |              \
                                     PIN_ODR_HIGH(GPIOA_SDI) |              \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOA_VBUS_FS) |          \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_ID) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DM) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DP) |        \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_BUTTON, 0) |         \
                                     PIN_AFIO_AF(GPIOA_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOA_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOA_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOA_LRCK, 6) |           \
                                     PIN_AFIO_AF(GPIOA_SPC, 5) |            \
                                     PIN_AFIO_AF(GPIOA_SDO, 5) |            \
                                     PIN_AFIO_AF(GPIOA_SDI, 5))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOA_VBUS_FS, 0) |        \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_ID, 10) |     \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DM, 10) |     \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DP, 10) |     \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) |          \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (input pullup).
 * PB1  - PIN1                      (input pullup).
 * PB2  - PIN2                      (input pullup).
 * PB3  - SWO                       (alternate 0).
 * PB4  - PIN4                      (input pullup).
 * PB5  - PIN5                      (input pullup).
 * PB6  - SCL                       (alternate 4).
 * PB7  - PIN7                      (input pullup).
 * PB8  - PIN8                      (input pullup).
 * PB9  - SDA                       (alternate 4).
 * PB10 - CLK_IN                    (input pullup).
 * PB11 - PIN11                     (input pullup).
 * PB12 - PIN12                     (input pullup).
 * PB13 - PIN13                     (input pullup).
 * PB14 - PIN14                     (input pullup).
 * PB15 - PIN15                     (input pullup).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SCL) |        \
                                     PIN_MODE_INPUT(GPIOB_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_SDA) |        \
                                     PIN_MODE_INPUT(GPIOB_CLK_IN) |         \
                                     PIN_MODE_INPUT(GPIOB_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOB_PIN15))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_SCL) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_SDA) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CLK_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN15))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_100M(GPIOB_PIN0) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOB_SWO) |           \
                                     PIN_OSPEED_100M(GPIOB_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOB_SCL) |           \
                                     PIN_OSPEED_100M(GPIOB_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOB_SDA) |           \
                                     PIN_OSPEED_100M(GPIOB_CLK_IN) |        \
                                     PIN_OSPEED_100M(GPIOB_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOB_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOB_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOB_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOB_PIN15))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SCL) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_SDA) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_CLK_IN) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN15))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOB_SCL) |              \
                                     PIN_ODR_HIGH(GPIOB_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOB_SDA) |              \
                                     PIN_ODR_HIGH(GPIOB_CLK_IN) |           \
                                     PIN_ODR_HIGH(GPIOB_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOB_PIN15))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SWO, 0) |            \
                                     PIN_AFIO_AF(GPIOB_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SCL, 4) |            \
                                     PIN_AFIO_AF(GPIOB_PIN7, 0))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SDA, 4) |            \
                                     PIN_AFIO_AF(GPIOB_CLK_IN, 0) |         \
                                     PIN_AFIO_AF(GPIOB_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOB_PIN15, 0))

/*
 * GPIOC setup:
 *
 * PC0  - OTG_FS_POWER_ON           (output pushpull maximum).
 * PC1  - PIN1                      (input pullup).
 * PC2  - PIN2                      (input pullup).
 * PC3  - PDM_OUT                   (input pullup).
 * PC4  - PIN4                      (input pullup).
 * PC5  - PIN5                      (input pullup).
 * PC6  - PIN6                      (input pullup).
 * PC7  - MCLK                      (alternate 6).
 * PC8  - PIN8                      (input pullup).
 * PC9  - PIN9                      (input pullup).
 * PC10 - SCLK                      (alternate 6).
 * PC11 - PIN11                     (input pullup).
 * PC12 - SDIN                      (alternate 6).
 * PC13 - PIN13                     (input pullup).
 * PC14 - PIN14                     (input pullup).
 * PC15 - PIN15                     (input pullup).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_OTG_FS_POWER_ON) |\
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_PDM_OUT) |        \
                                     PIN_MODE_INPUT(GPIOC_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN6) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_MCLK) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN9) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_SCLK) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN11) |          \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIN) |       \
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_OTG_FS_POWER_ON) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PDM_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MCLK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SCLK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIN) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_100M(GPIOC_OTG_FS_POWER_ON) |\
                                     PIN_OSPEED_100M(GPIOC_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOC_PDM_OUT) |       \
                                     PIN_OSPEED_100M(GPIOC_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOC_MCLK) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOC_SCLK) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOC_SDIN) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOC_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_OTG_FS_POWER_ON) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PDM_OUT) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN6) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_MCLK) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN9) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_SCLK) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIN) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_OTG_FS_POWER_ON) |  \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOC_PDM_OUT) |          \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOC_MCLK) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOC_SCLK) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOC_SDIN) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_OTG_FS_POWER_ON, 0) |\
                                     PIN_AFIO_AF(GPIOC_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PDM_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOC_MCLK, 6))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOC_SCLK, 6) |           \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOC_SDIN, 6) |           \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (input pullup).
 * PD1  - PIN1                      (input pullup).
 * PD2  - PIN2                      (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - RESET                     (output pushpull maximum).
 * PD5  - OVER_CURRENT              (input floating).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (input pullup).
 * PD10 - PIN10                     (input pullup).
 * PD11 - PIN11                     (input pullup).
 * PD12 - LED4                      (output pushpull maximum).
 * PD13 - LED3                      (output pushpull maximum).
 * PD14 - LED5                      (output pushpull maximum).
 * PD15 - LED6                      (output pushpull maximum).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_OUTPUT(GPIOD_RESET) |         \
                                     PIN_MODE_INPUT(GPIOD_OVER_CURRENT) |   \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_OUTPUT(GPIOD_LED4) |          \
                                     PIN_MODE_OUTPUT(GPIOD_LED3) |          \
                                     PIN_MODE_OUTPUT(GPIOD_LED5) |          \
                                     PIN_MODE_OUTPUT(GPIOD_LED6))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RESET) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_OVER_CURRENT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LED6))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_100M(GPIOD_PIN0) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN3) |          \
                                     PIN_OSPEED_100M(GPIOD_RESET) |         \
                                     PIN_OSPEED_100M(GPIOD_OVER_CURRENT) |  \
                                     PIN_OSPEED_100M(GPIOD_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOD_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOD_LED4) |          \
                                     PIN_OSPEED_100M(GPIOD_LED3) |          \
                                     PIN_OSPEED_100M(GPIOD_LED5) |          \
                                     PIN_OSPEED_100M(GPIOD_LED6))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_RESET) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_OVER_CURRENT) |\
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_LED4) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_LED3) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_LED5) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_LED6))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_RESET) |            \
                                     PIN_ODR_HIGH(GPIOD_OVER_CURRENT) |     \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_LOW(GPIOD_LED4) |              \
                                     PIN_ODR_LOW(GPIOD_LED3) |              \
                                     PIN_ODR_LOW(GPIOD_LED5) |              \
                                     PIN_ODR_LOW(GPIOD_LED6))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOD_RESET, 0) |          \
                                     PIN_AFIO_AF(GPIOD_OVER_CURRENT, 0) |   \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOD_LED4, 0) |           \
                                     PIN_AFIO_AF(GPIOD_LED3, 0) |           \
                                     PIN_AFIO_AF(GPIOD_LED5, 0) |           \
                                     PIN_AFIO_AF(GPIOD_LED6, 0))

/*
 * GPIOE setup:
 *
 * PE0  - INT1                      (input floating).
 * PE1  - INT2                      (input floating).
 * PE2  - PIN2                      (input floating).
 * PE3  - CS_SPI                    (output pushpull maximum).
 * PE4  - PIN4                      (input floating).
 * PE5  - PIN5                      (input floating).
 * PE6  - PIN6                      (input floating).
 * PE7  - PIN7                      (input floating).
 * PE8  - PIN8                      (input floating).
 * PE9  - PIN9                      (input floating).
 * PE10 - PIN10                     (input floating).
 * PE11 - PIN11                     (input floating).
 * PE12 - PIN12                     (input floating).
 * PE13 - PIN13                     (input floating).
 * PE14 - PIN14                     (input floating).
 * PE15 - PIN15                     (input floating).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_INT1) |           \
                                     PIN_MODE_INPUT(GPIOE_INT2) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_OUTPUT(GPIOE_CS_SPI) |        \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_INT1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_INT2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_CS_SPI) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_100M(GPIOE_INT1) |          \
                                     PIN_OSPEED_100M(GPIOE_INT2) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOE_CS_SPI) |        \
                                     PIN_OSPEED_100M(GPIOE_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_INT1) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_INT2) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_CS_SPI) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_INT1) |             \
                                     PIN_ODR_HIGH(GPIOE_INT2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_CS_SPI) |           \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_INT1, 0) |           \
                                     PIN_AFIO_AF(GPIOE_INT2, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOE_CS_SPI, 0) |         \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input floating).
 * PF1  - PIN1                      (input floating).
 * PF2  - PIN2                      (input floating).
 * PF3  - PIN3                      (input floating).
 * PF4  - PIN4                      (input floating).
 * PF5  - PIN5                      (input floating).
 * PF6  - PIN6                      (input floating).
 * PF7  - PIN7                      (input floating).
 * PF8  - PIN8                      (input floating).
 * PF9  - PIN9                      (input floating).
 * PF10 - PIN10                     (input floating).
 * PF11 - PIN11                     (input floating).
 * PF12 - PIN12                     (input floating).
 * PF13 - PIN13                     (input floating).
 * PF14 - PIN14                     (input floating).
 * PF15 - PIN15                     (input floating).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_100M(GPIOF_PIN0) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN3) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOF_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOF_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOF_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOF_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOF_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input floating).
 * PG1  - PIN1                      (input floating).
 * PG2  - PIN2                      (input floating).
 * PG3  - PIN3                      (input floating).
 * PG4  - PIN4                      (input floating).
 * PG5  - PIN5                      (input floating).
 * PG6  - PIN6                      (input floating).
 * PG7  - PIN7                      (input floating).
 * PG8  - PIN8                      (input floating).
 * PG9  - PIN9                      (input floating).
 * PG10 - PIN10                     (input floating).
 * PG11 - PIN11                     (input floating).
 * PG12 - PIN12                     (input floating).
 * PG13 - PIN13                     (input floating).
 * PG14 - PIN14                     (input floating).
 * PG15 - PIN15                     (input floating).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_100M(GPIOG_PIN0) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN3) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOG_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOG_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOG_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOG_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOG_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (input floating).
 * PH1  - OSC_OUT                   (input floating).
 * PH2  - PIN2                      (input floating).
 * PH3  - PIN3                      (input floating).
 * PH4  - PIN4                      (input floating).
 * PH5  - PIN5                      (input floating).
 * PH6  - PIN6                      (input floating).
 * PH7  - PIN7                      (input floating).
 * PH8  - PIN8                      (input floating).
 * PH9  - PIN9                      (input floating).
 * PH10 - PIN10                     (input floating).
 * PH11 - PIN11                     (input floating).
 * PH12 - PIN12                     (input floating).
 * PH13 - PIN13                     (input floating).
 * PH14 - PIN14                     (input floating).
 * PH15 - PIN15                     (input floating).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOH_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_100M(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_100M(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_100M(GPIOH_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN3) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOH_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOH_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOH_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOH_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOH_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0) |         \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0) |        \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input floating).
 * PI1  - PIN1                      (input floating).
 * PI2  - PIN2                      (input floating).
 * PI3  - PIN3                      (input floating).
 * PI4  - PIN4                      (input floating).
 * PI5  - PIN5                      (input floating).
 * PI6  - PIN6                      (input floating).
 * PI7  - PIN7                      (input floating).
 * PI8  - PIN8                      (input floating).
 * PI9  - PIN9                      (input floating).
 * PI10 - PIN10                     (input floating).
 * PI11 - PIN11                     (input floating).
 * PI12 - PIN12                     (input floating).
 * PI13 - PIN13                     (input floating).
 * PI14 - PIN14                     (input floating).
 * PI15 - PIN15                     (input floating).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_100M(GPIOI_PIN0) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN3) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN4) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN6) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN7) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOI_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOI_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOI_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOI_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOI_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0) |          \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
  void boardStop(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
