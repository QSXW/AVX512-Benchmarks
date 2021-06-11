SECTION .data
msg_format db "hello"
number dw 0x1234

SECTION .text

%macro FDEC_STRIDE 4
%endmacro
global predict_4x4_dc_mmxext

predict_4x4_dc_mmxext:
    mov     eax, 1234
    mov     [rdi], ax
    ret

    