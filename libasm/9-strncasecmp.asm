BITS 64
global asm_strncasecmp
section .text

asm_strncasecmp:
    push rbp
    mov rbp, rsp

_loop:
    test rdx, rdx         ; Check if we've compared n chars
    jz _equal             ; If 0, strings are equal up to n

    movzx eax, byte [rdi] ; Load byte from s1
    movzx ecx, byte [rsi] ; Load byte from s2

    ; Convert to lowercase if uppercase
    cmp al, 'A'
    jl _check_s2
    cmp al, 'Z'
    jg _check_s2
    add al, 32				; Cool bit op in ASCII

_check_s2:
    cmp cl, 'A'
    jl _compare
    cmp cl, 'Z'
    jg _compare
    add cl, 32

_compare:
    ; Compare chars
    cmp al, cl
    jne _return_diff

    ; Check if strings ended
    test al, al
    jz _equal

    ; Move to next char, decrement n
    inc rdi
    inc rsi
    dec rdx
    jmp _loop

_return_diff:
    sub eax, ecx  ; Calculate difference
    jmp _return

_equal:
    xor eax, eax

_return:
    mov rsp, rbp
    pop rbp
    ret
