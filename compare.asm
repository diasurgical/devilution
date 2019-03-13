push ebp
mov ebp, esp
push ecx
push ecx
push ebx
push esi
push edi
push 0x0A
mov [ebp-0x08], ecx
pop edx
mov cl, 0x39
call <imm_fn>
mov esi, [ebp+0x1C]
mov edi, eax
imul esi, esi, 0x54D8
inc edi
xor ebx, ebx
shl edi, 0x06
cmp [esi+0x4E6A78], bl
jle $+0x1C
push 0x04
mov cl, 0x39
pop edx
call <imm_fn>
inc eax
shl eax, 0x06
add edi, eax
inc ebx
movsx eax, byte ptr [esi+0x4E6A78]
cmp ebx, eax
jl $-0x1C
mov ebx, [ebp-0x08]
and dword ptr [ebp-0x04], 0x00
imul ebx, ebx, 0xB0
cmp dword ptr [ebx+0x516890], 0x00
jle $+0x1E
push 0x06
mov cl, 0x39
pop edx
call <imm_fn>
inc eax
shl eax, 0x06
add edi, eax
inc [ebp-0x04]
mov eax, [ebp-0x04]
cmp eax, [ebx+0x516890]
jl $-0x1E
mov al, [esi+0x4E6A20]
test al, al
jnz $+0x2
add edi, edi
cmp al, 0x01
jnz $+0x7
mov eax, edi
sar eax, 0x02
add edi, eax
mov ecx, [esi+0x4E6A5C]
lea eax, [esi+0x4E6A58]
add [eax], edi
mov edx, [eax]
cmp edx, ecx
jle $+0x2
mov [eax], ecx
lea eax, [esi+0x4E6A50]
mov esi, [esi+0x4E6A54]
add [eax], edi
mov ecx, [eax]
cmp ecx, esi
jle $+0x2
mov [eax], esi
mov ecx, [ebp+0x1C]
push 0x02
pop edx
call <imm_fn>
xor eax, eax
inc eax
pop edi
mov [ebx+0x516894], eax
pop esi
mov [0x6A5C94], eax
pop ebx
leave
ret 0x1C
