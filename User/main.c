/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH / Modified by UBNTOMAR
* Version            : V1.0.0
* Date               : 2024/01/xx
* Description        : Main program body for USB CDC example
*
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/*
 * Este ejemplo muestra cómo implementar un dispositivo USB CDC básico usando el CH32V305FBP6
 * utilizando el controlador USB de alta velocidad (High Speed - HS).
 * NOTA: Este microcontrolador solo dispone de USB HS, no tiene USB FS.
 *
 * This example shows how to implement a basic USB CDC device using the CH32V305FBP6
 * using the High Speed USB controller.
 * NOTE: This microcontroller only has USB HS, it does not have USB FS.
 *
 * Hardware:
 * - CH32V305FBP6 microcontroller
 * - USB HS peripheral (único controlador USB disponible en este IC)
 *
 * Connection:
 * - USB DP (D+) -> PB7
 * - USB DM (D-) -> PB6
 */

#include "UART.h"
#include "debug.h"

/* Mensaje a enviar / Message to send */
const char hello_msg[] = "Hola Mundo\r\n";

/* Contador para el temporizador / Timer counter */
volatile uint32_t tick_count = 0;

/*********************************************************************
 * @fn      send_hello
 *
 * @brief   Envía el mensaje a través de USB CDC
 *          Sends the message through USB CDC
 *
 * @return  none
 */
void send_hello(void)
{
    uint16_t len = strlen(hello_msg);

    printf("Intentando enviar por USB... / Attempting USB send... ");

    /* Espera a que el endpoint esté libre
     * Wait for endpoint to be free */
    while(USBHS_Endp_Busy[DEF_UEP2]);

    /* Limpia el flag de ocupado antes de iniciar nueva transferencia
     * Clear busy flag before starting new transfer */
    USBHS_Endp_Busy[DEF_UEP2] = 0;

    /* Copia datos al buffer del endpoint
     * Copy data to endpoint buffer */
    memcpy(USBHS_EP2_Tx_Buf, hello_msg, len);

    /* Configura longitud y dispara transmisión
     * Set length and trigger transmission */
    USBHSD->UEP2_TX_LEN = len;
    USBHSD->UEP2_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;

    /* Marca el endpoint como ocupado
     * Mark endpoint as busy */
    USBHS_Endp_Busy[DEF_UEP2] = 1;

    printf("enviados %d bytes / sent %d bytes\r\n", len, len);
}

/*********************************************************************
 * @fn      increment_tick
 *
 * @brief   Incrementa el contador del temporizador, llamado desde TIM2_IRQHandler
 *          Increments timer counter, called from TIM2_IRQHandler
 *
 * @return  none
 */
void increment_tick(void)
{
    tick_count++;
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Función principal.
 *          Main function
 *
 * @return  none
 */
int main(void)
{
    uint8_t i;

    /* Inicialización básica del sistema / Basic system initialization */
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);

    printf("\r\n");
    printf("******************************************\r\n");
    printf("USB CDC Example for CH32V307 (USB HS)\r\n");
    printf("SystemClk:%d Hz\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    printf("******************************************\r\n");

    /* Inicializa relojes del sistema / Initialize system clocks */
    RCC_Configuration();

    /* Inicializa Timer2 para intervalos de 100uS
     * Initialize Timer2 for 100uS intervals */
    TIM2_Init();

    /* Inicialización del USB HS / USB HS initialization */
    printf("Inicializando USB HS... / Initializing USB HS...\r\n");
    USBHS_RCC_Init();
    USBHS_Device_Endp_Init();
    USBHS_Device_Init(ENABLE);

    printf("Esperando enumeración USB... / Waiting for USB enumeration...\r\n");

    /* Espera a que el dispositivo sea enumerado
     * Wait for device enumeration */
    while(USBHS_DevEnumStatus == 0)
    {
        Delay_Ms(100);
    }

    printf("¡USB enumerado exitosamente! / USB enumerated successfully!\r\n");

    /* Envía un patrón inicial de prueba (0-63)
     * Send initial test pattern (0-63) */
    printf("Enviando patrón de prueba... / Sending test pattern...\r\n");
    for(i = 0; i < DEF_USB_EP2_HS_SIZE && i < 64; i++) {
        USBHS_EP2_Tx_Buf[i] = i;
    }

    USBHSD->UEP2_TX_LEN = 64;
    USBHSD->UEP2_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;

    Delay_Ms(1000);

    printf("Iniciando bucle principal / Starting main loop\r\n");

    while(1)
    {
        /* Envía mensaje cada 5 segundos (50000 * 100uS = 5s)
         * Send message every 5 seconds */
        if(tick_count >= 50000)
        {
            printf("5 segundos transcurridos / 5 seconds elapsed\r\n");
            tick_count = 0;
            send_hello();

            /* Pequeña pausa después del envío
             * Small delay after sending */
            Delay_Ms(10);
        }
    }
}
