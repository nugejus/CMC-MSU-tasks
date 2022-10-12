include io.asm 

stack segment stack
	dw 128 dup (?)
stack ends

data segment
COUNT equ 7
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	mov bx,0
	mov cx,1
	inint ax
	mov dx,ax ;first number = max number
	
	;circle start
	CIRCLE:
	inc cx
	inint ax
	cmp ax,dx
	jng LESS
	mov dx,ax
	mov bx,cx
	LESS:
	cmp cx,COUNT
	jne CIRCLE
	
	outint dx
	outch " "
	outint bx
    finish
code ends
    end start 
