/*
 * dissect.c — Estação 1: a anatomia de um float
 * ---
 * Compilação:
 *   gcc -Wall -Wextra -std=c11 -O2 dissect.c -o dissect
 * ---
 * Uso:
 *   ./dissect 0.1
 * ---
 * O programa trabalha com um float IEEE-754 de 32 bits:
 *   1 bit  -> sinal
 *   8 bits -> expoente
 *   23 bits -> fração
 * ---
 * Author — 0x03C1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef union {
    float    f;
    uint32_t u;
} FloatBits;

static void print_bits(uint32_t u)
{
    for (int i = 31; i >= 0; i--) {
        putchar((u >> i) & UINT32_C(1) ? '1' : '0');

        if (i == 31 || i == 23)
            putchar(' ');
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <numero>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr = NULL;

    FloatBits fb;
    fb.f = strtof(argv[1], &endptr);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Erro: '%s' não é um número válido.\n", argv[1]);
        return EXIT_FAILURE;
    }

    uint32_t sinal =
        (fb.u >> 31) & UINT32_C(0x1);

    uint32_t expo_raw =
        (fb.u >> 23) & UINT32_C(0xFF);

    uint32_t fracao =
        fb.u & UINT32_C(0x7FFFFF);

    printf("\nvalor digitado : %s\n", argv[1]);
    printf("valor guardado : %.20f\n", (double)fb.f);
    printf("hexadecimal    : 0x%08" PRIX32 "\n\n", fb.u);

    printf("bits           : ");
    print_bits(fb.u);

    printf("\n");
    printf("                 ^ ^------^ ^---------------------^\n");
    printf("                 | |        |\n");
    printf("                 | |        +--- fração (23 bits)\n");
    printf("                 | +------------ expoente (8 bits)\n");
    printf("                 +-------------- sinal (1 bit)\n\n");

    printf("sinal          : %" PRIu32 "  (%s)\n",
           sinal, sinal ? "negativo" : "positivo");

    printf("expoente bruto : %" PRIu32 "\n", expo_raw);

    if (expo_raw == 0 && fracao == 0) {
        printf("expoente real  : ---\n");
        printf("CLASSIFICACAO  : ZERO (%s)\n",
               sinal ? "-0.0" : "+0.0");

    } else if (expo_raw == 0) {
        printf("expoente real  : -126 (subnormal)\n");
        printf("CLASSIFICACAO  : SUBNORMAL\n");

    } else if (expo_raw == 255 && fracao == 0) {
        printf("CLASSIFICACAO  : INFINITO (%s)\n",
               sinal ? "-inf" : "+inf");

    } else if (expo_raw == 255) {
        printf("CLASSIFICACAO  : NaN\n");

    } else {
        int expoente_real = (int)expo_raw - 127;

        printf("expoente real  : %d  (%" PRIu32 " - 127)\n",
               expoente_real, expo_raw);

        printf("CLASSIFICACAO  : NORMAL\n");

        printf("\nvalor = (-1)^%" PRIu32
               " x 1.(fracao) x 2^%d\n",
               sinal, expoente_real);
    }

    printf("\n");

    return EXIT_SUCCESS;
}
