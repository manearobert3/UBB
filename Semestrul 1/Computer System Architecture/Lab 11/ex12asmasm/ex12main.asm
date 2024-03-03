
bits 32
global start

extern printf, exit
import printf msvcrt.dll
import exit msvcrt.dll
%include "ex12function.asm"
segment data use32 class=data
	format_string db "sir=%s",10,13,0
    sir  dw  'abcd'
    sir2 dw 'efgh'
    len equ $-sir
    len2 equ $-sir2
    d times len db 0
    d2 times len db 0
    
segment code use32 class=code

; programul "principal"       
start:
    mov eax,sir
    push eax
    mov eax,d
    push eax
    mov eax,len2
    push eax
	call impar ; apelez impar pentru a pune caracterele primului sir pe pozitii impare in sirul destinatie d
    mov eax,sir2
    push eax
    mov eax,d
    push eax
    mov eax,len2
    push eax
	call par ; apelez par pentru a pune caracterele celui de al doilea sir pe pozitii pare in sirul destinatie d
    
    ; afisare rezultat:
	push edi
	push format_string
	call [printf]
	add esp, 4*2
    
    ; reapelez cele 2 functii dand ca parametrii pe stiva aceleasi siruri in ordine inversa
    
    mov eax,sir2
    push eax
    mov eax,d2
    push eax
    mov eax,len2
    push eax
	call impar ; apelez impar pentru a pune caracterele sirului sir2 pe pozitii impare in sirul destinatie d2
    mov eax,sir
    push eax
    mov eax,d2
    push eax
    mov eax,len2
    push eax
	call par ; apelez par pentru a pune caracterele celui sirului sir pe pozitii pare in sirul destinatie d2
    
    ; afisare rezultat:
	push edi
	push format_string
	call [printf]
	add esp, 4*2

	push 0
	call [exit]
