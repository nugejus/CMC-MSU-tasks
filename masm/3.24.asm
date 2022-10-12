include io.asm 

stack segment stack
	dw 128 dup (?)
stack ends

data segment
K equ 5
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	mov cx,0
	inint ax
	L1:
	inc cx
	inint bx
	add ax,bx
	cmp cx,K
	jb L1
	outint ax
    finish
code ends
    end start 
