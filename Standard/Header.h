/* Header template for classes
 * Copyright (C) 2014 Brendan Bruner
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 */

#ifndef ${include_guard_symbol}
#define ${include_guard_symbol}

/* TODO: include all headers */
/* TODO: include super classes header (if inheriting). */

/******************************************************************************
 * Class ${file_base}
 *****************************************************************************/
/* TODO: Document ${file_base} class. */
typedef struct ${file_base} ${file_base};

/******************************************************************************
 * Class ${file_base} data members
 *****************************************************************************/
/* TODO: Document struct data_${file_base} members */
struct data_${file_base}
{
	/* TODO: Declariation of class data members. */
};

/******************************************************************************
 * vtable prototype
 *****************************************************************************/
struct vtable_${file_base}
{
	/* TODO: Declariation of pointers to class functions */
	/*	 Do not include constructor and destructor   */
};

/******************************************************************************
 * Class data structure
 *****************************************************************************/
struct ${file_base}
{
	/* *********************** IMPORTANT ************************** */
	/*    super class must be first data member for struct.		*/
	/*    If the class has no super class ignore this message.	*/
	/* TODO: Super class */
	struct vtable_${file_base} vtable;
	struct data_${file_base} _data;
};

/******************************************************************************
 * Constructor and destructor prototypes
 *****************************************************************************/
/* TODO: Customize constructor */
/* TODO: If customizing constructor then document changes. */
/**
 * Constructor.
 * Initializes an object.
 * @param this Object to initialize.
 */
void new_${file_base}(${file_base} *this);

/**
 * Destructor.
 * @param this The object to destroy.
 */
void destroy_${file_base}(${file_base} *this);

#endif /* ${include_guard_symbol} */
