/*
 * monstros.c — Estação 3: o zoológico do IEEE-754
 * ---
 * Compilação:
 *   gcc -Wall -Wextra -std=c11 -O2 monstros.c -o monstros
 * ---
 * ATENÇÃO:
 *   Compile SEM -ffast-math.
 * ---
 * Este programa explora zeros assinados, infinito, NaN,
 * epsilon, absorção e não associatividade.
 * ---
 * Author — 0x03C1
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>

typedef union {
    float    f;
    uint32_t u;
} FB;

static void mostra(const char *nome, float v)
{
    FB b;
    b.f = v;

    printf("%-22s = %-16g  hex=0x%08" PRIX32 "\n",
           nome, (double)v, b.u);
}

int main(void)
{
    printf("=== 1. OS DOIS ZEROS ===\n");

    float zp = 0.0f;
    float zn = -0.0f;

    mostra("+0.0", zp);
    mostra("-0.0", zn);

    printf("+0.0 == -0.0 ?          %s\n",
           zp == zn ? "SIM" : "NAO");

    printf("1/+0.0 = %g     1/-0.0 = %g\n",
           1.0f / zp, 1.0f / zn);

    printf(">> Os bits sao diferentes mas a comparacao diz iguais. Explique.\n\n");


    printf("=== 2. INFINITO ===\n");

    volatile float inf = FLT_MAX;
    inf = inf * 2.0f;

    mostra("1.0/0.0 (ideia)", inf);
    mostra("inf + 1", inf + 1.0f);
    mostra("inf * 2", inf * 2.0f);

    printf(">> Somar 1 ao infinito nao muda nada. Por que isso e COERENTE?\n\n");


    printf("=== 3. NaN: o numero que nao e numero ===\n");

    float nan_v = inf - inf;

    mostra("inf - inf", nan_v);

    printf("nan == nan ?            %s\n",
           nan_v == nan_v ? "SIM" : "NAO");

    printf("nan != nan ?            %s\n",
           nan_v != nan_v ? "SIM" : "NAO");

    printf("nan <  1.0 ?            %s\n",
           nan_v < 1.0f ? "SIM" : "NAO");

    printf("nan >= 1.0 ?            %s\n",
           nan_v >= 1.0f ? "SIM" : "NAO");

    printf(">> DESAFIO: escreva um teste de NaN sem usar isnan().\n\n");


    printf("=== 4. EPSILON: o limite da resolucao ===\n");

    printf("FLT_EPSILON = %g\n", FLT_EPSILON);

    printf("1.0f + 1e-8f == 1.0f ?  %s\n",
           (1.0f + 1e-8f) == 1.0f ? "SIM" : "NAO");

    printf("1.0f + 1e-7f == 1.0f ?  %s\n",
           (1.0f + 1e-7f) == 1.0f ? "SIM" : "NAO");

    printf(">> Encontre o MENOR x tal que 1.0f + x != 1.0f.\n\n");


    printf("=== 5. ABSORCAO: o grande engole o pequeno ===\n");

    float grande = 1e7f;

    printf("1e7 + 1.0  = %.1f   (mudou? %s)\n",
           (double)(grande + 1.0f),
           (grande + 1.0f) != grande ? "SIM" : "NAO");

    printf("1e8 + 1.0  = %.1f   (mudou? %s)\n",
           (double)(1e8f + 1.0f),
           (1e8f + 1.0f) != 1e8f ? "SIM" : "NAO");

    printf(">> A partir de que magnitude somar 1.0 vira no-op? Descubra.\n\n");


    printf("=== 6. A SOMA NAO E ASSOCIATIVA ===\n");

    float a = 1e8f;
    float b = -1e8f;
    float c = 1.0f;

    printf("(a+b)+c = %g\n",
           (double)((a + b) + c));

    printf("a+(b+c) = %g\n",
           (double)(a + (b + c)));

    printf(">> Mesmos numeros, ordens diferentes, resultados diferentes.\n");
    printf(">> Que consequencia isso tem para computacao PARALELA?\n\n");

    return 0;
}
