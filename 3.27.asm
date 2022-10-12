include io.asm

stack segment stack
	dw 128 dup (?)
stack ends

data segment
COUNT equ 5
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	
	mov cx,0
	mov dx,0
	
	CIRCLE:
	inc cx
	inint ax
	cmp ax,0
	jge MORETHENZERO
	cmp dx,0
	je NEXTSTEP
	cmp ax,dx
	jl MORETHENZERO
	NEXTSTEP:
	mov dx,ax
	MORETHENZERO:
	cmp cx,COUNT
	jne CIRCLE
	
	outint dx
    finish
code ends
    end start 
