
#include <stdio.h>

#include "coroutine.h"

void test(void) {
    int a = 10;
    printf("test 1... a = %d\n", a);
    co_yield ();

    a++;
    printf("test 2... a = %d\n", a);
    co_yield ();

    a++;
    printf("test 3... a = %d\n", a);
    co_yield ();
}

int main(int argc, char* argv[]) {

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
