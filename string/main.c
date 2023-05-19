#include <string.h>
#include <stdio.h>
#include "cstring.h"

int main()
{
    String* s = String_new("Hello");
    String_push(s, ' ');
    String_append(s, "World\n");
    String_append(s, "this is a test to see how well this functions æææææææææææøøøøøøøøøøøåååååååååååå\n");

    if (String_contains(s, "World")) {
        printf("%s", s->as_raw);
    }

    printf("strlen(s) == %lu\n"
           "String_len(s) == %lu\n",
           strlen(s->as_raw), String_len(s));
    String_delete(s);

    char buff[1000] = { 0 };



    scanf("%s", buff);

    String* string = String_new(buff);

    printf("Got %d bytes: %s\n", String_len(string), string->as_raw);
    

    String_delete(string);
}
