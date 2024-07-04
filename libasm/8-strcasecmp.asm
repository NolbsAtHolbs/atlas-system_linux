BITS 64
global asm_strcasecmp
section .text

asm_strcasecmp:
    push rbp
    mov rbp, rsp

_loop:
    movzx eax, byte [rdi]	; Load byte from s1
    movzx ecx, byte [rsi]	; Load byte from s2

		; Convert to lowercase if uppercase
    cmp al, 'A'
    jl _check_s2
    cmp al, 'Z'
    jg _check_s2
    add al, 32

_check_s2:
    cmp cl, 'A'
    jl _compare
    cmp cl, 'Z'
    jg _compare
    add cl, 32

_compare:
		; Compare the chars
    cmp al, cl
    jne _return_diff

		; Check if strings have ended
    test al, al
    jz _equal

		; Move to next char
    inc rdi
    inc rsi
    jmp _loop

_return_diff:
    sub eax, ecx			; Calculate difference
    jmp _return

_equal:
    xor eax, eax			; Set return value to 0 (strings are equal)

_return:
    mov rsp, rbp
    pop rbp
    ret
