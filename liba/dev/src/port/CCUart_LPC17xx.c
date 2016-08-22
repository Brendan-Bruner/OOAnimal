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

#include <chip.h>
#include <stdlib.h>
#include <CCUart.h>
#include <CError.h>
#include <limits.h>

/********************************************************************/
/* Defines															*/
/********************************************************************/
#define UART_PIN_MUX_LENGTH 2

/************************************************************************/
/* Methods																*/
/************************************************************************/
size_t CCUart_Tx( struct CCUart* self, const char* buffer, size_t buflen )
{
	CAssertObject(self);

	size_t buf_index;
	char ch;

	/* Move all data into tx queue.
	 */
	buf_index = 0;
	while( buf_index < buflen ) {
		ch = buffer[buf_index];
		++buf_index;

		COSBase err = COSQueue_Insert(self->tx_queue, &ch, POLL);
		if( err != COSQUEUE_OK ) {
			break;
		}
	}

	/* Enable UART transmit interrupt so it can begin filling its hardware
	 * FIFO with data from tx queue.
	 */
	Chip_UART_IntEnable(self->uart_port_type, UART_IER_THREINT);

	/* Return total number of bytes successful queued for tx.
	 */
	return buf_index;
}

size_t CCUart_Rx( struct CCUart* self, char* buffer, size_t buflen )
{
	CAssertObject(self);
	return CCUart_RxBlocking(self, buffer, buflen, POLL);
}

size_t CCUart_RxBlocking( struct CCUart* self, char* buffer, size_t buflen, COSTime block )
{
	CAssertObject(self);

	size_t buf_index;
	char ch;

	buf_index = 0;
	while( buf_index < buflen ) {
		COSBase err = COSQueue_Get(self->rx_queue, &ch, block);
		if( err != COSQUEUE_OK ) {
			break;
		}

		buffer[buf_index] = ch;
		++buf_index;
	}

	return buf_index;
}

size_t CCUart_Available( struct CCUart* self )
{
	CAssertObject(self);

	COSSize available = COSQueue_Available(self->rx_queue);

	if( available > SIZE_MAX ) {
		return SIZE_MAX;
	}
	return (size_t) available;
}

void CCUart_FlushRx( struct CCUart* self )
{
	CAssertObject(self);

	COSQueue_Reset(self->rx_queue);
}

void CCUart_FlushTx( struct CCUart* self )
{
	CAssertObject(self);

	COSQueue_Reset(self->tx_queue);
}


/************************************************************************/
/* vtable key															*/
/************************************************************************/
const struct CCUart_VTable* CCUart_VTable_Key( )
{
	static struct CCUart_VTable vtable;

	/* Copy of super's vtable. */
	vtable.CObject_VTable = *CObject_VTable_Key( );

	/* Return pointer to vtable. 
	 */
	return &vtable;
}


/************************************************************************/
/* Constructor															*/
/************************************************************************/
static CError CCUart( 	struct CCUart* self,
						LPC_USART_T* port,
						IRQn_Type irq_vector,
						const PINMUX_GRP_T* pin_mux,
						uint32_t baud_rate,
						uint32_t uart_config,
						uint32_t fifo_config
					)
{
	/* First thing in constructor must be to call super's constructor. 
	 */
	CObject(&self->cObject);

	/* Second thing in constructor must be to map vtable. 
	 */
	CVTable(self, CCUart_VTable_Key( ));

	/* Setup aggregate data.
	 */
	self->irq_vector = irq_vector;
	self->uart_port_type = port;

	/* Create tx and rx queues.
	 */
	self->rx_queue = COSQueueCreate(CCUART_RX_BUFSIZE, sizeof(char));
	if( self->rx_queue == NULL ) {
		return COBJ_ALLOC_FAIL;
	}

	self->tx_queue = COSQueueCreate(CCUART_TX_BUFSIZE, sizeof(char));
	if( self->tx_queue == NULL ) {
		COSQueueDelete(self->rx_queue);
		return COBJ_ALLOC_FAIL;
	}

	/* Mux the pins. */
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pin_mux, UART_PIN_MUX_LENGTH);

	/* Initialize uart hardware. */
	Chip_UART_Init(self->uart_port_type);
	Chip_UART_SetBaud(self->uart_port_type, baud_rate);
	Chip_UART_ConfigData(self->uart_port_type, uart_config);
	Chip_UART_SetupFIFOS(self->uart_port_type, fifo_config);
	Chip_UART_TXEnable(self->uart_port_type);

	/* Reset and enable FIFOs */
	Chip_UART_SetupFIFOS(self->uart_port_type, fifo_config);

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(self->uart_port_type, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* Enable interrupts in the NVIC */
	NVIC_SetPriority(self->irq_vector, 15);

	return COBJ_OK;
}


