bits 32

global start

; declare external functions needed by our program
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll
%include "ex27functionul.asm"
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format_string db "sir=%s",10,13,0
    message db "sir=", 0                   ; maximum number of characters to read
    ;text dd 0         ; string to hold the text which is read from file
    ;textmici dd 0
    ;textmari dd 0
    text dd 'asbDFD2Aa',0
    len equ $-text
    textmici times len db 0
    textmari times len db 0
segment code use32 class=code

    start:
        mov eax,text
        push eax
        mov eax,textmici
        push eax
        mov eax,len
        push eax
        call mici
        push edi
        push format_string
        call [printf]
        add esp, 4*2
        mov eax,text
        push eax
        mov eax,textmari
        push eax
        mov eax,len
        push eax
        call mari
        push edi
        push format_string
        call [printf]
        add esp, 4*2
        