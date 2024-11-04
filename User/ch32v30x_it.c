#include "ch32v30x_it.h"
#include "UART.h"

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
 *
 * @return  none
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        /* Increment our tick counter */
        increment_tick();

        /* Process normal UART timeout events */
        if(Uart.Rx_TimeOut < 0xFFFF) Uart.Rx_TimeOut++;
        if(Uart.USB_Up_TimeOut < 0xFFFF) Uart.USB_Up_TimeOut++;

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
