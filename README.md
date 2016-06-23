#CObject
---

CObject is a small set of macros and functions for using fundamental object oriented concepts (OO) in the C language. 

* Classes
* Single inheritance
* Interfaces
* Virtual methods

It's implementation is designed to be as simple as possible, making application code intuitive to develop and easier to debug. 

The memory footprint of objects are:

| Data Type | Minimum |
|:---|:---|
| Class | sizeof(void\*) + 2\*sizeof(void(\*)(void)) |
| Interface | sizeof(void\*) |

CObject is c99 compliant. 

###Compile Time and Run Time Checks

Run time checks are (optionally) done to catch errors the compiler can't. **When compiling, the symbol DEBUG must be defined for run time checks to be used**.

When a run time check fails, an error will be printed to console and the program execution halted. The printed message will explain the most likely cause of failure and common solutions. Since different systems have different requirements, hooks are provided to changed the behaviour when asserts fail, and information is printed to console. For example, on an embedded system, the print hook can be used to power on an LED instead or print over a UART connection.
