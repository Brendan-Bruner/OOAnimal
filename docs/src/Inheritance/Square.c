#include <Square.h>

/* Implementation declare for Point_Clone( ). */
static struct Point* PointPureVirtual_Clone( struct Point* );

/* Constructor. */
struct Square* Square( struct Square* self, int x, int y, int length )
{
	/* Like before, CConstructor( ) must be first operation. */
	CConstructor(self);

	/* Like before, must call super class' constructor. */
	Point(&self->super, x, y);

	/* IMPORTANT */
	/* The super classes constructor must be called before linking the */
	/* implementation of Point_Clone( ). */

	/* IMPORTANT */
	/* Link the pure virtual method implementation. */
	/* The first argument is the path to the function */
	/* pointer that is documented as pure virtual. */
	/* The second argument is the name of the function pointer. */
	/* This resolves to exactly: */
	/* 			&self->super.PointPureVirtual_Clone = PointPureVirtual_Clone; */
	/* After doing this, the assert discussed in the last section will stop failing. */
	/* When someone calls Point_Clone( ), the assert passes, then this */
	/* method gets called. */
	CLinkVirtual(&self->super, PointPureVirtual_Clone);

	/* Set up member variables. */
	self->length = length;

	return self;
}

static struct Point* PointPureVirtual_Clone( struct Point* self_ )
{
	/* IMPORTANT */
	/* Must always call this as the first operation in any virtual method. It does some */
	/* run time checking and casts the input pointer to a pointer of the implementing */ 
	/* class. It will safetly cast the pointer to a struct Point to a pointer to a */
	/* struct Square. Even though its safe to cast a pointer to any of its super */
	/* classes, the reverse should be avoided. When we discuss interfaces, the reverse. */
	/* is never true. */
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