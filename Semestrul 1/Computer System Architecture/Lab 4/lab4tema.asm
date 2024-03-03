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
    ;a dw 0111011101010111b
    ;b dw 1001101110111110b
    ;c dw 0
    n db 0
    a dq 0111_0111_0101_0111_0111_0111_0101_1111_0111_0111_0101_0111_0111_0111_0101_0111b
    ;b dd 1110_1110_1110_1010_1110_1110_1110_1010b
        ;c= 1010_1110 
; our code starts here
;Given the words A and B, compute the doubleword C as ;follows:
;the bits 0-6 of C have the value 0
;the bits 7-9 of C are the same as the bits 0-2 of A
;the bits 10-15 of C are the same as the bits 8-13 of B
;the bits 16-31 of C have the value 1
segment code use32 class=code
    start:
    ;mov bx, 0
    ;and bx, 1111111110000000b
    ;mov ax,[a]
    ;and ax,0000000000000111b
    ;mov cl,7
    ;rol ax,cl 
    ;or bx,ax    ;0000001110000000
    ;mov ax,[b]
    ;and ax, 0011111100000000b
    ;mov cl,2
    ;rol ax,cl
    ;or bx,ax  ; 0110111110000000
    ;mov cx,1111111111111111b
    ;push cx
    ;push bx
    ;pop ebx     ; 0110 1111 1000 0000
    
; Given the quadword A, obtain the integer number N represented on the bits 35-37 of A. Then obtain the the doubleword B by rotating the low doubleword of A N positions to the right. Obtain the byte C as follows:
    ;the bits 0-3 of C are the same as the bits 8-11 of B
    ;the bits 4-7 of C are the same as the bits 16-19 of B

    mov eax,dword[a]
    mov edx,dword[a+4]
    mov ebx,edx
    and ebx,0000_0000_0000_0000_0000_0000_0011_1000b
    mov cl,3
    ror ebx,3
    mov ecx,0
    mov cl,bl ; cl=n
    mov edx,0
    ror eax,cl
    mov edx,eax ; edx=B
    mov eax,0
    mov ebx,0   
    mov eax,0
    mov eax,edx
    and eax, 0000_0000_0000_0000_0000_1111_0000_0000b
    mov cl, 8
    ror eax,8
    or bl,al
    mov eax,edx
    and eax, 0000_0000_0000_1111_0000_0000_0000_0000b
    mov cl, 12
    ror eax,cl
    or bl,al
    
    
    
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
