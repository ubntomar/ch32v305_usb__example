# Technical Guide - USB CDC Example CH32V305

[🇬🇧 English Version](#english-technical-guide) | [🇪🇸 Versión en Español](/TECHNICAL_GUIDE_ES.md)

*Note: Full Spanish version available in TECHNICAL_GUIDE_ES.md file*

# English Technical Guide

## Table of Contents
1. [Basic Concepts](#1-basic-concepts)
2. [Project Structure](#2-project-structure)
3. [Key Components](#3-key-components)
4. [Practical Examples](#4-practical-examples)
5. [Common Debugging](#5-common-debugging)
6. [Additional Resources](#6-additional-resources)

## 1. Basic Concepts

### 1.1 What is USB CDC?
USB CDC (Communications Device Class) is a standard that allows a USB device to behave as a serial port. When you connect the device to your PC:
- It appears as a virtual COM port
- You can communicate with it using any serial terminal
- No special drivers required (uses standard system CDC drivers)

Example:
```
PC (Terminal) <---> USB <---> CH32V305 (our device)
        COM3 <------> Virtual Serial Port
```

### 1.2 USB HS vs USB FS
- FS (Full Speed): 12 Mbps
- HS (High Speed): 480 Mbps
- CH32V305FBP6 only has USB HS
- Configuration is different from USB FS, which is why many generic examples don't work

## 2. Project Structure

### 2.1 Key Files
```plaintext
project/
├── main.c                 # Main program and USB CDC implementation
├── ch32v30x_it.c         # Interrupt handlers and timing system
├── UART.c                # USB-UART bridge functions
└── UART.h                # Configurations and definitions
```

### 2.2 Program Flow
```plaintext
Initialization
    ├── System Clock Configuration
    ├── Timer (TIM2) Setup - 100µs intervals
    ├── USB HS Initialization
    └── Endpoint Configuration

Main Loop
    ├── Wait for USB Enumeration
    ├── Send Initial Test Pattern
    └── Every 5 seconds:
        └── Send "Hello World"
```

## 3. Key Components

### 3.1 Timer System
The timing system is crucial for periodic message sending:
```c
// Timer configuration (100µs intervals)
TIM_TimeBaseStructure.TIM_Period = 100 - 1;
TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 1000000 - 1;

// Counting mechanism
volatile uint32_t tick_count = 0;  // Incremented every 100µs
// 50000 ticks = 5 seconds (50000 * 100µs)
```

### 3.2 USB Communication
Key elements of USB communication:

1. **Endpoint Configuration**:
```c
USBHS_Device_Endp_Init();  // Initialize endpoints
```

2. **Data Transmission**:
```c
void send_hello(void)
{
    // Wait for endpoint to be free
    while(USBHS_Endp_Busy[DEF_UEP2]);
    
    // Copy data and configure transmission
    memcpy(USBHS_EP2_Tx_Buf, hello_msg, len);
    USBHSD->UEP2_TX_LEN = len;
    
    // Trigger transmission
    USBHSD->UEP2_TX_CTRL = USBHS_UEP_T_RES_ACK;
}
```

### 3.3 Interrupt Handling
Critical modifications in ch32v30x_it.c:
```c
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        increment_tick();           // For message timing
        /* UART timeout handling */
        if(Uart.Rx_TimeOut < 0xFFFF) Uart.Rx_TimeOut++;
        if(Uart.USB_Up_TimeOut < 0xFFFF) Uart.USB_Up_TimeOut++;
        
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
```

## 4. Practical Examples

### 4.1 Modifying Message Interval
To change the message interval from 5 seconds to 2 seconds:
```c
// In main loop
if(tick_count >= 20000)  // 20000 * 100µs = 2s
{
    tick_count = 0;
    send_hello();
}
```

### 4.2 Changing the Message
Send different types of messages:
```c
// Simple message
const char hello_msg[] = "Test Message\r\n";

// Formatted data
char buffer[64];
int value = 123;
sprintf(buffer, "Sensor Value: %d\r\n", value);
```

### 4.3 Adding Status LED
```c
// In initialization
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOA, &GPIO_InitStructure);

// In main loop
GPIO_SetBits(GPIOA, GPIO_Pin_15);    // LED ON
Delay_Ms(100);
GPIO_ResetBits(GPIOA, GPIO_Pin_15);  // LED OFF
```

## 5. Common Debugging

### 5.1 Hardware Verification
1. **USB Pins Check**
   - PB6 (D-): Should have ~0.3V at idle
   - PB7 (D+): Should have ~0.3V at idle

2. **Power Supply**
   - Verify 3.3V supply to MCU
   - Check USB bus voltage (5V)

### 5.2 Software Debugging
1. **Enumeration Issues**
   - Monitor debug UART output
   - Check USBHS_DevEnumStatus
   - Verify USB initialization sequence

2. **Data Transmission Problems**
   - Check endpoint busy flags
   - Monitor TIM2 interrupt execution
   - Verify message buffer contents

### 5.3 Common Issues and Solutions
1. **No USB Enumeration**
   - Verify USB connections (PB6/PB7)
   - Check USB driver installation
   - Monitor USB power status

2. **No Data Reception**
   - Verify COM port settings (9600 8N1)
   - Check message formatting (\r\n)
   - Monitor transmission timing

## 6. Additional Resources

### 6.1 Documentation
- [CH32V305 Reference Manual](http://www.wch-ic.com/downloads/CH32V305DS0_PDF.html)
- [USB 2.0 Specification](https://www.usb.org/document-library/usb-20-specification)
- [WCH Official Website](http://www.wch-ic.com/)

### 6.2 Tools
1. MounRiver Studio
2. USB Protocol Analyzer
3. Serial Terminal (PuTTY recommended)
4. Oscilloscope (for signal debugging)

### 6.3 Support
- GitHub Issues
- WCH Technical Forum
- Community Support Channels