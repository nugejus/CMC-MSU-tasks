include io.asm

stack segment stack
	dw 128 dup (?)
stack ends

data segment
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	inint ax ;input P
	inint bx ;input Q
	
	mov dx,0
	div bx
	outint ax
	outch '.'
	
	mov cx,5
	LOOP1:
	mov ax,dx
	mov dx,10
	mul dx
	div bx
	outint ax
	loop LOOP1
	
    finish
code ends
    end start 
