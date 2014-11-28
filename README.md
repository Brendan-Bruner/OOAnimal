OOAnimal
========

See /Standard for wrappers and documentation.

##The Good

OOAnimal provides a simple wrapper for implementing classes in C. This method enables single inheritance, traits, function overriding, polymorphism, and aggregation. Since I developed this standard for use in embedded applications there is no dynamic memory allocation. However, an object can still be allocated on the heap, like any other data type. 

In the OOAnimal folder is an eclipse project which demonstrates how to use the class wrapper (no traits). I used Eclipse 3.8 on Lubuntu. In the CommandLineCompile folder is a Makefile to run the project from the command line.

In the OODragon folder is an eclipse project which demonstrates how to use the class and trait wrapper. Like the OOAnimal folder, I used Eclipse 3.8 on Lubuntu.

OOAnimal is licensed under the GNU General Public License v2. I did this so hopefully everyone can use these wrappers in their projects.

##The Bad

The compiler will give several "warning: assignment from incompatible pointer type" using this standard. Adding type casts will remove these warnings, but it makes no difference to the functionality.


The software engineer / programmer will have some overhead when writing code. The most notable is setting up the function pointers in each classes constructors. In addition, there is a naming convention in the standard.

##The Ugly

The worst of the overhead with this standard is a larger code base and the run time cost of dynamic linkage. What this means is, everytime an object is initialized (with a call to new_Obj()) the function has to spend time setting up the function pointers. When a class method is called (ie, obj.vtable.func(&obj)) there is a small amount of overhead to put the pointer to the object on the stack. Finally, the code base is larger because each object will have its own collection of function pointers.
