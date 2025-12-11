# co_ctx_swap.S
.text
.globl co_ctx_swap
.type co_ctx_swap, @function

co_ctx_swap:
    movq %rsp, (%rdi)
    movq %rbx, 8(%rdi)
    movq %rbp, 16(%rdi)
    movq %r12, 24(%rdi)
    movq %r13, 32(%rdi)
    movq %r14, 40(%rdi)
    movq %r15, 48(%rdi)

    movq 48(%rsi), %r15
    movq 40(%rsi), %r14
    movq 32(%rsi), %r13
    movq 24(%rsi), %r12
    movq 16(%rsi), %rbp
    movq 8(%rsi), %rbx
    movq (%rsi), %rsp

    ret

.size co_ctx_swap, .-co_ctx_swap
