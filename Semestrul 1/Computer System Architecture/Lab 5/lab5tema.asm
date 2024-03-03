bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ex12 data:
    ;s1 db 'a', 'b', 'c', 'd', 'e', 'f'
    ;k equ $-s1
    ;s2 db '1', '2', '3', '4', '5'
    ;l equ $-s1
    ;p equ $-s2
    ;d times l db 0
    
    ; ex27 data:
    s1 db 1, 3, 6, 2, 3, 2
    s2 db 6, 3, 8, 1, 2, 5
    l equ $-s2
    d times l db 0 
    
; our code starts here
segment code use32 class=code
    start:
    ;mov eax,0
    ;mov al,p
    ;mov bl,2
    ;div bl ;al = length of s2 / 2
    ;mov ecx,0
    ;mov cl,al
    ;mov esi,1
    ;mov edi,0
    ;mov edx,ecx
    ;jecxz sfarsit
    ;Repeta:
    ;    mov al,[s2+esi]
     ;   mov [d+edi],al
     ;   inc esi
     ;   inc esi
     ;   inc edi
    ;loop Repeta
    ;sfarsit:
    ;mov edi,edx
    ;mov eax,0
    ;mov al,k
    ;mov bl,2
    ;div bl ;al = length of s1 / 2
    ;mov ecx,0
    ;mov cl,al
    ;mov esi,0
    ;jecxz sfarsit1
    ;Repeta1:
    ;    mov al,[s1+esi]
    ;    mov [d+edi],al
    ;    inc esi
    ;    inc esi
    ;    inc edi
    ;loop Repeta1
    ;sfarsit1:
    
    
    
    
    mov ecx,l
    mov esi,0
    jecxz sfarsit
    Repeta:
        mov ax,0
        mov bx,0
        mov al,[s1+esi]
        mov bl,[s2+esi]
        sub al,bl
        mov [d+esi],al
        inc esi
    loop Repeta
    sfarsit:
       
    

    ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
