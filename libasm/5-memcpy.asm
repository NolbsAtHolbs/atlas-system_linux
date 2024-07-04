BITS 64
global asm_memcpy
section .text

asm_memcpy:
    push rbp
    mov rbp, rsp
    push rcx

    ; Save destination pointer to return it later
    mov rax, rdi

    ; Check if n is 0
    test rdx, rdx
    jz _return

_loop:
    ; Copy 1 byte from src to dest
    mov cl, byte [rsi]
    mov byte [rdi], cl

    ; Increment pointers, decrement counter
    inc rsi
    inc rdi
    dec rdx

    ; Check if complete
    test rdx, rdx
    jnz _loop

_return:
    pop rcx
    mov rsp, rbp
    pop rbp
    ret
