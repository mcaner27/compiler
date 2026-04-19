.globl main
main:
    mov $1, %rax
    push %rax
    mov $2, %rax
    mov %rax, %rbx
    pop %rax
    cmp %rbx, %rax
    setl %al
    movzb %al, %rax
    cmp $0, %rax
    je .L0
    mov $5, %rax
    ret
.L0:
    mov $0, %rax
    ret

