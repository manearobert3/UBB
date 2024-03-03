
%ifndef _EX12FUNCTION_ASM_ ; 
%define _EX12FUNCTION_ASM_ ; 
impar:
    mov ecx, [esp+4] ; lungimea sirului
    mov edi, [esp+8]    ; sirul destinatie  (d)
    mov esi, [esp + 12] ; sirul initial    (sir)
    mov ebx,0
    mov edx,0
  
	
    .repet: 
        mov al,[esi+ebx]
        inc ebx
        mov [edi+edx],al
        inc edx
        inc edx
    loop .repet 
    ret
    
par:
    mov ecx, [esp+4] ; lungimea sirului
    mov edi, [esp+8]    ; sirul destinatie  (d)
    mov esi, [esp + 12] ; sirul initial    (sir)
    mov ebx,0
    mov edx,1
  
	
    .repet: 
        mov al,[esi+ebx]
        inc ebx
        mov [edi+edx],al
        inc edx
        inc edx
    loop .repet 
    ret   
       
%endif
