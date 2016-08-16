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
#ifndef TERM_DEFINES
#define TERM_DEFINES

/****************************************************************************/
/* CCTerminal Defines														*/
/****************************************************************************/
/* Max length of command prompt string.
 */
#define CCTERMINAL_PROMPT_LENGTH	16

/* Max length of input string to terminal.
 */
#define CCTERMINAL_MAX_INPUT_LENGTH	64

/* Error messages printed to terminal.
 */
#define CCTERMINAL_UNKOWN_PROGRAM_MSG	"command not found"
#define CCTERMINAL_NO_MEMORY_MSG		"memory low, try again later"
#define CCTERMINAL_HARD_ERROR_MSG		"unexpected termination of program\nassociate object failure"
#define CCTERMINAL_SYNTAX_ERROR_MSG		"unkown syntax"
#define CCTERMINAL_ARGS_ERROR_MSG		"invalid arguments"

/* Task parameters.
 */
#define CCTERMINAL_TASK_NAME		((const signed char*) "terminal")
#define CCTERMINAL_TASK_STACK		(128 + CCTERMINAL_MAX_INPUT_LENGTH)
#define CCTERMINAL_TASK_PRIO		(tskIDLE_PRIORITY+1)


/****************************************************************************/
/* CCProgram Defines														*/
/****************************************************************************/
/* Maximum arguments that can be given to a program.
 */
#define CCPROGRAM_MAX_ARG_COUNT 8
#define CCPROGRAM_MAX_NAME_LENGTH 16

/* Max length of input string to CCProgram_Run()
 */
#define CCPROGRAM_MAX_INPUT_LENGTH	64

/* Maximum number of programs which can be kept at one time.
 */
#define CCPROGRAM_LIST_MAX_PROGRAMS 16

/* Name of programs.
 */
#define CCPROGRAM_LIST_NAME	"help"
#define CCPING_PROGRAM_NAME "ping"

#endif /* TERM_DEFINES */
