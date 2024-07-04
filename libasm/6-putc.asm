BITS 64
global asm_putc
section .text

asm_putc:
    ; Save char to be printed on stack
    push rdi

    ; Prepare args for write syscall
    mov rax, 1          ; syscall num for write
    mov rdi, 1          ; file descriptor 1 (stdout)
    mov rsi, rsp        ; pointer to the character on the stack
    mov rdx, 1          ; num of bytes to write

    syscall				; Write

    ; Restore stack
    add rsp, 8

    ; Return num of bytes written
    mov rax, 1
    ret
