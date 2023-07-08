

#ifndef S_MDEF_H
#define S_MDEF_H


#define container_of(ptr, type, member) \
    (type *)((char*)ptr - offsetof(type, member))







#endif // S_MDEF_H
