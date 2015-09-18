#ifndef CLASS_H
#define CLASS_H

#define PRE_OBJECT_REFERENCE self_
#define OBJECT_REFERENCE self

#define CLASS_CLASS_NAME		_
#define SUPER_CLASS_NAME	       	_
#define CLASS_VIRTUAL_TABLE_NAME	__
#define OBJECT_VIRTUAL_TABLE_NAME	___

#define EXTENDS( class ) class
#define VIRTUAL( ... ) __VA_ARGS__
#define METHOD( ... ) __VA_ARGS__
#define DATA( ... ) __VA_ARGS__

#define CLASS_APPLICATION_TYPE( name ) 				\
  typedef struct name	 					\
  {								\
  char _[ sizeof( struct _##name##Representation_t ) ];	\
  } name;

#define CLASS_VIRTUAL_TABLE( name, virtual )		\
  struct _##name##VirtualTable_t 			\
  {							\
  Class_t CLASS_CLASS_NAME;				\
  virtual						\
  };
  
#define CLASS_COMPLETE_TYPE( name, extends, data )			\
  struct _##name##Representation_t					\
  {									\
  struct extends SUPER_CLASS_NAME;					\
  struct _##name##VirtualTable_t OBJECT_VIRTUAL_TABLE_NAME;		\
  struct _##name##VirtualTable_t const* CLASS_VIRTUAL_TABLE_NAME;	\
  data									\
  };

#define CLASS(\
	      name,			\
	      extends,			\
	      virtual,			\
	      data			\
	     )				\
  typedef struct name name;					\
  CLASS_VIRTUAL_TABLE( name, virtual )				\
  CLASS_COMPLETE_TYPE( name, extends, data ) 			\
  CLASS_APPLICATION_TYPE( name )				\
  
#define self( type ) type PRE_OBJECT_REFERENCE

#define MEMBER_OF( class ) \
  struct _##class##Representation_t* OBJECT_REFERENCE = (struct _##class##Representation_t*) PRE_OBJECT_REFERENCE

#define class( type, obj ) \
  (struct _##type##Representation_t* (obj))->OBJECT_VIRTUAL_TABLE_NAME




typedef void* Class_t;
typedef void* Object_t;

struct Class_t
{
  void (*destroy)( Class_t );
};

struct Object_t
{
  long id;
};

#endif /* CLASS_H */
