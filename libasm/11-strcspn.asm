BITS 64
global asm_strcspn
section .text

asm_strcspn:
    xor rax, rax

_loop:
    movzx rcx, byte [rdi + rax] ; Load next char from `s` string into rcx
    test rcx, rcx               ; At end of `s`?
    jz _return                  ; If yes, return

    ; Check if char is in `reject`
    mov rbx, rsi                ; Copy `reject` string pointer to rbx
_check_reject_loop:
    movzx rdx, byte [rbx]       ; Load next char from `reject` into rdx
    test rdx, rdx               ; At end of `reject`?
    jz _next_char               ; If yes, char is not in `reject`

    cmp rcx, rdx                ; Compare char from `s` with char from `reject`
    je _return                  ; Return if match

    inc rbx                     ; Move to next char in `reject`
    jmp _check_reject_loop

_next_char:
    inc rax                     ; Increment result counter
    jmp _loop               	; Continue

_return:
    ret
