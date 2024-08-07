BITS 64
section .text
global asm_strchr

asm_strchr:
    ; Initialize pointer to the string
    mov rdx, rdi        ; rdx = s

_loop:
    ; Load the current character from the string
    mov al, byte [rdx]  ; al = *s

    ; Check if we reached the end of the string (null terminator)
    test al, al
    jz _check_null      ; If al == 0, check if we are looking for the null terminator

    ; Compare the current character with the target character
    cmp al, sil         ; Compare al (current char) with sil (c)
    je _found           ; If they are equal, we found the character

    ; Move to the next character in the string
    inc rdx             ; s++
    jmp _loop           ; Repeat the loop

_check_null:
    ; Check if we are looking for the null terminator
    cmp sil, 0          ; Compare sil (c) with 0
    je _found           ; If sil == 0, we found the null terminator

_not_found:
    ; Return NULL if the character was not found
    xor rax, rax        ; rax = 0 (NULL)
    ret

_found:
    ; Return the pointer to the found character
    mov rax, rdx        ; rax = s
    ret
