#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

struct st1 {
    int64_t id;
    char * name;
};

typedef struct st1 ST1DEF;

typedef struct {
    int64_t id;
    char * name;
} ST1DEF1;

void print001(const struct st1 s)
{
    printf("id:%lld^^^name:%s\n", s.id, s.name);
}

void print002(ST1DEF1 * s) 
{
    printf("id:%lld^^^name:%s\n", s->id, s->name);
}

// =================================================
// YES
// =================================================
struct X {
    int64_t id;
    char * name;
};
struct X * init_x(const int64_t, const char *);
void print_x(struct X *);