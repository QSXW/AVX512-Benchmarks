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
    for (int i = 0; i < 1000000000; i++)
    {
        add_avx(a, b, dst);
    }
    finish = clock();
    duration = finish - start;
    display_int_matrix(dst, 16, "", 8);

    return 0;
}