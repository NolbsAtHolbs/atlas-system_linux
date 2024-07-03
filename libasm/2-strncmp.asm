section .text
global asm_strncmp

asm_strncmp:
    ; Initialize pointers and counter
    mov rcx, rdx        ; rcx = n (counter for number of characters to compare)
    test rcx, rcx       ; Check if n is 0
    jz _eq            ; If n is 0, strings are considered equal

_cmp_loop:
    mov al, byte [rdi]  ; Load byte from s1
    mov bl, byte [rsi]  ; Load byte from s2

    ; Compare bytes
    cmp al, bl
    jne _neq       ; If bytes are not equal, return difference

    ; Check if we reached the end of either string
    test al, al
    jz _check_remaining  ; If end of s1, check if we need to compare more
    test bl, bl
    jz _check_remaining  ; If end of s2, check if we need to compare more

    ; Move to the next character
    inc rdi
    inc rsi
    dec rcx             ; Decrement the counter
    jnz _cmp_loop    ; If counter is not zero, continue loop

    jmp _eq           ; If we compared n characters, strings are equal

_check_remaining:
    ; Check if we need to compare more characters
    test rcx, rcx
    jz _eq            ; If no more characters to compare, strings are equal

_neq:
    ; Calculate the difference between the characters
    sub al, bl
    movsx rax, al       ; Sign extend the result to 64 bits
    ret

_eq:
    xor eax, eax        ; Return 0 (strings are equal)
    ret
