#include <stdlib.h>
#include <string.h>
#include "cstring.h"

typedef struct {
    char* str;
    size_t len;
} String_t;

String* String_new(const char* str)
{
    String_t* string = (String_t*)malloc(sizeof(String_t));
    string->len = strlen(str);
    string->str = (char*)calloc(string->len + 1, 1);

    strcpy(string->str, str);
    return (String*)string;
}

void String_delete(String* string)
{
    String_t* s = (String_t*) string;
    free(s->str);
    free(s);
}

size_t String_len(const String* string)
{
    return ((String_t*)string)->len;
}

void String_append(String* string, const char* str)
{
    String_t* s = (String_t*)string;
    s->len += strlen(str);
    s->str = realloc(s->str, s->len+1);
    strcat(s->str, str);
}

void String_push(String* string, const char c)
{
    String_t* s = (String_t*)string;
    size_t newSize = s->len + 1;
    s->str = realloc(s->str, newSize);
    s->str[s->len] = c;
    s->len = newSize;
}

bool String_contains(String* string, const char* pattern)
{
    String_t* s = (String_t*)string;
    size_t patternLen = strlen(pattern);
    size_t endIndex = s->len - patternLen;

    for (char* substr = s->str; substr != s->str+endIndex; substr++) {
        if (strncmp(substr, pattern, patternLen) == 0) {
            return true;
        }
    }
    return false;
}
