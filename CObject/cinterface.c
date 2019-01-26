/*
 * Copyright 2019 Brendan Bruner
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
 * Nov. 2015
 */
/**
 * @file
 */

/*
 * ==========================================================================
 * ------------------------------ Includes ----------------------------------
 * ==========================================================================
 */
#include "cinterface.h"

/*
 * ==========================================================================
 * ----------------------- Function Definitions- ----------------------------
 * ==========================================================================
 */
void cinterface_init( void* self, void* iface, const void* vtable )
{
        /* iface is suppose to be an interface, therefore, we assume that
         * the first variable in the structures definition is of type
         * cclass_t
         */
        struct cclass_t* iface_class = iface;
        
	iface_class->croot = self;
        cclass_set_cvtable(iface, vtable);
}

