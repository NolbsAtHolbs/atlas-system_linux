BITS 64
global asm_strncmp
section .text

asm_strncmp:
    push rbp
    mov rbp, rsp

    test rdx, rdx         ; Check if n is 0
    jz _equal             ; If n is 0, strings are considered equal

_loop:
    test rdx, rdx         ; Check if we've compared n characters
    jz _equal             ; If so, strings are considered equal up to n

    movzx eax, byte [rdi] ; Load byte from s1
    movzx ecx, byte [rsi] ; Load byte from s2

    ; Compare the characters
    cmp al, cl
    jne _return_diff

    ; Check if we've reached the end of either string
    test al, al
    jz _equal

    ; Move to next character and decrement n
    inc rdi
    inc rsi
    dec rdx
    jmp _loop

_return_diff:
    sub eax, ecx  ; Compute difference
    jmp _return

_equal:
    xor eax, eax  ; Set return value to 0 (strings are equal up to n characters)

_return:
    mov rsp, rbp
    pop rbp
    ret
