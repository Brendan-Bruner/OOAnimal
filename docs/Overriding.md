#Overriding
---

In this section, we're going to continue with the Square class by overriding the super class' method, Point_Draw( ). Overriding has two implications.

* The method implemented by the super class is changed to a new implementation by the sub class
* The super class' implementation can still be called, but only within the overriding sub class. 

Both these concepts will be demonstrated by overriding the original Point_Draw( ), and calling the original Point_Draw( ) in the new implementation.

![](https://raw.githubusercontent.com/Brendan-Bruner/CObject/docs/Inheritance.jpg)

###Header

###Source
 
###Main

### Compiling

Assuming a directory structures like this:

./
<br>|-> Class
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.h
<br>|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-> Class.c
<br>|-> Square.h
<br>|-> Square.c
<br>|-> Point.h
<br>|-> Point.c
<br>|-> main.c

```
gcc -I. -DDEBUG -Wall Class/Class.c Point.c Square.c main.c -o main
./main
```