; The following code will open/create a file called "ana.txt" in the current folder,
; and it will write a text at the end of this file.

; The program will use:
; - the function fopen() to open/create the file
; - the function fprintf() to write a text to file
; - the function fclose() to close the created file.

; Because the fopen() call uses the file access mode "a", the writing operations will
; append text at the end of the file. The file will be created if it does not exist.
; For details about the file access modes see the section "Theory".

bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
extern exit, scanf, printf
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "problem.asm", 0       ; filename to be read
    access_mode db "w", 0           ; file access mode:
                                    ; a - appends to a file. Append data at
                                    ; the end of the file.
    file_descriptor dd -1           ; variable to hold the file descriptor
    text db "Ana are si pere.", 0   ; text to append to file
    a dd 12
    format db "%d ",0
    message db "c=", 0
    b dw 0
    access_mode1 db "w", 0
    ; our code starts here
segment code use32 class=code
    start:
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen

        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final
        mov eax,0
        repeta:
        push dword message ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4*1
        push dword a ; pushing the parameters on the stack from right to left
        push dword format  
        call [scanf]
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

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
]       
        add esp, 4 * 2
        mov eax,0
        mov eax,[a]
        cmp eax,0
        je done
        push dword eax ; pushing the parameters on the stack from right to left
        push dword format
        push dword [file_descriptor]        
        call [fprintf]       ; calling the printf function
        add esp, 4 * 3
        loop repeta

 
        done:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0
        call [exit]