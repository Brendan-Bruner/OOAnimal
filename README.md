OOAnimal
========

##The Good

OOAnimal provides a standard for object oriented programming in C. There are no wrappers, just a template to follow. Implementing classes this way enables single inheritance, virtual functions, polymorphism, and aggregation. Since I developed this standard for use in embedded applications there is no dynamic memory allocation. Everything is put on the stack. However, an object can still be allocated on the heap, like any other data type. 

In the OOAnimal folder is an eclipse project which demonstrates how to follow the standard. I used Eclipse 3.8 on Lubuntu. In the CommandLineCompile folder is a Makefile to run the project from the command line.

OOAnimal is licensed under the GNU General Public License v2. I did this so hopefully everyone can use these ideas in their projects.

##The Bad

The compiler will give several "warning: assignment from incompatible pointer type" using this standard. Adding type casts will remove these warnings, but it makes no difference to the functionality.


The software engineer / programmer will have some overhead when writing code. The most notable is setting up the function pointers in each classes constructors. In addition, the naming convention in the standard (or what ever naming convention is used) must be strictly followed.

##The Ugly

The worst of the overhead with this standard is a larger code base and the run time cost of dynamic linkage. What this means is, everytime an object is instantiated (with a call to new_Obj()) the function has to spend time setting up the function pointers. When a class method is called (ie, obj.vtable.func(&obj)) there is a small amount of overhead to put the pointer to the object on the stack. Finally, the code base is larger because each object will have its own collection of function pointers.

##Standard Directory

This provides a template .c and .h folder for classes. Replace the string &{file_base} in each file with the name of the file (there are many of them to replace). The name of the file should be the same name as the class. Also, replace the ${include_guard_symbol} in the header file with appropriate test for a header file guard. Typically this will be _FILENAME_H_.

