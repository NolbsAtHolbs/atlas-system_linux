BITS 64
global asm_strncmp
section .text

asm_strncmp:
	push rbp
	mov rbp, rsp

    ; Initialize pointers and counter
    mov rcx, rdx        ; rcx used as n counter
    test rcx, rcx       ; Is n = 0?
    jz _equal           ; If yes, strings are considered equal

_loop:
    mov al, byte [rdi]  ; Load byte from s1
    mov bl, byte [rsi]  ; Load byte from s2

    cmp al, bl			; Compare bytes
	jg _greater         ; If s1 byte is greater, return 1
    jl _less            ; If s1 byte is less, return -1

    ; Check if we reached the end of either string
    test al, al
    jz _equal           ; If end of s1, strings are equal
    test bl, al
    jz _equal           ; If end of s2, strings are equal

    ; Move to the next character
    inc rdi
    inc rsi
    dec rcx             ; Decrement the counter
    jnz _loop			; If counter is not zero, continue loop

_equal:
    xor rax, rax        ; Return 0
    jmp _return

_greater:
    mov rax, 1          ; Return 1
    jmp _return

_less:
    mov rax, -1         ; Return -1
_return:
    mov rsp, rbp
    pop rbp
    ret