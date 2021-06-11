#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>
#include <memory.h>

void Add(uint32_t *a, uint32_t *b, uint32_t *dst);

void add(uint32_t *src1, uint32_t *src2, uint32_t *dst)
{
    __m512i zmm0 = _mm512_load_epi32(src1);
    __m512i zmm1 = _mm512_load_epi32(src2);

    zmm0 = _mm512_add_epi32(zmm0, zmm1);
    _mm512_store_epi32(dst, zmm0);
}

void test(uint32_t *s)
{
    for (int i = 0; i < 16; i++)
    {
        if (i && !(i & 7))
        {
            putchar(10);
        }
        printf("%4d", s[i]);
    }
    putchar(10);
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

    Add(a, b, dst);

    test(dst);

    return 0;
}