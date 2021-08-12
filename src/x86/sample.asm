
SECTION .data
message db "Hello world\n"

SECTION .text
global add_avx
add_avx:
    vmovdqa32      zmm0,  [rsi]
    vpaddd         zmm0,  zmm0, [rdi]
    vmovdqa32     [rdx],  zmm0
    vzeroupper
    ret

%define ctrl 0x1F &
%define param(a, b) ((a) + (a) * (b))

global add2
add2:
    mov         ebx, esi
    mov         eax, ctrl 0xd
    ret