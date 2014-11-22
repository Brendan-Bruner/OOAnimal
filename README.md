OOAnimal
========

OOAnimal provides an example of how to do object oriented programming in C. There are no wrappers, just a template to follow. Implementing classes this way enables single inheritance, virtual functions, and polymorphism. Since I developed this template for use in embedded applications there is no dynamic memory allocation. This means there is no concept of private and protected class members. Everything is public. In the application folder is an eclipse project which demonstrates how to follow the template. I used Eclipse 3.8 on Lubuntu.

OOAnimal is licensed under the GNU General Public License verion 2 or later. I did this so hopefully everyone can use these ideas in their projects.

##Template Directory
This provides a temple .c and .h folder for classes. Replace the string &{file_base} in each file with the name of the file (there are many of them to replace). The name of the file should be the same name as the class. Also, replace the ${include_guard_symbol} in the header file with appropriate test for a header file guard. Typically this will be _FILENAME_H_.

