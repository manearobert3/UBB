bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf 
extern exit, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
	segment data use32 class=data
        a dd -8
        apariti dd 0
        string db 'a','b','d','c','a','f'
        len equ $-string
		format  db "a=%d (base 10),", 0  ; definining the format
        format2 db "a=%x (base 16) ", 0
        n dd 0
        message db "character=", 0
        format3 db "%c", 0
        format4 db "character is %c,",0
        format5 db "number of occurences is %d",0
	segment code use32 class=code
		;start:
            push dword [a] ; pushing the parameters on the stack from right to left
            push dword format  
            call [printf]       ; calling the printf function
            add esp, 4 * 2     ; cleaning the parameters from the stack
            push dword [a] ; pushing the parameters on the stack from right to left
            push dword format2  
            call [printf]       ; calling the printf function
            add esp, 4 * 2     ; cleaning the parameters from the stack
		; ...
        start:
       
        ; will call printf(message) => will print "n="
        ; place parameters on stack
        push dword message ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4*1       ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
                                                   
        ; will call scanf(format, n) => will read a number in variable n
        ; place parameters on stack from right to left
        push dword n       ; ! addressa of n, not value
        push dword format3
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
                           ; 4 = size of a dword; 2 = no of perameters
        mov esi,string
        cld
        mov ecx,len
        mov bl,[n]
        mov bh,0
        repeta1:
            lodsb
            cmp al,bl
            je done
            jmp final
            done:
            add bh,1
            final:
        loop repeta1
        push dword [n] ; pushing the parameters on the stack from right to left
        push dword format4  
        call [printf]       ; calling the printf function
        add esp, 4 * 2     ; cleaning the parameters from the stack
        mov byte [apariti],bh
        push dword [apariti] ; pushing the parameters on the stack from right to left
        ;mov al,bh
        ;mov ebx,0
        ;mov bl,al
        ;push dword [ebx]
        push dword format5  
        call [printf]       ; calling the printf function
        add esp,4*2     ; cleaning the parameters from the stack
        

            push    dword 0      ; push the parameter for exit onto the stack
            call    [exit]       ; call exit to terminate the program