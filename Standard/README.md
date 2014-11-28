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
* All function definitions have to be static
