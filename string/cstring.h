

#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct { const char* as_raw; } String;


String* String_new(const char* str);
size_t String_len(const String* string);
void String_append(String* string, const char* str);
void String_push(String* string, const char c);
void String_delete(String* string);
bool String_contains(String* string, const char* pattern);


#endif /* __STRING_H__ */
