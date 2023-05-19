#include <stdio.h>
#include <stdlib.h>

#include "hashmap/hashmap.h"
#include "vector/vector.h"

typedef struct Foo {
	int x;
	int y;
} Foo_t;

void test_hashmap();

void vectorCallback(void *elemData)
{
	printf("x = %d\n", ((Foo_t *)elemData)->x);
}

void printElem(void *elem)
{
    Foo_t *e = (Foo_t *)elem;
    printf("(%d, %d)", e->x, e->y);
}

int main(int argc, char *argv[])
{
    test_hashmap();
}

void test_hashmap()
{
    struct HashMap *map = HashMap_new(20, sizeof(Foo_t));
    Foo_t f = { 20, 123 };
    Foo_t g = { 50, 800 };
    Foo_t d = { 21, 424 },
          x = { 10, 200 },
          y = { 123, 90 },
          z = { 99, 88 };

    char dave[20] = "Dave",
         bob[20]  = "Bob",
         frank[20]  = "Frank",
         brian[20]  = "Brian",
         mat[20]    = "Mat",
         soren[20]  = "Soren";


    HashMap_insert(map, dave, &f);
    HashMap_insert(map, bob, &g);
    HashMap_insert(map, frank, &d);
    HashMap_insert(map, brian, &x);
    HashMap_insert(map, mat, &y);
    HashMap_insert(map, soren, &z);

    Foo_t *bptr = HashMap_get(map, brian);

    printElem(bptr);
    printf("\n");

    HashMap_print(map, printElem);

    HashMap_delete(map);
}

void test_vector()
{
	Vector_t *vec = Vector_new(sizeof(Foo_t));
	Foo_t foo = {
		.x = 10,
		.y = 20
	};
	for (int i = 0; i < 10; i++)
	{
		Vector_push_back(vec, &foo);
		Vector_push_front(vec, &foo);
		foo.x += 1;
		foo.y += 1;
	}

	Vector_foreach(vec, vectorCallback);

	int len = Vector_len(vec);

	Foo_t *f = (Foo_t *)Vector_get(vec, 70);
	if (f)
		printf("F = x:%d y: %d\n", f->x, f->y);

	for (int i = 0; i < len; i++)
	{
		Foo_t *bar = (Foo_t *)Vector_pop_back(vec);
		printf("[%d] Return x: %d, y: %d\n", i, bar->x, bar->y);
		free(bar);
	}

	Vector_delete(vec);
}
