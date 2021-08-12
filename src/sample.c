#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>
#include <memory.h>
#include <time.h>

#define ALIGN(v, n) v __attribute__((aligned(n)))

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

typedef struct char64 {
    char data[64];
} char64;

void test_hflip()
{
    // static uint8_t m0[16] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
     static uint8_t m0[16] = { 14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1 };

    uint8_t *a = (uint8_t *)aligned_alloc(1920 * sizeof(int), 64);
    uint8_t *b = (uint8_t *)aligned_alloc(1920 * sizeof(int), 64);

    for (int i = 0; i < 1920; i++) {
        a[i] = i;
    }
    memset(b, 0, 1920 * sizeof(float));

    char64 *t1;
    char64 *t2;
    __m512i m = _mm512_broadcast_i64x2(*(__m128i *)m0);
    for (int i = 0; i < 1920; i += 64*2)
    {
        __m512i m1 = _mm512_permutex_epi64(*(__m512i *)(a + i), 0x4e);
        __m512i m2 = _mm512_permutex_epi64(*(__m512i *)(a + i + 64), 0x4e);

        __m256i m3 = _mm512_extracti64x4_epi64(m1, 0);
        __m256i m4 = _mm512_extracti64x4_epi64(m2, 0);
        t1 = (char64 *)&m1;
        t2 = (char64 *)&m2;
        m1 = _mm512_inserti64x4(m1, m3, 0);
        m2 = _mm512_inserti64x4(m2, m4, 0);
        t1 = (char64 *)&m1;
        t2 = (char64 *)&m2;
    }

    int pause = 0;
}

static void test_convolution()
{
    char64 *c1;
    char64 *c2;

    uint8_t ALIGN(a[64], 64) = { 0 };
    uint8_t ALIGN(b[64], 64) = { 0 };

    for (int i = 0; i < 64; i++)
    {
        a[i] = i;
        b[i] = i + 64;
    }

    __m256i m1 = _mm256_unpacklo_epi8(*(__m256i *)a, *(__m256i *)b);
    __m256i m2 = _mm256_unpacklo_epi16(m1, *(__m256i *)b);

    return;
}

static void test_ternarylogic()
{
    char64 *t1;
    char64 *t2;

    __m512i a;
    __m512i m1 = _mm512_ternarylogic_epi32 (a, a, a, 0xff);
    __mmask64 k = _mm512_cmpgt_epi8_mask(a, m1);
    t1 = (char64 *)&m1;
    return;
}

int main()
{
    test_hflip();
    test_convolution();
    test_ternarylogic();

    return 0;
}
