#CObject
---

CObject is a small set of macros and functions that enable fundamental object oriented concepts (OO) in the C language. Using C++ and Java terminology, CObject enables: classes, single inheritance, interfaces, virtual methods, and pure virtual methods. In addition to supporting OO concepts, CObject was designed to use minimal boiler plate code and reveal as much of the implementation as possible. With a transparent implementation, CObject is easier to debug and more intuitive to develop with. However, this comes at a cost: the developer must have some understanding of object oriented programming in C++. Go through the check list below, if you are already aware of everything stated, then CObject will be straight forward to understand. If not, you'll figure things out as you go.

* Virtual functions are implemented with function pointers
* A class with pure virtual methods is abstract and should never be instantiated.
* The diamond problem
* Inheritance is actually just a special form of aggregation

###Compile Time and Run Time Checks

Since C is not an OO language, compile time checks are very limited. For example, the compiler can't know if a class has forgot to implement a method inherited from an interface or if application code is using private variables. To remedy this, run time checks are (optionally) done. When compiling, the symbol DEBUG must be defined for run time checks to be used.

When a run time check fails, an error will be printed to console and the program execution halted. The printed message will explain the most likely cause of failure and common solutions. Since different systems have different requirements, hooks are provided to changed the behaviour when asserts fail, and information is printed to console. For example, on an embedded system, the print hook can be used to power on an LED instead or print over a UART connection.

###Tutorials

These tutorials provide a brief overview of how to use CObject by example. 

1. [Classes](https://github.com/bandren/CObject/blob/master/docs/Classes.md)
2. [Virtual and Pure Virtual Methods](https://github.com/bandren/CObject/blob/master/docs/VirtualMethods.md)
3. [Inheritance and Implementing Pure Virtual Methods](https://github.com/bandren/CObject/blob/master/docs/Inheritance.md)
4. [Overriding](https://github.com/bandren/CObject/blob/master/docs/Overriding.md)
5. [Overwriting](https://github.com/bandren/CObject/blob/master/docs/Overwriting.md)
6. [The Destructor](https://github.com/bandren/CObject/blob/master/docs/TheDestructor.md)
7. [Interfaces](https://github.com/bandren/CObject/blob/master/docs/Interfaces.md)
8. [Overriding and Overwriting Inherited Interface Methods](https://github.com/bandren/CObject/blob/master/docs/OverridingInterfaceMethods.md)
