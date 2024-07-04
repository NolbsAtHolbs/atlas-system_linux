BITS 64
global asm_strncmp
section .text

asm_strncmp:
    ; Initialize pointers and counter
    mov rcx, rdx        ; rcx used as n counter
    test rcx, rcx       ; Is n = 0?
    jz _equal           ; If yes, strings are considered equal

_compare_loop:
    mov al, byte [rdi]  ; Load byte from s1
    mov bl, byte [rsi]  ; Load byte from s2

    cmp al, bl			; Compare bytes
    jne _not_equal      ; If unequal, return difference

    ; Reached end of either string?
    test al, al
    jz _equal           ; If end of s1, strings are equal
    test bl, al
    jz _equal           ; If end of s2, strings are equal

    ; Move to next char
    inc rdi
    inc rsi
    dec rcx             ; Decrement counter
    jnz _compare_loop   ; Until 0

_equal:
    xor rax, rax        ; Return 0
    ret

_not_equal:
    sub al, bl			; Calculate difference between chars
    movsx rax, al       ; Sign extend result to 64 bits
    ret
