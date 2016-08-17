/*
 * Copyright 2015 Brendan Bruner
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * bbruner@ualberta.ca
 * Aug 17, 2016
 */
/**
 * @file
 */
#ifndef DEV_DEFINES
#define DEV_DEFINES


/************************************************************************/
/* CIPrint																*/
/************************************************************************/
/* Maximum string length when printing using the CCUartPrint class.
 */
#define CCUART_PRINTER_MAX_STRING 128

/************************************************************************/
/* CCUart																*/
/************************************************************************/
/* Size of rx buffer.
 */
#define CCUART_RX_RING_BUFSIZE 128

/* Size of tx buffer
 */
#define CCUART_TX_RING_BUFSIZE 128

/* Define these to enable the compilation of code for the
 * uart port.
 */
#define CCUART_USE_UART0
#define CCUART_USE_UART1
#define CCUART_USE_UART2
#define CCUART_USE_UART3

/* Default uart parameters for the different uart ports.
 */
#define CCUART0_DEFAULT_BAUD		115200
#define CCUART0_DEFAULT_DEV_CONFIG	(UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS )
#define CCUART0_DEFAULT_FIFO_CONFIG	(UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV0)

#define CCUART1_DEFAULT_BAUD		115200
#define CCUART1_DEFAULT_DEV_CONFIG	(UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS )
#define CCUART1_DEFAULT_FIFO_CONFIG	(UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV0)

#define CCUART2_DEFAULT_BAUD		115200
#define CCUART2_DEFAULT_DEV_CONFIG	(UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS )
#define CCUART2_DEFAULT_FIFO_CONFIG	(UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV0)

#define CCUART3_DEFAULT_BAUD		115200
#define CCUART3_DEFAULT_DEV_CONFIG	(UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS )
#define CCUART3_DEFAULT_FIFO_CONFIG	(UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV0)


#endif /* DEV_DEFINES */
