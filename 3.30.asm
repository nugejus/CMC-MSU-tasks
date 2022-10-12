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
	mov bx,0
	mov cl,0
	
	CIRCLE:
	inch al;first input of word
	mov ah,al;save first byte
	cmp ah,'S'
	jne PASS0;if first byte=='S'
	inc bx
	L:;loop while input=='.'V','
	inch al
	cmp al,','
	je CIRCLE
	cmp al,'.'
	je FIN
	jmp L
	
	PASS0:;if first byte!='S'	
	inch al;input of after first byte(AFB)
	cmp al,','
	jne PASS1;if AFB==','
	cmp cl,ah
	jne PASS2;if first byte==AFB
	inc bx
	jmp CIRCLE
	PASS2:
	cmp cl,'Z'
	jne CIRCLE;if last byte of the word=='Z'
	inc bx
	jmp CIRCLE
	
	PASS1:;else
	cmp al,'.'
	jne PASS3
	cmp cl,ah
	jne PASS4;if first byte==AFB
	inc bx
	jmp FIN
	PASS4:
	cmp cl,'Z'
	jne FIN;if last byte of the word=='Z'
	inc bx
	jmp FIN
	PASS3:
	mov cl,al;save previous byte
	jmp PASS0
	
	FIN:
	outint bx
    finish
code ends
    end start 
