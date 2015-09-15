#ifndef CLASS_H
#define CLASS_H

typedef void* Class_t;

struct Class_t
{
  void (*destroy)( Class_t );
};

#endif /* CLASS_H */
