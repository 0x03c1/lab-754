/*
 * patriot.c — Estação 2: o erro que ceifa
 * ---
 * Esta é uma simulação simplificada do mecanismo de erro de
 * ponto flutuante e de sua acumulação. Ela não reproduz
 * literalmente o software/hardware histórico do Patriot.
 * ---
 * Compilação:
 *   gcc -Wall -Wextra -std=c11 -O2 patriot.c -o patriot
 * ---
 * Uso:
 *   ./patriot
 * ---
 * Author — 0x03C1
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void)
{
    volatile float soma_f = 0.0f;
    double soma_d = 0.0;

    for (int i = 0; i < 10; i++) {
        soma_f += 0.1f;
        soma_d += 0.1;
    }

    printf("=== PARTE A: somar 0.1 dez vezes ===\n");
    printf("float  : %.20f   (== 1.0 ? %s)\n",
           (double)soma_f,
           soma_f == 1.0f ? "SIM" : "NAO");

    printf("double : %.20f   (== 1.0 ? %s)\n\n",
           soma_d,
           soma_d == 1.0 ? "SIM" : "NAO");

    printf("=== PARTE B: o relogio (0,1 s por tique) ===\n");

    printf("%10s | %18s | %18s | %s\n",
           "horas", "tempo acumulado", "tempo real", "erro (s)");

    printf("-----------------------------------------------------------------------\n");

    volatile float t = 0.0f;
    int64_t tiques = 0;

    for (int h = 1; h <= 100; h++) {

        for (int k = 0; k < 36000; k++) {
            t += 0.1f;
            tiques++;
        }

        if (h == 1 || h == 8 || h == 20 ||
            h == 50 || h == 100) {

            double real = (double)tiques * 0.1;
            double erro = real - (double)t;

            printf("%10d | %18.6f | %18.6f | %.6f\n",
                   h, (double)t, real, erro);
        }
    }

    printf("\nUm misil Scud voa a ~1676 m/s.\n");
    printf("Calcule: quantos METROS de erro de posicao cada linha representa?\n\n");

    return 0;
}
