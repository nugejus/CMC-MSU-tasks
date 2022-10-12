include io.asm

stack segment stack
	dw 128 dup (?)
stack ends

data segment
COUNT equ 10
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	mov cx,0
	
	CIRCLELOOP:
	inc cx
	inch al
	cmp al,' '
	jne PASS2
	outch al
	CIRCLE2:
	cmp cx,COUNT
	je DONE
	inc cx
	inch al
	cmp al,' '
	jne CIRCLE
	jmp CIRCLE2
	PASS2:
	cmp al,'p'
	jne CIRCLE
	inc cx
	inch al
	cmp al,'h'
	jne PASS3
	outch 'f'
	jmp CIRCLE3
	PASS3:
	outch 'p'
	jmp CIRCLE
	
	CIRCLE:
	outch al
	CIRCLE3:
	cmp cx,COUNT
	jne CIRCLELOOP
	DONE:
    finish
code ends
    end start 
