#Introduction

Class.h and Trait.h provide wrappers which will enable object oriented programming in C. The syntax for classes is pretty clean, but for traits it can be kind of ugly. These wrappers allow single inheritance, function overriding, polymorphism, and traits.

***Single Inheritance***

This allows a class (The derived class) to extend another class (which is called the super class). The derived class gets everything from the super class without having to rewrite it. 

***Function Overriding***

This allows derived  classes to override functions in their super classes

***Polymorphism***

A derived class can be treated as its super class or trait. 

***Traits***

A trait prototypes functions. A class can use a trait. When it does this it has to implement the function prototypes of the trait (The compiler does not enforce this). 

#Rules

There are a few rules that need to be followed to avoid issues like the diamond problem. The compiler does not enforce these so i've tried to make them as simple as possible.

* A trait cannot use a trait
* A class cannot use a trait which its super class uses. Instead, the derived  class has to use function overriding.
* A class can only inherit from one class (single inheritance)
* All function implementations have to be static
* Function pointer names declared in header must be the same name as static implementation in source
* Class and trait names should be the same as their source and header file names
* Functions must have their first argument be a pointer to their class or trait

These rules are probably confusing right now. They will each be cleared up.

#Classes

Each class needs a header and source file. Starting with the header.

***Header***

The header file is where you prototype your class. Make sure you #include "Class.h". Lets start by making a class called Animal.

Animal.h
```
#ifndf ANIMAL_H_
#define ANIMAL_H_

#include "Class.h"

Class(Animal)                     /* Class name is the same as file name */
  Data
    int _age;
  Methods
    int (*getAge)(Animal *);      /* First argument is a pointer to the class (Animal *) */
    void (*birthday)(Animal *);   /* First argument is a pointer to the class (Animal *) */
EndClass;

#endif /* ANIMAL_H_ */
```
Thats all there is to it. We have created a class which has data member, _age (note, the underscore is to tell people it should be treated as a private data member), and two methods, getAge and brithday. The rules that are being followed are:
* Class and trait names should be the same as their source and header file names
* Functions must have their first argument be a pointer to their class or trait

***Source***

The source file implements the functions and constructor. 

Animal.c
```
#include "Animal.h"

/******************************************************************************/
/* Method Implementation                                                      */
/******************************************************************************/
static int getAge(Animal *this)
{
  return this->data._age;
}

static void brithday(Animal *this)
{
  ++this->data._age;
}

/******************************************************************************/
/* Constructor                                                                */
/******************************************************************************/
Constructor(Animal)
{
  LinkMethod(getAge);
  LinkMethod(birthday);
  this->data._age = 1;
}
```
There it is. The Animal class is implemented. Take note of the rules being followed here:
* All function implementations have to be static
* Function pointer names declared in header must be the same name as static implementation in source
* Class and trait names should be the same as their source and header file names
* Functions must have their first argument be a pointer to their class or trait
