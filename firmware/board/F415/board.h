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


/*
 * IO pins assignments.
 */
#define GPIOA_PWM1                  0U
#define GPIOA_PWM2                  1U
#define GPIOA_PWM3                  2U
#define GPIOA_PWM4                  3U
#define GPIOA_CS1                   4U
#define GPIOA_SCK1                  5U
#define GPIOA_MISO1                 6U
#define GPIOA_MOSI1                 7U
#define GPIOA_PIN8                  8U
#define GPIOA_VBUS_FS               9U
#define GPIOA_OTG_FS_ID             10U
#define GPIOA_OTG_FS_DM             11U
#define GPIOA_OTG_FS_DP             12U
#define GPIOA_TMS                   13U
#define GPIOA_TCK                   14U
#define GPIOA_TDI                   15U

#define GPIOB_PWM7                  0U
#define GPIOB_PWM8                  1U
#define GPIOB_PIN2                  2U
#define GPIOB_TDO                   3U
#define GPIOB_TRST                  4U
#define GPIOB_PIN5                  5U
#define GPIOB_U1Tx                  6U
#define GPIOB_U1Rx                  7U
#define GPIOB_PIN8                  8U
#define GPIOB_SOUND                 9U
#define GPIOB_U3Tx                  10U
#define GPIOB_U3Rx                  11U
#define GPIOB_CS2                   12U
#define GPIOB_SCK2                  13U
#define GPIOB_MISO2                 14U
#define GPIOB_MOSI2                 15U

#define GPIOC_LED1                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_ADC                   3U
#define GPIOC_SINK                  4U
#define GPIOC_RDY                   5U
#define GPIOC_PWM5                  6U
#define GPIOC_PWM6                  7U
#define GPIOC_SD0                   8U
#define GPIOC_SD1                   9U
#define GPIOC_SD2                   10U
#define GPIOC_SD3                   11U
#define GPIOC_SDCLK                 12U
#define GPIOC_LED4                  13U
#define GPIOC_LED3                  14U
#define GPIOC_LED2                  15U

#define GPIOD_RSTR1                 0U
#define GPIOD_RSTR2                 1U
#define GPIOD_SDCMD                 2U
#define GPIOD_CTS                   3U
#define GPIOD_RTS                   4U
#define GPIOD_U2Tx                  5U
#define GPIOD_U2Rx                  6U
#define GPIOD_SLEEP                 7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_CS3                   10U
#define GPIOD_MODE                  11U
#define GPIOD_CONN                  12U
#define GPIOD_PITS                  13U
#define GPIOD_PITE                  14U
#define GPIOD_RSTI                  15U

