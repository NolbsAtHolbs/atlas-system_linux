BITS 64
global asm_strpbrk
section .text

asm_strpbrk:
    push rbp
    mov rbp, rsp

    mov rbx, rdi        	; rbx iterates through `s` string
    mov rcx, rsi        	; rcx iterates through `accept` string

_loop:
    movzx rdx, byte [rbx]	; Load next char from `s`
    test rdx, rdx			; At end of `s`?
    jz _not_found			; If yes, return NULL

    mov rcx, rsi			; Reset `accept` pointer

_accept_loop:
    movzx rax, byte [rcx]	; Load next char from `accept`
    test rax, rax			; At end of `accept`?
    jz _next_char			; If yes, increment and repeat main loop

    cmp rdx, rax			; Compare char from `s` with char from `accept`
    je _found				; If they match, jump to found

    inc rcx					; Move to next char in `accept`
    jmp _accept_loop		; Repeat this loop

_next_char:
    inc rbx					; Move to next char in `s`
    jmp _loop				; Repeat main loop

_found:
    mov rax, rbx			; Return pointer to matching char in `s`
    jmp _return

_not_found:
    xor rax, rax			; Return NULL if no matching char is found
							; The expected return type of strpbrk is `char *`

_return:
    pop rbp
    ret
