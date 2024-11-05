/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v30x_it.c
* Author             : WCH / Modified by UBNTOMAR
* Version            : V1.0.0
* Date               : 2024/01/xx
* Description        : Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2024 UBNTOMAR
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include "ch32v30x_it.h"
#include "UART.h"

/* Global Variable for tick count */
extern volatile uint32_t tick_count;
extern void increment_tick(void);

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
    while (1)
    {
    }
}

/*********************************************************************
 * @fn      TIM2_IRQHandler
 *
 * @brief   This function handles TIM2 global interrupt request.
 *          Modificado para manejar nuestro contador de tiempo para USB CDC
 *          Modified to handle our USB CDC time counter
 *
 * @return  none
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        /* Increment our custom tick counter */
        increment_tick();

        /* Process UART timeout events */
        if(Uart.Rx_TimeOut < 0xFFFF)
        {
            Uart.Rx_TimeOut++;
        }
        if(Uart.USB_Up_TimeOut < 0xFFFF)
        {
            Uart.USB_Up_TimeOut++;
        }

        /* Clear interrupt flag */
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
