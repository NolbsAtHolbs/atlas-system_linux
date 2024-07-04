BITS 64
section .text
global asm_puts
extern asm_strlen

asm_puts:
    push rdi			; Save pointer to string
    call asm_strlen		; Call asm_strlen to get length of string
    push rax			; Save length of string

		; Prepare args for write syscall
    mov rdx, rax        ; Num of bytes to write aka str length
    mov rsi, rdi        ; Pointer to string
    mov rdi, 1          ; File descriptor 1 (stdout)
    mov rax, 1          ; Syscall num for write

    syscall

    pop rax				; Restore length of string
    pop rdi				; Restore pointer to string
    ret					; Return length of string
