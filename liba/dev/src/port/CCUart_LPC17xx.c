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

	size_t bytes = 0;

	if( buflen > INT_MAX ) {
		return 0;
	}

	/* loop until everything is transmitted.
	 */
	CMutex_Take(self->tx_mutex, BLOCK_UNTIL_READY);
	while( buflen > 0 )
	{
		CSemaphore_Take(self->send_sync, BLOCK_UNTIL_READY);
		bytes += Chip_UART_SendRB(self->uart_port_type, &self->tx_ring, buffer + bytes, (int) buflen);
		buflen = buflen - bytes;
	}
	CMutex_Give(self->rx_mutex);

	return bytes;
}

size_t CCUart_Rx( struct CCUart* self, char* buffer, size_t buflen )
{
	CAssertObject(self);

	if( buflen > INT_MAX ) {
		return 0;
	}

	CMutex_Take(self->rx_mutex, BLOCK_UNTIL_READY);
	int read = Chip_UART_ReadRB(self->uart_port_type, &self->rx_ring, buffer, (int) buflen);
	CMutex_Give(self->rx_mutex);

	if( read < 0 ) {
		return 0;
	}
	return (size_t) read;
}

size_t CCUart_Available( struct CCUart* self )
{
	CAssertObject(self);

	int available = RingBuffer_GetFree(&self->rx_ring);

	if( available < 0 ) {
		return 0;
	}
	return (size_t) available;
}

void CCUart_FlushRx( struct CCUart* self )
{
	CAssertObject(self);

	RingBuffer_Flush(&self->rx_ring);
}

void CCUart_FlushTx( struct CCUart* self )
{
	CAssertObject(self);

	RingBuffer_Flush(&self->tx_ring);
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

	/* Create sync semaphore.
	 */
	self->send_sync = CSemaphoreCreateBinary( );
	if( self->send_sync == NULL ) {
		/* Error creating semaphore.
		 */
		return COBJ_ALLOC_FAIL;
	}
	CSemaphore_Give(self->send_sync);

	self->rx_mutex = CMutexCreate( );
	if( self->rx_mutex == NULL ) {
		CSemaphoreDelete(self->send_sync);
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

	/* Initialize ring buffers. */
	RingBuffer_Init(&self->rx_ring, self->rx_buff, sizeof(*self->rx_buff), CCUART_RX_RING_BUFSIZE );
	RingBuffer_Init(&self->tx_ring, self->tx_buff, sizeof(*self->tx_buff), CCUART_TX_RING_BUFSIZE );

	/* Reset and enable FIFOs */
	Chip_UART_SetupFIFOS(self->uart_port_type, fifo_config);

	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(self->uart_port_type, (UART_IER_RBRINT | UART_IER_RLSINT));

	/* Enable interrupts in the NVIC */
	NVIC_SetPriority(self->irq_vector, 1);
	NVIC_EnableIRQ(self->irq_vector);

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
#ifdef CCUART_USE_UART0
void UART0_IRQHandler(void)
{
	Chip_UART_IRQRBHandler(uart0_p->uart_port_type, &uart0_p->rx_ring, &uart0_p->tx_ring);
	CSemaphore_Give(uart0_p->send_sync);
}
#endif

#ifdef CCUART_USE_UART1
void UART1_IRQHandler(void)
{
	Chip_UART_IRQRBHandler(uart1_p->uart_port_type, &uart1_p->rx_ring, &uart1_p->tx_ring);
	CSemaphore_Give(uart1_p->send_sync);
}
#endif

#ifdef CCUART_USE_UART2
void UART2_IRQHandler(void)
{
	Chip_UART_IRQRBHandler(uart2_p->uart_port_type, &uart2_p->rx_ring, &uart2_p->tx_ring);
	CSemaphore_Give(uart2_p->send_sync);
}
#endif

#ifdef CCUART_USE_UART3
void UART3_IRQHandler(void)
{
	Chip_UART_IRQRBHandler(uart3_p->uart_port_type, &uart3_p->rx_ring, &uart3_p->tx_ring);
	CSemaphore_Give(uart3_p->send_sync);
}
#endif


/********************************************************************/
/* Uart gateway														*/
/********************************************************************/
//void CCUart_GatewayTask( void* args )
//{
//
//}
