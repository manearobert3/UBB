bits 32
global _modul
global _modul1
segment code use32 class=code public
modul:
    push ebp
    mov ebp, esp
    mov ecx, [ebp+8] ; lungimea sirului
    mov edi, [ebp+12]    ; sirul destinatie  (d)
    mov esi, [ebp + 16] ; sirul initial    (sir)
    mov ebx,0
    mov edx,0
    
    .repet:
        cmp ebx,ecx
        ja sfarsit
        mov al,[esi+ebx]
        inc ebx
        cmp al,'a'
        jb .repet
        cmp al,'z'
        ja .repet
        mov [edi+edx],al
        inc edx
        mov al,0
    loop .repet
    sfarsit:
    mov eax,edi
    mov esp, ebp
    pop ebp
    ret
    
modul1:
    push ebp
    mov ebp, esp
    mov ecx, [ebp+8] ; lungimea sirului
    mov edi, [ebp+12]    ; sirul destinatie  (d)
    mov esi, [ebp + 16] ; sirul initial    (sir)
    mov ebx,0
    mov edx,0
    
    .repet:
        cmp ebx,ecx
        ja sfarsit1
        mov al,[esi+ebx]
        inc ebx
        cmp al,'A'
        jb .repet
        cmp al,'Z'
        ja .repet
        mov [edi+edx],al
        inc edx
        mov al,0
    loop .repet
        sfarsit1:
    mov eax,edi
    mov esp, ebp
    pop ebp
    ret
