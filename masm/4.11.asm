
include io.asm 

stack segment stack
	dw 128 dup (?)
stack ends

data segment
Q dw 10 dup(?)
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	
	mov bx,0
	L1:
	inint ax
	mov Q[bx],ax
	add bx,2
	cmp bx,20
	jne L1
	
	mov al,3
	dec al
	
	mov ah,0
	mov bx,ax
	shl bx,1
	mov si,Q[bx]
	shl si,1
	mov ax,Q[si]
	
	outint ax

    finish
code ends
    end start 
