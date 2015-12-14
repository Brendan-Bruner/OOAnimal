#Overwriting
---

Overwriting is not in the OO dictionary. However, it's an important part of the CObject back bone. 

In the previous section we overrode the Point_Draw( ) method, then used the super's implementation in our new implementation. When we did this, we added an extra function pointer to the Square structure, increasing the memory usage of all square objects. What if we didn't use the super's implementation, at all? Then, we wouldn't need that extra function pointer and hence, we would save memory. This is overwriting, we remove all reference to the old implementation, and only have our new implementation. 

This is useful when you want to override a virtual method, but have no desire to reference the super's implementation.

We will use the same header file for Square as we did in the [Virtual and Pure Virtual Methods](https://github.com/bandren/CObject/blob/master/docs/VirtualMethods.md) section, and modify Square's source file from the [Overriding](https://github.com/bandren/CObject/blob/master/docs/Overriding.md) section.

###Source

```C
#include <Square.h>

/* Implementation declare for Point_Clone( ). */
static struct Point* PointPureVirtual_Clone( struct Point* );
static void PointVirtual_Draw( struct Point* );

/* Constructor. */
struct Square* Square( struct Square* self, int x, int y, int length )
{
	/* Like before, CConstructor( ) must be first operation. */
	CConstructor(self);

	/* Like before, must call super class' constructor. */
	Point(&self->super, x, y);

	/* Link the pure virtual method implementation. */
	CLinkVirtual(&self->super, PointPureVirtual_Clone);

	/* IMPORTANT */
	/* Must always call the super class constructor before overwriting */
	/* a method. */
	/* The first argument is a pointer to the super class where the */
	/* method being overwritten is defined. */
	/* The last argument is the name of method pointer being overwritten. */
	/* This resolves to exactly: */
	/*		(&self->super)->PointVirtual_Draw = PointVirtual_Draw; */
	COverwriteVirtual(&self->super, PointVirtual_Draw);

	/* Set up member variables. */
	self->length = length;

	return self;
}

static void PointVirtual_Draw( struct Point* self_ )
{
	/* Must always call this as the first operation in any virtual method. */
	struct Square* self = CCast(self_);

	/* Print the squares length. */
	printf("Square of length: %d\n", self->length);
}

static struct Point* PointPureVirtual_Clone( struct Point* self_ )
{
	/* Must always call this as the first operation in any virtual method. */
	struct Square* self = CCast(self_);

	/* Start making the clone */
	struct Square* clone = malloc(sizeof(struct Square));
	if( clone == NULL )
	    return NULL;

	/* Construct the allocated memory for a clone. */
	if( Square(clone, self->super.x, self->super.y, self->length) == NULL ) {
		free(clone);
		return NULL;
	}

	/* Flag the clone as being dynamically allocated. */
	CDynamic(clone);

	/* Return the clone. Recalling it is always safe to cast a pointer to any */
	/* of its super classes. */
	return ((struct Point*) self);
}

/* The new scale method. */
void Square_Scale( struct Square* self, int factor )
{
	/* As usual, assert for NULL input. */
	CAssertObject(self);

	/* Interesting note, what if factor was MIN_INT? Because, */
	/* -MIN_INT = MAX_INT+1 due to two's complement. */
	if( factor < 0 )
	    self->length = self->length / -factor;
	else
	    self->length = self->length * factor;
}
```

###Main

Using the same main as in the **Overriding** section, we can see our new implementation of Point_Draw( ) gets called, and the super's implementation is lost.

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
