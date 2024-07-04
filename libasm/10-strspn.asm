BITS 64
global asm_strspn
section .text

asm_strspn:
    xor rax, rax

_loop:
    movzx rcx, byte [rdi + rax] ; Load next char from `s` string into rcx
    test rcx, rcx               ; At end of `s`?
    jz _return                  ; If yes, return

	; Check if char is in `accept`
    mov rbx, rsi                ; Copy `accept` string pointer to rbx

_check_accept_loop:
    movzx rdx, byte [rbx]       ; Load next char from `accept` into rdx
    test rdx, rdx               ; At end of `accept`?
    jz _return                  ; If yes, return

    cmp rcx, rdx                ; Compare char from `s` to char from `accept`
    je _found_char              ; If they match, continue to next char in `s`

    inc rbx                     ; Move to next char in `accept`
    jmp _check_accept_loop

_found_char:
    inc rax                     ; Increment result counter
    jmp _loop               	; Continue

_return:
    ret
