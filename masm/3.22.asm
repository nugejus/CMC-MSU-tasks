
include io.asm 

stack segment stack
	dw 128 dup (?)
stack ends

data segment
 B db 'correct'
 C db 'not corrext'
 B1 dw B
 C1 dw C

data ends

code segment 'code'
	assume ss:stack, ds:data, cs:code

start:
	mov ax,data
	mov ds,ax
	mov ax,data
	mov ds,ax
	
  mov bx,0
  L:
   inch al
   cmp al, '.'
   je M1
   cmp al, '('
   jne M2
   inc bl
   M2:
   cmp al, ')'
   jne L
   dec bl
  jmp L
  M1:
  	outint bx
  cmp bx,0
  jne NO
  mov ax, B1
  jmp FIN
  NO:
  mov ax, C1
FIN:
  outstr
 END:
 finish
code ends
    end start 
