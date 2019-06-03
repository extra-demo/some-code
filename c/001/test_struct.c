#include "test_struct.h"

void test_struct_print() {
    struct st1 s01 = {
        1,
        "abab",
    };
    print001(s01);

    ST1DEF s02 = {
        2,
        "abab",
    };
    print001(s02);

    ST1DEF s03 = {
        3,
        "abab",
    };
    print001(s03);

    ST1DEF1 * s04;
    s04 = (ST1DEF1*) malloc (sizeof(ST1DEF1*));
    s04->id = 4;
    s04->name = "cefg";
    print002(s04);

    struct X *x;
    char name[20] = "abab";
    x = init_x(1111, name);
    print_x(x);
}

struct X * init_x(const int64_t id, const char * name)
{
    struct X * x = (struct X *) malloc(sizeof(struct X *));
    x->id = id;
    x->name = (char *) name;
   
   return x;
}

void print_x(struct X * x)
{
    printf("id=%lld, name=%s\n", x->id, x->name);
}