#define GPIOE_ESS1                  0U
#define GPIOE_ESS2                  1U
#define GPIOE_ESS3                  2U
#define GPIOE_ESS4                  3U
#define GPIOE_ESS5                  4U
#define GPIOE_ESS6                  5U
#define GPIOE_ESS7                  6U
#define GPIOE_ESS8                  7U
#define GPIOE_ESS9                  8U
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
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_PWM1) |         \
                                     PIN_MODE_INPUT(GPIOA_PWM2) |           \
                                     PIN_MODE_INPUT(GPIOA_PWM3) |           \
                                     PIN_MODE_INPUT(GPIOA_PWM4) |           \
                                     PIN_MODE_ALTERNATE(GPIOA_CS1) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_SCK1) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_MISO1) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_MOSI1) |        \
                                     PIN_MODE_INPUT(GPIOA_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOA_VBUS_FS) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_ID) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_TMS) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_TCK) |      \
                                     PIN_MODE_INPUT(GPIOA_TDI))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PWM1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PWM2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PWM3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PWM4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_CS1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SCK1) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MISO1) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MOSI1) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_VBUS_FS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_ID) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DP) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TMS) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TCK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_TDI))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_100M(GPIOA_PWM1) |        \
                                     PIN_OSPEED_100M(GPIOA_PWM2) |          \
                                     PIN_OSPEED_100M(GPIOA_PWM3) |          \
                                     PIN_OSPEED_100M(GPIOA_PWM4) |          \
                                     PIN_OSPEED_100M(GPIOA_CS1) |          \
                                     PIN_OSPEED_50M(GPIOA_SCK1) |            \
                                     PIN_OSPEED_50M(GPIOA_MISO1) |            \
                                     PIN_OSPEED_50M(GPIOA_MOSI1) |            \
                                     PIN_OSPEED_100M(GPIOA_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOA_VBUS_FS) |       \
                                     PIN_OSPEED_100M(GPIOA_OTG_FS_ID) |     \
                                     PIN_OSPEED_100M(GPIOA_OTG_FS_DM) |     \
                                     PIN_OSPEED_100M(GPIOA_OTG_FS_DP) |     \
                                     PIN_OSPEED_100M(GPIOA_TMS) |         \
                                     PIN_OSPEED_100M(GPIOA_TCK) |         \
                                     PIN_OSPEED_100M(GPIOA_TDI))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PWM1) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_PWM2) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PWM3) |         \
                                     PIN_PUPDR_PULLUP(GPIOA_PWM4) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_CS1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_SCK1) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_MISO1) |        \
                                     PIN_PUPDR_FLOATING(GPIOA_MOSI1) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_PIN8) |         \
                                     PIN_PUPDR_FLOATING(GPIOA_VBUS_FS) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_ID) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DM) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_OTG_FS_DP) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_TMS) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_TCK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_TDI))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PWM1) |           \
                                     PIN_ODR_HIGH(GPIOA_PWM2) |             \
                                     PIN_ODR_HIGH(GPIOA_PWM3) |             \
                                     PIN_ODR_HIGH(GPIOA_PWM4) |             \
                                     PIN_ODR_HIGH(GPIOA_CS1) |             \
                                     PIN_ODR_HIGH(GPIOA_SCK1) |              \
                                     PIN_ODR_HIGH(GPIOA_MISO1) |              \
                                     PIN_ODR_HIGH(GPIOA_MOSI1) |              \
                                     PIN_ODR_HIGH(GPIOA_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOA_VBUS_FS) |          \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_ID) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DM) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DP) |        \
                                     PIN_ODR_HIGH(GPIOA_TMS) |            \
                                     PIN_ODR_HIGH(GPIOA_TCK) |            \
                                     PIN_ODR_HIGH(GPIOA_TDI))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PWM1, 0) |         \
                                     PIN_AFIO_AF(GPIOA_PWM2, 0) |           \
                                     PIN_AFIO_AF(GPIOA_PWM3, 0) |           \
                                     PIN_AFIO_AF(GPIOA_PWM4, 0) |           \
                                     PIN_AFIO_AF(GPIOA_CS1, 6) |           \
                                     PIN_AFIO_AF(GPIOA_SCK1, 5) |            \
                                     PIN_AFIO_AF(GPIOA_MISO1, 5) |            \
                                     PIN_AFIO_AF(GPIOA_MOSI1, 5))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOA_VBUS_FS, 0) |        \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_ID, 10) |     \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DM, 10) |     \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DP, 10) |     \
                                     PIN_AFIO_AF(GPIOA_TMS, 0) |          \
                                     PIN_AFIO_AF(GPIOA_TCK, 0) |          \
                                     PIN_AFIO_AF(GPIOA_TDI, 0))

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
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_PWM7) |           \
                                     PIN_MODE_INPUT(GPIOB_PWM8) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN2) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_TDO) |        \
                                     PIN_MODE_INPUT(GPIOB_TRST) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN5) |           \
                                     PIN_MODE_ALTERNATE(GPIOB_U1Tx) |        \
                                     PIN_MODE_INPUT(GPIOB_U1Rx) |           \
                                     PIN_MODE_INPUT(GPIOB_PIN8) |           \
                                     PIN_MODE_OUTPUT(GPIOB_SOUND) |        \
                                     PIN_MODE_INPUT(GPIOB_U3Tx) |         \
                                     PIN_MODE_INPUT(GPIOB_U3Rx) |          \
                                     PIN_MODE_INPUT(GPIOB_CS2) |          \
                                     PIN_MODE_INPUT(GPIOB_SCK2) |          \
                                     PIN_MODE_INPUT(GPIOB_MISO2) |          \
                                     PIN_MODE_INPUT(GPIOB_MOSI2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PWM7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PWM8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TDO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_TRST) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN5) |       \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_U1Tx) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_U1Rx) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SOUND) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_U3Tx) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_U3Rx) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CS2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SCK2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MISO2) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MOSI2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_100M(GPIOB_PWM7) |          \
                                     PIN_OSPEED_100M(GPIOB_PWM8) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOB_TDO) |           \
                                     PIN_OSPEED_100M(GPIOB_TRST) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN5) |          \
                                     PIN_OSPEED_100M(GPIOB_U1Tx) |           \
                                     PIN_OSPEED_100M(GPIOB_U1Rx) |          \
                                     PIN_OSPEED_100M(GPIOB_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOB_SOUND) |           \
                                     PIN_OSPEED_100M(GPIOB_U3Tx) |        \
                                     PIN_OSPEED_100M(GPIOB_U3Rx) |         \
                                     PIN_OSPEED_100M(GPIOB_CS2) |         \
                                     PIN_OSPEED_100M(GPIOB_SCK2) |         \
                                     PIN_OSPEED_100M(GPIOB_MISO2) |         \
                                     PIN_OSPEED_100M(GPIOB_MOSI2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_PWM7) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PWM8) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN2) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_TDO) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_TRST) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN5) |         \
                                     PIN_PUPDR_FLOATING(GPIOB_U1Tx) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_U1Rx) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOB_SOUND) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_U3Tx) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_U3Rx) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_CS2) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_SCK2) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_MISO2) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_MOSI2))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PWM7) |             \
                                     PIN_ODR_HIGH(GPIOB_PWM8) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOB_TDO) |              \
                                     PIN_ODR_HIGH(GPIOB_TRST) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOB_U1Tx) |              \
                                     PIN_ODR_HIGH(GPIOB_U1Rx) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOB_SOUND) |              \
                                     PIN_ODR_HIGH(GPIOB_U3Tx) |           \
                                     PIN_ODR_HIGH(GPIOB_U3Rx) |            \
                                     PIN_ODR_HIGH(GPIOB_CS2) |            \
                                     PIN_ODR_HIGH(GPIOB_SCK2) |            \
                                     PIN_ODR_HIGH(GPIOB_MISO2) |            \
                                     PIN_ODR_HIGH(GPIOB_MOSI2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PWM7, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PWM8, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOB_TDO, 0) |            \
                                     PIN_AFIO_AF(GPIOB_TRST, 0) |           \
                                     PIN_AFIO_AF(GPIOB_PIN5, 0) |           \
                                     PIN_AFIO_AF(GPIOB_U1Tx, 4) |            \
                                     PIN_AFIO_AF(GPIOB_U1Rx, 0))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOB_SOUND, 0) |            \
                                     PIN_AFIO_AF(GPIOB_U3Tx, 0) |         \
                                     PIN_AFIO_AF(GPIOB_U3Rx, 0) |          \
                                     PIN_AFIO_AF(GPIOB_CS2, 0) |          \
                                     PIN_AFIO_AF(GPIOB_SCK2, 0) |          \
                                     PIN_AFIO_AF(GPIOB_MISO2, 0) |          \
                                     PIN_AFIO_AF(GPIOB_MOSI2, 0))

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
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_LED1) |\
                                     PIN_MODE_INPUT(GPIOC_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOC_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOC_ADC) |        \
                                     PIN_MODE_INPUT(GPIOC_SINK) |           \
                                     PIN_MODE_INPUT(GPIOC_RDY) |           \
                                     PIN_MODE_INPUT(GPIOC_PWM5) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_PWM6) |       \
                                     PIN_MODE_INPUT(GPIOC_SD0) |           \
                                     PIN_MODE_INPUT(GPIOC_SD1) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_SD2) |       \
                                     PIN_MODE_INPUT(GPIOC_SD3) |          \
                                     PIN_MODE_ALTERNATE(GPIOC_SDCLK) |       \
                                     PIN_MODE_OUTPUT(GPIOC_LED4) |          \
                                     PIN_MODE_OUTPUT(GPIOC_LED3) |          \
                                     PIN_MODE_OUTPUT(GPIOC_LED2))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_LED1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_ADC) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SINK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_RDY) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PWM5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PWM6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SD3) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDCLK) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED4) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED3) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED2))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_100M(GPIOC_LED1) |\
                                     PIN_OSPEED_100M(GPIOC_PIN1) |          \
                                     PIN_OSPEED_100M(GPIOC_PIN2) |          \
                                     PIN_OSPEED_100M(GPIOC_ADC) |       \
                                     PIN_OSPEED_100M(GPIOC_SINK) |          \
                                     PIN_OSPEED_100M(GPIOC_RDY) |          \
                                     PIN_OSPEED_100M(GPIOC_PWM5) |          \
                                     PIN_OSPEED_100M(GPIOC_PWM6) |          \
                                     PIN_OSPEED_100M(GPIOC_SD0) |          \
                                     PIN_OSPEED_100M(GPIOC_SD1) |          \
                                     PIN_OSPEED_100M(GPIOC_SD2) |          \
                                     PIN_OSPEED_100M(GPIOC_SD3) |         \
                                     PIN_OSPEED_100M(GPIOC_SDCLK) |          \
                                     PIN_OSPEED_100M(GPIOC_LED4) |         \
                                     PIN_OSPEED_100M(GPIOC_LED3) |         \
                                     PIN_OSPEED_100M(GPIOC_LED2))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_LED1) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_ADC) |      \
                                     PIN_PUPDR_PULLUP(GPIOC_SINK) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_RDY) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_PWM5) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_PWM6) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_SD0) |         \
                                     PIN_PUPDR_PULLUP(GPIOC_SD1) |         \
                                     PIN_PUPDR_FLOATING(GPIOC_SD2) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_SD3) |        \
                                     PIN_PUPDR_FLOATING(GPIOC_SDCLK) |       \
                                     PIN_PUPDR_PULLUP(GPIOC_LED4) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_LED3) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_LED2))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_LED1) |  \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOC_ADC) |          \
                                     PIN_ODR_HIGH(GPIOC_SINK) |             \
                                     PIN_ODR_HIGH(GPIOC_RDY) |             \
                                     PIN_ODR_HIGH(GPIOC_PWM5) |             \
                                     PIN_ODR_HIGH(GPIOC_PWM6) |             \
                                     PIN_ODR_HIGH(GPIOC_SD0) |             \
                                     PIN_ODR_HIGH(GPIOC_SD1) |             \
                                     PIN_ODR_HIGH(GPIOC_SD2) |             \
                                     PIN_ODR_HIGH(GPIOC_SD3) |            \
                                     PIN_ODR_HIGH(GPIOC_SDCLK) |             \
                                     PIN_ODR_HIGH(GPIOC_LED4) |            \
                                     PIN_ODR_HIGH(GPIOC_LED3) |            \
                                     PIN_ODR_HIGH(GPIOC_LED2))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_LED1, 0) |\
                                     PIN_AFIO_AF(GPIOC_PIN1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0) |           \
                                     PIN_AFIO_AF(GPIOC_ADC, 0) |        \
                                     PIN_AFIO_AF(GPIOC_SINK, 0) |           \
                                     PIN_AFIO_AF(GPIOC_RDY, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PWM5, 0) |           \
                                     PIN_AFIO_AF(GPIOC_PWM6, 6))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SD0, 0) |           \
                                     PIN_AFIO_AF(GPIOC_SD1, 0) |           \
                                     PIN_AFIO_AF(GPIOC_SD2, 6) |           \
                                     PIN_AFIO_AF(GPIOC_SD3, 0) |          \
                                     PIN_AFIO_AF(GPIOC_SDCLK, 6) |           \
                                     PIN_AFIO_AF(GPIOC_LED4, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED3, 0) |          \
                                     PIN_AFIO_AF(GPIOC_LED2, 0))

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
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_RSTR1) |           \
                                     PIN_MODE_INPUT(GPIOD_RSTR2) |           \
                                     PIN_MODE_INPUT(GPIOD_SDCMD) |           \
                                     PIN_MODE_INPUT(GPIOD_CTS) |           \
                                     PIN_MODE_OUTPUT(GPIOD_RTS) |         \
                                     PIN_MODE_INPUT(GPIOD_U2Tx) |   \
                                     PIN_MODE_INPUT(GPIOD_U2Rx) |           \
                                     PIN_MODE_INPUT(GPIOD_SLEEP) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_CS3) |          \
                                     PIN_MODE_INPUT(GPIOD_MODE) |          \
                                     PIN_MODE_OUTPUT(GPIOD_CONN) |          \
                                     PIN_MODE_OUTPUT(GPIOD_PITS) |          \
                                     PIN_MODE_OUTPUT(GPIOD_PITE) |          \
                                     PIN_MODE_OUTPUT(GPIOD_RSTI))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_RSTR1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RSTR2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SDCMD) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_CTS) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RTS) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_U2Tx) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_U2Rx) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SLEEP) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_CS3) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_MODE) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_CONN) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PITS) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PITE) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_RSTI))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_100M(GPIOD_RSTR1) |          \
                                     PIN_OSPEED_100M(GPIOD_RSTR2) |          \
                                     PIN_OSPEED_100M(GPIOD_SDCMD) |          \
                                     PIN_OSPEED_100M(GPIOD_CTS) |          \
                                     PIN_OSPEED_100M(GPIOD_RTS) |         \
                                     PIN_OSPEED_100M(GPIOD_U2Tx) |  \
                                     PIN_OSPEED_100M(GPIOD_U2Rx) |          \
                                     PIN_OSPEED_100M(GPIOD_SLEEP) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN8) |          \
                                     PIN_OSPEED_100M(GPIOD_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOD_CS3) |         \
                                     PIN_OSPEED_100M(GPIOD_MODE) |         \
                                     PIN_OSPEED_100M(GPIOD_CONN) |          \
                                     PIN_OSPEED_100M(GPIOD_PITS) |          \
                                     PIN_OSPEED_100M(GPIOD_PITE) |          \
                                     PIN_OSPEED_100M(GPIOD_RSTI))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_RSTR1) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_RSTR2) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_SDCMD) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_CTS) |         \
                                     PIN_PUPDR_FLOATING(GPIOD_RTS) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_U2Tx) |\
                                     PIN_PUPDR_PULLUP(GPIOD_U2Rx) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_SLEEP) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_CS3) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_MODE) |        \
                                     PIN_PUPDR_FLOATING(GPIOD_CONN) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PITS) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PITE) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_RSTI))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_RSTR1) |             \
                                     PIN_ODR_HIGH(GPIOD_RSTR2) |             \
                                     PIN_ODR_HIGH(GPIOD_SDCMD) |             \
                                     PIN_ODR_HIGH(GPIOD_CTS) |             \
                                     PIN_ODR_HIGH(GPIOD_RTS) |            \
                                     PIN_ODR_HIGH(GPIOD_U2Tx) |     \
                                     PIN_ODR_HIGH(GPIOD_U2Rx) |             \
                                     PIN_ODR_HIGH(GPIOD_SLEEP) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_CS3) |            \
                                     PIN_ODR_HIGH(GPIOD_MODE) |            \
                                     PIN_ODR_LOW(GPIOD_CONN) |              \
                                     PIN_ODR_LOW(GPIOD_PITS) |              \
                                     PIN_ODR_LOW(GPIOD_PITE) |              \
                                     PIN_ODR_LOW(GPIOD_RSTI))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_RSTR1, 0) |           \
                                     PIN_AFIO_AF(GPIOD_RSTR2, 0) |           \
                                     PIN_AFIO_AF(GPIOD_SDCMD, 0) |           \
                                     PIN_AFIO_AF(GPIOD_CTS, 0) |           \
                                     PIN_AFIO_AF(GPIOD_RTS, 0) |          \
                                     PIN_AFIO_AF(GPIOD_U2Tx, 0) |   \
                                     PIN_AFIO_AF(GPIOD_U2Rx, 0) |           \
                                     PIN_AFIO_AF(GPIOD_SLEEP, 0))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0) |           \
                                     PIN_AFIO_AF(GPIOD_CS3, 0) |          \
                                     PIN_AFIO_AF(GPIOD_MODE, 0) |          \
                                     PIN_AFIO_AF(GPIOD_CONN, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PITS, 0) |           \
                                     PIN_AFIO_AF(GPIOD_PITE, 0) |           \
                                     PIN_AFIO_AF(GPIOD_RSTI, 0))

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
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_ESS1) |           \
                                     PIN_MODE_INPUT(GPIOE_ESS2) |           \
                                     PIN_MODE_INPUT(GPIOE_ESS3) |           \
                                     PIN_MODE_OUTPUT(GPIOE_ESS4) |        \
                                     PIN_MODE_INPUT(GPIOE_ESS5) |           \
                                     PIN_MODE_INPUT(GPIOE_ESS6) |           \
                                     PIN_MODE_INPUT(GPIOE_ESS7) |           \
                                     PIN_MODE_INPUT(GPIOE_ESS8) |           \
                                     PIN_MODE_INPUT(GPIOE_ESS9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_ESS1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_ESS9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_100M(GPIOE_ESS1) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS2) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS3) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS4) |        \
                                     PIN_OSPEED_100M(GPIOE_ESS5) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS6) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS7) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS8) |          \
                                     PIN_OSPEED_100M(GPIOE_ESS9) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN9) |          \
                                     PIN_OSPEED_100M(GPIOE_PIN10) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN11) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN12) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN13) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN14) |         \
                                     PIN_OSPEED_100M(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_ESS1) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS2) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS3) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS4) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS5) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS6) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS7) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS8) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_ESS9) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_ESS1) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS2) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS3) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS4) |           \
                                     PIN_ODR_HIGH(GPIOE_ESS5) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS6) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS7) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS8) |             \
                                     PIN_ODR_HIGH(GPIOE_ESS9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_ESS1, 0) |           \
                                     PIN_AFIO_AF(GPIOE_ESS2, 0) |           \
                                     PIN_AFIO_AF(GPIOE_ESS3, 0) |           \
                                     PIN_AFIO_AF(GPIOE_ESS4, 0) |         \
                                     PIN_AFIO_AF(GPIOE_ESS5, 0) |           \
                                     PIN_AFIO_AF(GPIOE_ESS6, 0) |           \
                                     PIN_AFIO_AF(GPIOE_ESS7, 0) |           \
                                     PIN_AFIO_AF(GPIOE_ESS8, 0))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_ESS9, 0) |           \
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
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
