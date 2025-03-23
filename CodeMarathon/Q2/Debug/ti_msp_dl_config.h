/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                              32768
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_33_kHZ_9600_BAUD                                         (1)
#define UART_0_FBRD_33_kHZ_9600_BAUD                                         (9)





/* Defines for BTN_PA18: GPIOA.18 with pinCMx 40 on package pin 11 */
#define GPIO_GRP_0_BTN_PA18_PORT                                         (GPIOA)
// pins affected by this interrupt request:["BTN_PA18"]
#define GPIO_GRP_0_GPIOA_INT_IRQN                               (GPIOA_INT_IRQn)
#define GPIO_GRP_0_GPIOA_INT_IIDX               (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_GRP_0_BTN_PA18_IIDX                            (DL_GPIO_IIDX_DIO18)
#define GPIO_GRP_0_BTN_PA18_PIN                                 (DL_GPIO_PIN_18)
#define GPIO_GRP_0_BTN_PA18_IOMUX                                (IOMUX_PINCM40)
/* Defines for BTN_PB21: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_GRP_0_BTN_PB21_PORT                                         (GPIOB)
// pins affected by this interrupt request:["BTN_PB21"]
#define GPIO_GRP_0_GPIOB_INT_IRQN                               (GPIOB_INT_IRQn)
#define GPIO_GRP_0_GPIOB_INT_IIDX               (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define GPIO_GRP_0_BTN_PB21_IIDX                            (DL_GPIO_IIDX_DIO21)
#define GPIO_GRP_0_BTN_PB21_PIN                                 (DL_GPIO_PIN_21)
#define GPIO_GRP_0_BTN_PB21_IOMUX                                (IOMUX_PINCM49)
/* Defines for LED_PB22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_GRP_0_LED_PB22_PORT                                         (GPIOB)
#define GPIO_GRP_0_LED_PB22_PIN                                 (DL_GPIO_PIN_22)
#define GPIO_GRP_0_LED_PB22_IOMUX                                (IOMUX_PINCM50)
/* Defines for LED_PB26: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_GRP_0_LED_PB26_PORT                                         (GPIOB)
#define GPIO_GRP_0_LED_PB26_PIN                                 (DL_GPIO_PIN_26)
#define GPIO_GRP_0_LED_PB26_IOMUX                                (IOMUX_PINCM57)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
