#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>
#include <memory.h>
#include <time.h>

#define display_int_matrix(matrix, size, title, flag) {\
    if (title) { printf("\033[0;31m%s\033[0m", title); }\
    for (int i = 0; i < size; i++) { printf("%6d", (matrix)[i]); if (flag && ((i + 1) % flag == 0)) { putchar(10); } }\
    putchar(10);\
}

void add_avx(uint32_t *a, uint32_t *b, uint32_t *dst);

void add(uint32_t *src1, uint32_t *src2, uint32_t *dst)
{

    __m512i zmm0 = _mm512_load_epi32(src1);
    __m512i zmm1 = _mm512_load_epi32(src2);

    zmm0 = _mm512_add_epi32(zmm0, zmm1);
    _mm512_store_epi32(dst, zmm0);
}


int add2(int a, int b);

int add3(int a, int b)
{
    return a + b;
}

int main()
{
    uint32_t data1[] = {
        1,  2,  3,  4,  5,  6,  7,  8,
        9, 10, 11, 12, 13, 14, 15, 16
    };

    uint32_t data2[] = {
        16, 15, 14, 13, 12, 11, 10, 9,
         8,  7,  6,  5,  4,  3,  2, 1
    };

    uint32_t *dst = (uint32_t *)aligned_alloc(16 * sizeof(int), 64);

    uint32_t *a = (uint32_t *)aligned_alloc(16 * sizeof(int), 64);
    uint32_t *b = (uint32_t *)aligned_alloc(16 * sizeof(int), 64);

    memcpy(a, data1, 16 * sizeof(int));
    memcpy(b, data2, 16 * sizeof(int));

    clock_t start;
    clock_t finish;
    clock_t duration;

    start = clock();
    for (int i = 0; i < 1; i++)
    {
        add(a, b, dst);
    }
    finish = clock();
    duration = finish - start;
    display_int_matrix(dst, 16, "", 8);

    int t = add2(12, 10);
    __mmask16 k1 = 0b1111111111111110;

    __attribute__((aligned(64))) uint32_t indices[]  = {
        0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
    };

    __m512i idx = _mm512_load_epi32((void *)indices);
    __m512i src = _mm512_load_epi32((void *)a);
    __m512i d = _mm512_maskz_permutexvar_epi32(k1, idx, src);
    return 0;
}