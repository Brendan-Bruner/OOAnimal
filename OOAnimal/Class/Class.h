/*
 * Class.h
 *
 *  Created on: 2014-11-26
 *      Author: brendan
 */

#ifndef CLASS_H_
#define CLASS_H_

#define Constructor(D)	void new##D(D *this)

#define Class(D)	typedef struct _##D D;		\
					Constructor(D);			\
					struct _##D					\
					{
						/* Super class */
#define Data			struct					\
						{
							/* Class data */
#define Methods			} data;
						/* Function pointers */
#define End			}

#define extends(S)	S super;

#endif /* CLASS_H_ */
