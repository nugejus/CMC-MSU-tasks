include io.asm

stack segment stack
	dw 128 dup (?)
stack ends

data segment
x dw 10 dup(?)
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	
	mov cx,10
	mov bx,20
	L1:
	sub bx,2
	inint ax
	mov x[bx],ax
	loop L1
	
	newline
	;a proccess start
	mov ax,0
	mov cx,10
	mov bx,20
	L2:
	sub bx,2
	mov dx,x[bx]
	cmp dx,0
	jne J1
	inc ax
	J1:
	LOOP L2
	outint ax
	;a proccess end
	newline
	;b proccess start  (not finished)
	mov cx,9
	mov bx,18
	mov ax,x[bx]
	L3:
	sub bx,2
	cmp ax,x[bx]
	jg J2
	mov ax,x[bx]
	J2:
	loop L3
	outint ax
	;b proccess end
	
    finish
code ends
    end start 