/************************************************************************/
/* Singleton retrieval functions										*/
/************************************************************************/
#ifdef CCUART_USE_UART0
static struct CCUart* uart0_p = NULL;
struct CCUart* CCUart_GetDev0( )
{
	static struct CCUart uart;

	if( uart0_p == NULL ) {
		const PINMUX_GRP_T uart_mux[] = 	{
											{0,  2,   IOCON_MODE_INACT | IOCON_FUNC1},	/* TXD0 */
											{0,  3,   IOCON_MODE_INACT | IOCON_FUNC1},	/* RXD0 */
											};
		CError err = CCUart(&uart, LPC_UART0, UART0_IRQn, uart_mux,
							CCUART0_DEFAULT_BAUD, CCUART0_DEFAULT_DEV_CONFIG, CCUART0_DEFAULT_FIFO_CONFIG);
		if( err == COBJ_OK ) {
			uart0_p = &uart;
		}
	}
	return uart0_p;
}
#endif

#ifdef CCUART_USE_UART1
static struct CCUart* uart1_p = NULL;
struct CCUart* CCUart_GetDev1( )
{
	static struct CCUart uart;

	if( uart1_p == NULL ) {
		const PINMUX_GRP_T uart_mux[] = 	{
											{0,  15,   IOCON_MODE_INACT | IOCON_FUNC1},	/* TXD1 */
											{0,  16,   IOCON_MODE_INACT | IOCON_FUNC1},	/* RXD1 */
											};
		CError err = CCUart(&uart, LPC_UART1, UART1_IRQn, uart_mux,
							CCUART1_DEFAULT_BAUD, CCUART1_DEFAULT_DEV_CONFIG, CCUART1_DEFAULT_FIFO_CONFIG);
		if( err == COBJ_OK ) {
			uart1_p = &uart;
		}
	}
	return uart1_p;
}
#endif

#ifdef CCUART_USE_UART2
static struct CCUart* uart2_p = NULL;
struct CCUart* CCUart_GetDev2( )
{
	static struct CCUart uart;

	if( uart2_p == NULL ) {
		const PINMUX_GRP_T uart_mux[] = 	{
											{0,  10,   IOCON_MODE_INACT | IOCON_FUNC1},	/* TXD2 */
											{0,  11,   IOCON_MODE_INACT | IOCON_FUNC1},	/* RXD2 */
											};
		CError err = CCUart(&uart, LPC_UART2, UART2_IRQn, uart_mux,
							CCUART2_DEFAULT_BAUD, CCUART2_DEFAULT_DEV_CONFIG, CCUART2_DEFAULT_FIFO_CONFIG);
		if( err == COBJ_OK ) {
			uart2_p = &uart;
		}
	}
	return uart2_p;
}
#endif

#ifdef CCUART_USE_UART3
static struct CCUart* uart3_p = NULL;
struct CCUart* CCUart_GetDev3( )
{
	static struct CCUart uart;

