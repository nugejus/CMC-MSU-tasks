;3.28
include io.asm 

stack segment stack
	dw 128 dup (?)
stack ends

data segment
COUNT equ 6
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	mov cx,0
	mov bx,0;count of same num
	
	inint ax;when cx = 0, dont do anything
	CIRCLE:
	mov dx,ax;previous num
	inc cx
	inint ax
	cmp dx,ax;if previous==present
	jne CIRCLEREP
	CIRCLE2:
	mov dx,ax
	inc cx
	inint ax
	cmp dx,ax;if present==next
	jne CIRCLEREP
	inc bx
	jmp CIRCLEREP2
	CIRCLEREP:
	cmp cx,COUNT
	jb CIRCLE
	jmp OUTPRINT
	
	CIRCLEREP2:
	cmp cx,COUNT
	jb CIRCLE2
	
	OUTPRINT:
	outint bx
    finish
code ends
    end start 
