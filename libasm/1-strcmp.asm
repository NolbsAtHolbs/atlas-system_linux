BITS 64
global asm_strcmp
section .text

asm_strcmp:
	xor eax, eax            ; Clear eax (return value)
	xor ecx, ecx            ; Clear ecx (used for character comparison)

_compare_loop:
	mov al, byte [rdi]      ; Load byte from s1
	mov cl, byte [rsi]      ; Load byte from s2
	test al, al             ; Check if end of s1
	je _last				; If end of s1, check if s2 also ended

	test cl, cl             ; Check if end of s2
	je _s1_gt				; If end of s2, s1 is greater

	inc rdi                 ; Move to next byte in s1
	inc rsi                 ; Move to next byte in s2

	cmp al, cl              ; Compare bytes
	je _compare_loop        ; If equal, continue loop

		; Difference found
	ja _s1_gt				; If s1 byte greater, jump to return 1
	jb _s1_lt				; If s1 byte less, jump to return -1

_last:
	test cl, cl             ; Check if end of s2
	je _eq               ; If end of s2, strings are equal
	jmp _s1_lt				; If not, s1 is less

_s1_gt:
	mov eax, 1              ; Return 1
	ret

_s1_lt:
	mov eax, -1             ; Return -1
	ret

_eq:
	xor eax, eax            ; Return 0
	ret
