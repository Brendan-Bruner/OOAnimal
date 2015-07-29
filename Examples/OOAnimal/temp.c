# 1 "../../Class/BaseObject.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../../Class/BaseObject.c"
# 17 "../../Class/BaseObject.c"
# 1 "../../Class/Class.h" 1
# 21 "../../Class/Class.h"
# 1 "../../Class/ClassConfig.h" 1
# 60 "../../Class/ClassConfig.h"
typedef struct Object Object;
struct Object
{
 void (*destroy)( Object *self );
};
# 74 "../../Class/ClassConfig.h"
void newObject( Object *self );
# 22 "../../Class/Class.h" 2
# 18 "../../Class/BaseObject.c" 2


static void destroy( Object *self )
{
 (void) self;
 return;
}


void newObject( Object *self )
{
 self-> destroy = & destroy;
}
