/*
 * Copyright (C) 2015  Brendan Bruner
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * bbruner@ualberta.ca
 *
 * This test suite was inspired from the test suite at:
 * http://www.jera.com/techinfo/jtns/jtn002.html - January 2015
 */

#include "unit.h"

unsigned int unit_asserts_passed = 0, delta_unit_asserts_passed = 0;
unsigned int unit_asserts_failed = 0, delta_unit_asserts_failed = 0;
unsigned int unit_tests_run = 0;
unsigned int unit_tests_aborted = 0;
unsigned int unit_asserts_failed_pre_test = 0;
unsigned int unit_tests_passed = 0, unit_tests_failed = 0;
