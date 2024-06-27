BITS 64

section .data

section .bss

section .text
global asm_strlen

asm_strlen:
    xor rax, rax				; Exclusive OR with itself always gives zero
_byte_compare_loop:
    cmp byte [rdi + rax], 0		; Compare each byte in str with 0
    je _strlen_return			; If comparison = 0 (end of str), jump to return statement
    inc rax						; Otherwise, increment rax
    jmp _byte_compare_loop 		; Repeat the loop
_strlen_return:
    ret							; Return to caller by popping return address with totaled str len in rax
