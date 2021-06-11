#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>

void predict_4x4_dc_mmxext(uint8_t *src);

int main()
{
    int32_t s[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    uint64_t *s1 = (uint64_t *)malloc(1024);

    __m512i zmm0 = *(__m512i *)s1;

    return 0;
}