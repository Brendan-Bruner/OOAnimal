#CObject
---

CObject is a small set of macros and functions that enable fundamental object oriented concepts (OO) in the C language. it was designed to use minimal boiler plate code and use as simple an implementation as possible. With a transparent implementation, CObject is easier to debug and more intuitive to develop with. However, this comes at a cost: the developer must be more aware of the back bone enabling object oriented programming.

CObject is c99 compliant. 

###What it Can do

Using C++ and Java terminology: 

* Classes
* Single inheritance
* Interfaces
* Virtual and pure virtual methods

###What it Can't do

It can only hide private functions, since these are defined as static in a class' source file. Everything else is public. The best a programmers can do is try to hide private data, by using an anonymous struct with the name '_', ie:

```C
struct SomeClass
{
  /* Private data */
  struct
  {
    int x;
  }_; /* Private variable 'x' is hidden in an anonymous struct with the variable name, _. */
}
```

In addition, it cannot stop you from successfully compiling code with logical OO errors, such as, instantiating a class with pure virtual methods, forgetting to implement pure virtual methods, etc. Run time checks are provided to catched this.

###Compile Time and Run Time Checks

Since C is not an OO language, compile time checks are very limited. For example, the compiler can't know if a class has forgot to implement a method inherited from an interface or if application code is using private variables. To remedy this, run time checks are (optionally) done. **When compiling, the symbol DEBUG must be defined for run time checks to be used**.

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
