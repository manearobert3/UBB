%ifndef _EX27FUNCTIONUL_ASM_ ; 
%define _EX27FUNCTIONUL_ASM_ ; 
mici:
    mov ecx, [esp+4] ; lungimea sirului
    mov edi, [esp+8]    ; sirul destinatie  (d)
    mov esi, [esp + 12] ; sirul initial    (sir)
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
    ret
    
mari:
    mov ecx, [esp+4] ; lungimea sirului
    mov edi, [esp+8]    ; sirul destinatie  (d)
    mov esi, [esp + 12] ; sirul initial    (sir)
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
    ret
%endif