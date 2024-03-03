bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
a db 101
b db 6
c dw 2
e dd 10
x dq 202
segment code use 32 class=code
start:


;ex 12 mul and div (a*b+2)/(a+7-c)+d+x; a,c-byte; b-word; d-doubleword; x-qword           (6*2+2)/(6+7-6)       ;14/7=2
; a db 6 b dw 2 c db 6 d dd 10 x dq 10 result will be 22
;mov eax,0
;mov edx,0
;mov al,[a]
;mul word[b];dx:ax=a*b+2
;add al,2
;mov ebx,0
;mov ecx,0
;mov bl,[a]
;add bl,7
;sub bl,[c]
;div bx ; ax=(a*b+2)/(a+7-c)
;mov dx,0
;add ax,word[d]
;add dx,word[d+2]
;push dx
;push ax
; pop eax
;add eax,dword[x]
;add edx,dword[x+4]

;ex 12 signed representation: mul and div (a*b+2)/(a+7-c)+d+x; a,c-byte; b-word; d-doubleword; x-qword
;mov ebx,0
;mov eax,0
;add al,[a]
;add al,7
;sub al,[c]
;cbw
;mov bx,ax
;mov eax,0
;mov al,[a]
;cbw
;imul word[b]
;add al,2
;idiv bx;ax=a*b+2 / a+7-c
;cwd
;add ax,word[d]
;adc dx,word[d+2]
;push dx
;push ax
;pop eax
;cdq
;add eax,dword[x]
;adc edx,dword[x+2] ; edx:eax=(a*b+2)/(a+7-c)+d+x

;ex 27 multiplications signed (100+a+b*c)/(a-100)+e+x/a; a,b-byte; c-word; e-doubleword; x-qword
;(100+101+6*2)/(101-100)+10+202/101 = 225 ; values: a db 101 b db 6 c dw 2 e dd 10 x dq 202 result should be 225
;mov eax,0
;mov ebx,0
;mov al,[a]
;sub al,100
;cbw
;mov bx,ax          ; bx=a-100
;mov eax,0
;mov al,[b]
;cbw
;imul word[c]
;add al,[a]
;add ax,100         ; dx:ax=100+a+b*c
;idiv bx            ;ax= (100+a+b*c)/(a-100)
;cwde
;add eax,[e]
;mov ebx,eax        ; ebx=(100+a+b*c)/(a-100)+e
;mov ecx,0
;mov al,[a]
;cbw
;cwde
;mov ecx,eax
;mov eax,0
;mov edx,0
;mov eax,dword[x]
;mov edx,dword[x+4]
;idiv ecx
;add ebx,eax        ; ebx= (100+a+b*c)/(a-100)+e+x/a

;ex 27 multiplications unsigned (100+a+b*c)/(a-100)+e+x/a; a,b-byte; c-word; e-doubleword; x-qword
;mov eax,0
;mov al,[a]
;sub al,100
;mov ebx,0
;mov bl,al
;mov al,[b]
;mov ah,0
;mul word[c]
;add al,[a]
;add ax,100
;mov bh,0
;div bx          ; ax=(100+a+b*c)/(a-100)
;mov bx,ax       ; bx=(100+a+b*c)/(a-100)
;mov al,[a]
;mov ah,0
;mov dx,0
;push dx
;push ax
;pop eax
;mov ecx,eax
;mov eax,dword[x]
;mov edx,dword[x+4]
;div ecx         ;eax=x/a
;mov cx,0
;push cx
;push bx
;pop ebx
;add ebx,eax
;add ebx,[e]      ; ebx = (100+a+b*c)/(a-100)+e+x/a; 

;ex 27 (100+a+b*c)/(a-100)+e+x/a; a,b-byte; c-word; e-doubleword; x-qword

