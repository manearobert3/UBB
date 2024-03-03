bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    ;data for the first exercise, exercise 12
    sir dd 120593ac3h, 2134ad43h, 32453234h
    len1 equ $-sir
    len equ ($-sir)/4
    d times len db 0
    d1 times len db 0
    ;date for the second exercise, exercise 27
    ;s dd 12345678h, 1A2B3C4Dh, 1234DC76h
    ;lungime equ ($-s)/4
    ;d resb 3
    ;aux_ecx dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi,sir
        cld
        mov edi,d
        cld
        mov ecx,len
        repeta:
            lodsd
            stosb
        loop repeta
        mov edi,d1
        mov esi,sir
        cld
        mov ecx,len
        repeta1:
            lodsw
            lodsw
            mov al,ah
            stosb
        loop repeta1
        
         ;mov esi, s
        ;cld
        ;mov ecx,lungime
        ;mov ebx, 0
        ;repeta:
        ;    lodsd
        ;    mov dh, ah
        ;    mov [aux_ecx], ecx
        ;    mov cl, 0Ah ;10 in baza 10 este A din baza 1, facem impartirea si verificam restul din AH
        ;    mov al, ah
        ;    mov ah, 0
        ;    div cl
        ;        test ah,ah
        ;        jz multiplu
        ;        jnz nu_multiplu
        ;        multiplu:
        ;            mov [d+ebx], dh
        ;            inc ebx
        ;            mov ecx, [aux_ecx]
        ;        nu_multiplu:
        ;            mov ecx, [aux_ecx]
        ;loop repeta
        
        ;mov esi, d
        ;cld
        ;mov ecx, ebx
        ;afisare:
        ;    lodsb
        ;loop afisare
        
                
            
            
            
            
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
