#include "UART.h"
#include "debug.h"

/* Buffer for hello world message */
const char hello_msg[] = "Hola Mundo\r\n";
volatile uint32_t tick_count = 0;

/*********************************************************************
 * @fn      send_hello
 *
 * @brief   Sends hello world message through USB CDC
 *
 * @return  none
 */
void send_hello(void)
{
    uint16_t len = strlen(hello_msg);

    printf("Attempting USB send... ");

    /* Wait for endpoint to be free */
    while(USBHS_Endp_Busy[DEF_UEP2]);

    /* Clear endpoint busy flag before starting new transfer */
    USBHS_Endp_Busy[DEF_UEP2] = 0;

    /* Copy data to endpoint buffer */
    memcpy(USBHS_EP2_Tx_Buf, hello_msg, len);

    /* Set endpoint length and trigger transmission */
    USBHSD->UEP2_TX_LEN = len;
    USBHSD->UEP2_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;

    /* Mark endpoint as busy */
    USBHS_Endp_Busy[DEF_UEP2] = 1;

    printf("sent %d bytes\r\n", len);
}

/*********************************************************************
 * @fn      increment_tick
 *
 * @brief   Increment tick counter, called from TIM2_IRQHandler
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
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t i;

    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);

    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    printf("USB-CDC Hello World Demo\r\n");

    /* Initialize system clocks */
    RCC_Configuration();

    /* Initialize Timer2 for 100uS intervals */
    TIM2_Init();

    /* Initialize USB device */
    USBHS_RCC_Init();

    /* Initialize endpoints */
    USBHS_Device_Endp_Init();

    /* Start USB device */
    USBHS_Device_Init(ENABLE);

    printf("Waiting for USB enumeration...\r\n");

    /* Wait for USB enumeration */
    while(USBHS_DevEnumStatus == 0)
    {
        Delay_Ms(100);
    }

    printf("USB enumerated successfully!\r\n");
    printf("Starting main loop...\r\n");

    /* Send an initial test pattern */
    for(i = 0; i < DEF_USB_EP2_HS_SIZE && i < 64; i++) {
        USBHS_EP2_Tx_Buf[i] = i;
    }

    printf("Sending initial test pattern...\n");
    USBHSD->UEP2_TX_LEN = 64;
    USBHSD->UEP2_TX_CTRL = (USBHSD->UEP2_TX_CTRL & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK;

    Delay_Ms(1000);

    while(1)
    {
        /* Send message every 5 seconds */
        if(tick_count >= 50000)
        {
            printf("5 seconds elapsed, sending message\r\n");
            tick_count = 0;
            send_hello();

            /* Add a small delay after sending */
            Delay_Ms(10);
        }
    }
}
