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
 * Aug 12, 2016
 */
/**
 * @file
 */
#ifndef UTIL_RTOS
#define UTIL_RTOS

#define FREERTOS

#if defined(FREERTOS)
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>
#elif defined(PTHREAD)
#error "Must create RTOS classes for pthread API"
#else
#error "Undefined operating system"
#endif


/****************************************************************************/
/* Base																		*/
/****************************************************************************/
#define BLOCK_UNTIL_READY portMAX_DELAY
#define POLL 0
typedef portBASE_TYPE COSBase;
#define CTICKS_TO_MS(ms) (ms/portTICK_RATE_MS)

/****************************************************************************/
/* Timing																	*/
/****************************************************************************/
#define CTaskDelay(ticks) 	vTaskDelay((ticks))
#define CTaskDelayMS(ms)	vTaskDelay(CTICKS_TO_MS((ms)))


/****************************************************************************/
/* Queues																	*/
/****************************************************************************/
typedef xQueueHandle COSQueue;

#define COSQUEUE_TIMEOUT 	pdFALSE
#define COSQUEUE_OK			pdTRUE

#define COSQueueCreate(depth, item_size)		xQueueCreate((depth), (item_size))
#define COSQueue_Insert(queue, item, block)		xQueueSend((queue), (item), (block))
#define COSQueue_Get(queue, item, block)		xQueueReceive((queue), (item), (block))
#define COSQueue_Peek(queue, item, block)		xQueuePeek((queue), (item), (block))


/****************************************************************************/
/* Semaphores																*/
/****************************************************************************/
typedef xSemaphoreHandle CSemaphore;
typedef xSemaphoreHandle CMutex;

#define CSEMAPHORE_TAKEN 	pdTRUE
#define CMUTEX_TAKEN 		pdTRUE
#define CSEMAPHORE_TIMEOUT 	pdFALSE
#define CMUTEX_TIMEOUT 		pdFALSE

#define CSemaphoreCreate(max, init) 	xSemaphoreCreateCounting((max), (init))
#define CSemaphoreCreateBinary( ) 		xSemaphoreCreateCounting(1, 0)
#define CSemaphoreDelete(sem)			vSemaphoreDelete((sem))
#define CSemaphore_Take(sem, timeout) 	xSemaphoreTake((sem), (timeout))
#define CSemaphore_Give(sem)			xSemaphoreGive((sem))
#define CSemaphore_Peek(sem, timeout)	xQueuePeek((sem), NULL, (timeout))

#define CMutexCreate( ) 				xSemaphoreCreateMutex( )
#define CMutexDelete(mutex)				vSemaphoreDelete((mutex))
#define CMutex_Take(mutex, timeout) 	xSemaphoreTake((mutex), (timeout))
#define CMutex_Give(mutex)				xSemaphoreGive((mutex))
#define CMutex_Peek(mutex, timeout)		xQueuePeek((mutex), NULL, (timeout))


/****************************************************************************/
/* Task																		*/
/****************************************************************************/
typedef xTaskHandle CTask;

#define CTASK_IDLE_PRIO	tskIDLE_PRIORITY
#define CTASK_CREATED	pdTRUE
#define CTASK_NO_ARG	NULL
#define CTASK_NO_HANDLE	NULL

#define CTaskCreate(task_function, task_name, task_stack, task_arg,	task_prio, task_handle)\
	xTaskCreate(task_function, task_name, task_stack, task_arg,	task_prio, task_handle)
#define CTaskDelete(task_handle) vTaskDelete((task_handle))

#endif /* UTIL_RTOS */
