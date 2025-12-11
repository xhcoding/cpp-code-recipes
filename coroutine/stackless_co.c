#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct co co_t;
typedef void (*co_entry_t)(co_t* co);

struct co {
    co_entry_t entry;
    int state;
    int val;
};

co_t* co_create(co_entry_t entry) {
    co_t* co = malloc(sizeof(co_t));
    if (co == NULL) {
        return NULL;
    }
    co->entry = entry;
    co->state = 0;
    co->val = 0;
    return co;
}

void co_resume(co_t* co) {
    co->entry(co);
}

void co_destroy(co_t* co) {
    free(co);
}

void test(co_t* co) {
    switch (co->state) {
    case 0:
        co->val = 10;
        printf("test 1... a = %d\n", co->val);
        co->state = 1;
        return;
    case 1:
        co->val++;
        printf("test 2... a = %d\n", co->val);
        co->state = 2;
        return;
    case 2:
        co->val++;
        printf("test 3... a = %d\n", co->val);
        return;
    }
}

int main() {

    co_t* co = co_create(test);

    co_resume(co);

    printf("main 1....\n");

    co_resume(co);

    printf("main 2 ...\n");

    co_resume(co);

    printf("main end\n");

    co_destroy(co);

    return 0;
}
