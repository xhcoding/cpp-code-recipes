#ifndef COROUTINE_H
#define COROUTINE_H

typedef struct co co_t;

typedef void (*co_entry_t)();

co_t* co_create(co_entry_t entry);

void co_resume(co_t* co);

void co_yield (void);

void co_destroy(co_t* co);

#endif /* COROUTINE_H */
