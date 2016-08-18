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
 * Jun 19, 2016
 */

#include <unit.h>
#include <chip.h>
#include <CCDebugPrint.h>
#include <FreeRTOS.h>
#include <task.h>
#include <CCTerminal.h>
#include <CCProgramList.h>
#include <CCPing.h>
#include <CCUart.h>
#include <CCUartPrint.h>
#include <string.h>

extern TEST_SUITE(destructor_suite);
extern TEST_SUITE(virtual_suite);
extern TEST_SUITE(interface_suite);
extern TEST_SUITE(array_queue);
extern TEST_SUITE(array_list);
extern TEST_SUITE(array_list_iterator);
extern TEST_SUITE(binary_tree);

static struct CCTerminal terminal;
static struct CCPing ping;
static struct CCProgramList prog_list;
static void main_task( void* term_ )
{
	/* Start the debug console.
	 */
	struct CCUart* uart = CCUart_GetDev2( );
	struct CCUartPrint uart_printer;
	CCUartPrint(&uart_printer, uart);
	struct CIPrint* printer = &uart_printer.cIPrint;
	CCPing(&ping, printer);
	CCProgramList(&prog_list, printer);
	CCProgramList_Add(&prog_list, &ping.cCProgram);
	CCTerminal(&terminal, printer, "debug$ ", &prog_list);
	CCTerminal_Start(&terminal);

	/* Setup uart2 to print to console.
	 */

	for( ;; ) {
//		CIPrint_String(&uart_printer.cIPrint, "Enter a letter: ");
//		char letter = CIPrint_GetChar(&uart_printer.cIPrint);
//		CIPrint_StringF(&uart_printer.cIPrint, "%c\n", letter);
//		CIPrint_StringF(&uart_printer.cIPrint, "You entered: %c\n", letter);
		vTaskDelay(1000/portTICK_RATE_MS);
	}
}

#if defined (__USE_LPCOPEN)
int main( void )
{
	SystemCoreClockUpdate();
#else
int main( int argc, char** argv )
{
	(void) argc; (void) argv;
#endif
//	RUN_TEST_SUITE(destructor_suite);
//	RUN_TEST_SUITE(virtual_suite);
//	RUN_TEST_SUITE(interface_suite);
//	RUN_TEST_SUITE(array_queue);
//	RUN_TEST_SUITE(array_list);
//	RUN_TEST_SUITE(array_list_iterator);
//	RUN_TEST_SUITE(binary_tree);
//	PRINT_DIAG( );
	xTaskCreate(main_task, "main task", 256, NULL, tskIDLE_PRIORITY+2, NULL);

	vTaskStartScheduler( );

#if defined(__USE_LPCOPEN)
	for(;;);
#endif

	return 0;
}