;mov eax,0
;mov ebx,0
;mov ecx,0
;mov al,[b]  ;al=b
;mul word[c] ;ax=b*c
;add al,[a]  ;ax=b*c+a
;add al,100  ;ax=100+a+b*c   . 202+12=214
;mov bl,[a]  ;bx=a
;sub bl,100  ;bx=a-100
;div bl      ;ax=dx:ax/bx   ax=(100+a+b*c)/(a-100)
;mov dx,0    ;dx=0
;mov bx,ax
;mov cx,0
;mov ax, word[e]
;mov dx, word[e+2]
;add ax,bx
;add dx,cx   ;dx:ax=(100+a+b*c)/(a-100)+e    202+12 ;214/2+12 = 107+12=119;
;mov ecx,0
;mov ebx,0
;mov cx,dx
;mov bx,ax
;mov eax, dword[x]
;mov edx, dword[x+4]


; ex 12 unsigned representation (a+b+d)-(a-c+d)+(b-c)   a - byte, b - word, c - double word, d - qword 6202-(102-4+6000)=
; 6202- 6098  =104 + (100-4)= 200
;mov eax,0
;mov al,[a]
;mov ah,0
;add ax,[b]
;mov edx,0
;add eax, dword [d]
;add edx, dword [d+4]
;mov ebx,eax
;mov ecx,edx
;mov eax,0
;mov edx,0
;mov al,[a]
;sub eax,[c]
;add eax, dword [d]
;add edx, dword [d+4]
;sub ebx,eax
;sub ecx,edx
;mov eax,0
;mov edx,0
;mov ax,[b]
;sub eax,[c]
;add ebx,eax

;ex 27 (a+c)-(d+b) unsigned representation a - byte, b - word, c - double word, d - qword    (102+4)-(6100)= 106-6100= 5994
;mov eax,0
;mov al,[a]
;add eax,[c]
;mov ebx,eax
;mov edx,0
;mov eax,0
;add eax, [d]
;add edx, [d+4]
;add ax,[b]
;mov ecx,0
;sub ebx,eax
;sub ecx,edx

;ex 12 a - byte, b - word, c - double word, d - qword - Signed representation (a-b-c)+(d-b-c)-(a-d)= (102-100-4)+(6000-104)-(102-6000)= -2+5896-(-5898)=11792
;mov eax,0
;mov al,[a] ; al=a
;cbw     
;sbb ax,[b]  ;ax=a-b
;cwd 
;push dx
;push ax
;pop eax ;eax=a-b
;sbb eax,[c] ;eax= a-b-c
;mov ebx,0
;mov edx,0
;mov ebx,dword[d]
;mov ecx,dword[d+4] ;ecx:ebx=d
;add eax,ebx
;adc edx,ecx
;mov ebx,eax
;mov ecx,edx ;ebx:ecx= a-b-c+d
;mov eax,0 
;mov edx,0
;mov ax,[b]
;push dx
;push ax
;pop eax     ;eax=b
;cdq
;sub ebx,eax
;sbb ecx,edx ;ecx:ebx=a-b-c+d-b
;mov eax,0
;mov edx,0
;mov eax,[c]
;cdq
;cwd
;sub ebx,eax
;sbb ecx,edx
;mov eax,0
;mov al,[a]
;cbw
;cwd
;push dx
;push ax
;pop eax
;cdq
;sub eax,dword [d]
;sbb edx,dword [d+4]
;sub ebx,eax
;sub ecx,edx

;ex 27 (d+d-c)-(c+c-a)+(c+a) = (11996)-(-94)+(4+102)=12196 
;mov eax,0
;mov edx,0
;add eax,dword[d]
;adc edx,dword [d+4]
;add eax,dword[d]
;adc edx,dword [d+4]
;mov ebx,eax
;mov ecx,edx
;mov eax,[c]
;cdq
;sub ebx,eax
;sbb ecx,edx
;mov eax,0
;sub al,[a]
;cbw
;cwd
;add ax, word [c]
;adc dx, word [c+2]
;add ax, word [c]
;adc dx, word [c+2]
;push dx
;push ax
;pop eax
;cdq
;sub ebx,eax
;sbb ecx,edx
;mov eax,0
;mov al,[a]
;cbw
;cwd
;add ax,word [c]
;add dx,word [c+2]
;push dx
;push ax
;pop eax
;cdq
;add ebx,eax
;adc ecx,edx


push dword 0
call [exit]
