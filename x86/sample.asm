SECTION .data
SECTION .text

global add_avx512, MatrixMultiply

add_avx512:
    vmovdqa32      zmm0,  [rsi]
    vpaddd         zmm0,  zmm0, [rdi]
    vmovdqa32     [rdx],  zmm0
    vzeroupper
    ret

MatrixMultiply:
    ldtilecfg [rax]
    ret
