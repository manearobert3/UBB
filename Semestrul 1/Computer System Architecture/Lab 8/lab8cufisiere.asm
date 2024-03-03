bits 32 

global start        

; declare external functions needed by our program
extern exit              
import exit msvcrt.dll  
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
extern fopen ,printf
import fscanf msvcrt.dll
extern fprintf ,fread,fclose,fscanf
extern exit, scanf
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "problem.asm", 0  ; numele fisierului care va fi creat
    mod_acces db "w", 0          ; modul de deschidere a fisierului - 
                                 ; w - pentru scriere. daca fiserul nu exista, se va crea 
    mod_acces2 db "r", 0
    text db "smecher.", 0    ; textul care va fi scris in fisier
                                    
    descriptor_fis dd -1         ; variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    a db 123
    b db '0'
    format2 db "number insert here: %d",0
    format db "%d ", 0
    message db "character=", 0
; our code starts here
segment code use32 class=code
    start:
        ; apelam fopen pentru a crea fisierul
        ; functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces   
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        ; scriem textul in fisierul deschis folosind functia fprintf
        ; fprintf(descriptor_fis, text)
        ;repeta:
        push dword message ; ! on the stack is placed the address of the string, not its value
        call [printf]      ; call function printf for printing
        add esp, 4*1
        push dword a ; pushing the parameters on the stack from right to left
        push dword format  
        call [scanf]       
        add esp, 4 * 2
        ;mov al,[a]
        ;cmp al,[b]
        ;je done
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2;
        push dword [a]
        push dword format
        call [fprintf]
        add esp, 4*2
        ;loop repeta
        ; apelam functia fclose pentru a inchide fisierul
        ; fclose(descriptor_fis)
            done:
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
      final:
        
        ; exit(0)
        push    dword 0      
        call    [exit]        