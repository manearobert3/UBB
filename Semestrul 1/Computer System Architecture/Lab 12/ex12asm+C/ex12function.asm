
bits 32
global _modul
global _modul1
segment code use32 class=code public
    _modul:
    push ebp
    mov ebp, esp
    mov ecx, [ebp +8] ; lungimea sirului
    mov edi, [ebp +12]    ; sirul destinatie  (d)
    mov esi, [ebp + 16] ; sirul initial    (sir)
    mov ebx,0
    mov edx,0
  
	
    .repet: 
        mov al,[esi+ebx]
        inc ebx
        mov [edi+edx],al
        inc edx
        inc edx
    loop .repet
    mov eax,edi
    mov esp, ebp
    pop ebp
    ret
    
    _modul1:
    push ebp
    mov ebp, esp
    mov ecx, [ebp +8] ; lungimea sirului
    mov edi, [ebp +12]    ; sirul destinatie  (d)
    mov esi, [ebp + 16] ; sirul initial    (sir)
    mov ebx,0
    mov edx,1
  
	
    .repet: 
        mov al,[esi+ebx]
        inc ebx
        mov [edi+edx],al
        inc edx
        inc edx
    loop .repet
    mov eax,edi
    mov esp, ebp
    pop ebp
    ret   
       