	if( uart3_p == NULL ) {
		const PINMUX_GRP_T uart_mux[] = 	{
											{0,  0,   IOCON_MODE_INACT | IOCON_FUNC2},	/* TXD3 */
											{0,  1,   IOCON_MODE_INACT | IOCON_FUNC2},	/* RXD3 */
											};
		CError err = CCUart(&uart, LPC_UART3, UART3_IRQn, uart_mux,
							CCUART3_DEFAULT_BAUD, CCUART3_DEFAULT_DEV_CONFIG, CCUART3_DEFAULT_FIFO_CONFIG);
		if( err == COBJ_OK ) {
			uart3_p = &uart;
		}
	}
	return uart3_p;
}
#endif


/********************************************************************/
/* ISRs																*/
/********************************************************************/
static void CCUart_ISRHandle( struct CCUart* self )
{
	COSBase task_woken_tx = CTASK_NONE_WOKEN;
	COSBase task_woken_rx = CTASK_NONE_WOKEN;

	/* Handle transmit interrupt if enabled
	 */
	if( self->uart_port_type->IER & UART_IER_THREINT ) {
		uint8_t ch;

		/* Fill tx FIFO until full or until there is no data to put into tx fifo.
		 */
		while( (Chip_UART_ReadLineStatus(self->uart_port_type) & UART_LSR_THRE) != 0 &&
			   COSQueue_GetFromISR(self->tx_queue, &ch, &task_woken_tx) == COSQUEUE_OK ) {
			Chip_UART_SendByte(self->uart_port_type, ch);
		}

		/* Disable transmit interrupt if there is no data left to put into tx FIFO.
		 */
		if( COSQueue_AvailableFromISR(self->tx_queue) == 0 ) {
			Chip_UART_IntDisable(self->uart_port_type, UART_IER_THREINT);
		}
	}

	/* Handle receive interrupt
	 */
	while (Chip_UART_ReadLineStatus(self->uart_port_type) & UART_LSR_RDR) {
		uint8_t ch = Chip_UART_ReadByte(self->uart_port_type);
		COSQueue_InsertFromISR(self->rx_queue, &ch, &task_woken_rx);
	}

//	/* Handle End Of Autobaud interrupt
//	 */
//	if((Chip_UART_ReadIntIDReg(self->uart_port_type) & UART_IIR_ABEO_INT) != 0) {
//        Chip_UART_SetAutoBaudReg(self->uart_port_type, UART_ACR_ABEOINT_CLR);
//		Chip_UART_IntDisable(self->uart_port_type, UART_IER_ABEOINT);
//	}
//
//    /* Handle Autobaud Timeout interrupt
//     */
//	if((Chip_UART_ReadIntIDReg(self->uart_port_type) & UART_IIR_ABTO_INT) != 0) {
//        Chip_UART_SetAutoBaudReg(self->uart_port_type, UART_ACR_ABTOINT_CLR);
//		Chip_UART_IntDisable(self->uart_port_type, UART_IER_ABTOINT);
//	}

    /* Send request for context switch if a task was unblocked by
     * reading/writing from tx/rx queues.
     */
    if( task_woken_tx == CTASK_WOKEN || task_woken_rx == CTASK_WOKEN ) {
    	 taskYIELD( );
    }
}

#ifdef CCUART_USE_UART0
void UART0_IRQHandler(void)
{
	CCUart_ISRHandle(uart0_p);
}
#endif

#ifdef CCUART_USE_UART1
void UART1_IRQHandler(void)
{
	CCUart_ISRHandle(uart1_p);
}
#endif

#ifdef CCUART_USE_UART2
void UART2_IRQHandler(void)
{
	CCUart_ISRHandle(uart2_p);
}
#endif

#ifdef CCUART_USE_UART3
void UART3_IRQHandler(void)
{
	CCUart_ISRHandle(uart3_p);
}
#endif


/********************************************************************/
/* Uart gateway														*/
/********************************************************************/
//void CCUart_GatewayTask( void* args )
//{
//
//}
