#include <stdio.h>
#include <immintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#include "sl.h"

#define DisplayIntergerMatrix(matrix, size, title, flag) {\
    if (title) \
    { \
        printf("\033[0;31m%s\033[0m", title); \
    } \
    else \
    { \
        printf("\033[0;31m%s\033[0m", #matrix": "); \
    } \
    for (int i = 0; i < size; i++) \
    { \
        printf("%6d", (matrix)[i]); \
        if (flag && ((i + 1) % flag == 0)) \
        { \
            putchar(10); \
        } \
    } \
    putchar(10); \
}

void Add16Intergers()
{
    uint32_t SLALIGN(64) a[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    uint32_t SLALIGN(64) b[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    uint32_t SLALIGN(64) c[16] = { 0 };

    __m512i zmm0 = _mm512_load_epi32(a);
    __m512i zmm1 = _mm512_load_epi32(b);

    zmm0 = _mm512_add_epi32(zmm0, zmm1);
    _mm512_store_epi32(c, zmm0);

    DisplayIntergerMatrix(a, 8, "a:", 16);
    DisplayIntergerMatrix(b, 8, "b:", 16);
    DisplayIntergerMatrix(c, 8, "c:", 16);
}

extern "C" void MatrixMultiply();
void TestMatrixMultiply()
{
    MatrixMultiply();
}


int main()
{
    Add16Intergers();
    TestMatrixMultiply();

    return 0;
}
