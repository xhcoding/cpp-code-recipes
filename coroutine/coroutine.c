#include "coroutine.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CO_STACK_SIZE (64 * 1024)  // 64KB

struct co_ctx {
    void* rsp;
    void* rbx;
    void* rbp;
    void* r12;
    void* r13;
    void* r14;
    void* r15;
};

struct co {
    co_entry_t entry;
    struct co_ctx ctx;
    char stack[CO_STACK_SIZE];
};

extern void co_ctx_swap(struct co_ctx* from, struct co_ctx* to);

static co_t* cur_co = NULL;
static struct co_ctx main_ctx;

co_t* co_create(co_entry_t entry) {
    co_t* co = malloc(sizeof(co_t));
    if (!co) return NULL;

    co->entry = entry;

    char* stack_top = co->stack + CO_STACK_SIZE;
    stack_top = (char*) ((uintptr_t) stack_top & ~0xF);

    stack_top -= sizeof(void*);
    *(void**) stack_top = (void*) entry;

    co->ctx.rsp = stack_top;
    return co;
}

void co_resume(co_t* co) {
    if (!co) return;
    cur_co = co;
    co_ctx_swap(&main_ctx, &co->ctx);
}

void co_yield (void) {
    co_ctx_swap(&cur_co->ctx, &main_ctx);
}

void co_destroy(co_t* co) {
    free(co);
}
