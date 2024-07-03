BITS 64
section .text
global asm_strchr

asm_strchr:
    ; Initialize pointer to the string
    mov rdx, rdi        ; rdx = s

_loop:
		; Load the current character from the string
    mov al, byte [rdx]  ; al = *s

		; Check if we reached the end of the string
    test al, al
    jz _not_found       ; If al == 0, the character was not found

		; Compare the current character with the target character
    cmp al, sil         ; Compare al (current char) with sil (c)
    je _found           ; If they are equal, we found the character

		; Move to the next character in the string
    inc rdx             ; s++
    jmp _loop           ; Repeat the loop

_found:
		; Return the pointer to the found character
    mov rax, rdx        ; rax = s
    ret

_not_found:
		; Return NULL if the character was not found
    xor rax, rax        ; rax = 0 (NULL)
    ret
