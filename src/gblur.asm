SECTION .text

global add_avx

; void Add(uint32_t *a, uint32_t *b, uint32_t *dst);
add_avx:
    vmovdqa32  zmm0, [rsi]
    vpaddd     zmm0,  zmm0, [rdi]
    vmovdqa32 [rdx],  zmm0
    vzeroupper
    ret