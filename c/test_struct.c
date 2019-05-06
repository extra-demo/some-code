#include "stdint.h"
#include "stdio.h"

struct st1 {
    int64_t id;
    char * name;
};

typedef struct st1 ST1DEF;

typedef struct {
    int64_t id;
    char * name;
} ST1DEF1;

void print001(const struct st1);

void print001(const struct st1 s)
{
    printf("id:%lld^^^name:%s\n", s.id, s.name);
}

int main(int num, char ** args) {
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
}
