include io.asm

stack segment stack
	dw 128 dup (?)
stack ends

data segment
DONE equ 10
data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	mov ah,0
	mov ch,0

	mov cl,2
	OUTERCIRCLE:
	mov bl,2
	INNERCIRCLE:
	mov al,bl
	outint ax
	outch "x"
	outint cx
	outch "="
	mul cl
	outint ax
	newline
	inc bl
	cmp bl,DONE
	jb INNERCIRCLE
	inc cl
	cmp cl,DONE
	jb OUTERCIRCLE
	
    finish
code ends
    end start 
