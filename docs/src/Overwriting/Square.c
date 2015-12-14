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
	/*		&(self->super)->PointVirtual_Draw = PointVirtual_Draw; */
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