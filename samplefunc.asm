section .data
msg db "Hello World", 13,10,0

section .text
bits 64
default rel ;to handle address relocation

global hello
extern printf

hello:
	sub rsp, 8*5	; caller
	lea rcx, [msg]
	call printf
	add rsp, 8*5
	ret