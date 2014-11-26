/*
 * Class.h
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#ifndef CLASS_H_
#define CLASS_H_

#define Class(D)	typedef struct _##D D;		\
					void new_##D(D *);			\
					struct _##D					\
					{
						/* Super class */

#define Data			struct					\
						{
							/* Class data */

#define Methods			} data;					\
						struct					\
						{
							/* Function pointers */

#define End				} method;				\
					}

#define extends(S)	S super;

#endif /* CLASS_H_ */
