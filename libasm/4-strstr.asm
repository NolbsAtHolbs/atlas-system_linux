BITS 64
global asm_strstr
section .text

asm_strstr:
    push rbp
    mov rbp, rsp
    push rbx

    ; If needle is an empty string, return haystack
    mov al, byte [rsi]
    test al, al
    jz _needle_empty

_next_char_in_haystack:
    ; If we reached the end of haystack, return NULL
    mov al, byte [rdi]
    test al, al
    jz _not_found

    ; Save current position of haystack
    mov rbx, rdi

    ; Compare needle with haystack
    mov rcx, rsi

_compare_chars:
    ; Load current chars from haystack and needle
    mov al, byte [rbx]
    mov dl, byte [rcx]

    ; If current char of needle is null, jump to found
    test dl, dl
    jz _found

    ; If chars differ, continue with next char in haystack
    cmp al, dl
    jne _next_haystack_char

    ; Move to the next chars in haystack and needle
    inc rbx
    inc rcx
    jmp _compare_chars

_next_haystack_char:
    ; Move to next char in haystack
    inc rdi
    jmp _next_char_in_haystack

_found:
    ; If needle is found, return start position in haystack
    mov rax, rdi
    pop rbx
    mov rsp, rbp
    pop rbp
    ret

_not_found:
    ; If needle is not found, return NULL
    xor rax, rax
    pop rbx
    mov rsp, rbp
    pop rbp
    ret

_needle_empty:
    ; If needle is an empty string, return haystack
    mov rax, rdi
    pop rbx
    mov rsp, rbp
    pop rbp
    ret
