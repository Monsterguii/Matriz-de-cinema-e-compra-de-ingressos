#include <stdio.h>
#include <math.h>

// Função que calcula o valor do polinomio com um dado X
void PolinomioX() {
    int grau;
    printf("Digite o grau do polinômio: ");
    scanf("%d", &grau);

    float coeficientes[grau + 1];
    for (int i = 0; i <= grau; i++) {
        printf("Digite o coeficiente para x^%d: ", grau - i);
        scanf("%f", &coeficientes[i]);
    }

    float x;
    printf("Digite o valor de x: ");
    scanf("%f", &x);

    float resultado = 0;
    for (int i = 0; i <= grau; i++) {
        resultado += coeficientes[i] * pow(x, grau - i);
    }
    printf("Resultado: %f\n", resultado);
}

void somarPolinomios() {
    int grau1, grau2;

    printf("Digite o grau do primeiro polinômio: ");
    scanf("%d", &grau1);

    printf("Digite o grau do segundo polinômio: ");
    scanf("%d", &grau2);

    int grauResultado = (grau1 > grau2) ? grau1 : grau2; // Grau do polinômio resultado

    float coeficientes1[grauResultado + 1];
    float coeficientes2[grauResultado + 1];
    float resultado[grauResultado + 1];

    for (int i = 0; i <= grauResultado; i++) {
        coeficientes1[i] = 0;
        coeficientes2[i] = 0;
        resultado[i] = 0;
    }

    printf("Digite os coeficientes do primeiro polinômio:\n");
    for (int i = 0; i <= grau1; i++) {
        printf("Digite o coeficiente para x^%d: ", grau1 - i);
        scanf("%f", &coeficientes1[i]);
    }

    printf("Digite os coeficientes do segundo polinômio:\n");
    for (int i = 0; i <= grau2; i++) {
        printf("Digite o coeficiente para x^%d: ", grau2 - i);
        scanf("%f", &coeficientes2[i]);
    }

    for (int i = 0; i <= grauResultado; i++) {
        resultado[i] = coeficientes1[i] + coeficientes2[i];
    }

    printf("A soma dos polinômios é:\n");
    for (int i = 0; i <= grauResultado; i++) {
        if (resultado[i] != 0) {
            printf("%.2fx^%d ", resultado[i], grauResultado - i);
            if (i < grauResultado) {
                printf("+ ");
            }
        }
    }
    printf("\n");
}

void multiplicarPolinomios() {
    int grau1, grau2;

    printf("Digite o grau do primeiro polinômio: ");
    scanf("%d", &grau1);

    printf("Digite o grau do segundo polinômio: ");
    scanf("%d", &grau2);

    int grauResultado = grau1 + grau2;

    float coeficientes1[grau1 + 1];
    float coeficientes2[grau2 + 1];
    float resultado[grauResultado + 1];

        for (int i = 0; i <= grauResultado; i++) {
        coeficientes1[i] = 0;
        coeficientes2[i] = 0;
        resultado[i] = 0;
    }

    printf("Digite os coeficientes do primeiro polinômio:\n");
    for (int i = 0; i <= grau1; i++) {
        printf("Digite o coeficiente para x^%d: ", grau1 - i);
        scanf("%f", &coeficientes1[i]);
    }

    printf("Digite os coeficientes do segundo polinômio:\n");
    for (int i = 0; i <= grau2; i++) {
        printf("Digite o coeficiente para x^%d: ", grau2 - i);
        scanf("%f", &coeficientes2[i]);
    }

    for (int i = 0; i <= grau1; i++) {
        for (int j = 0; j <= grau2; j++) {
            resultado[i + j] += coeficientes1[i] * coeficientes2[j];
        }
    }

    printf("A multiplicação dos polinômios é:\n");
    for (int i = 0; i <= grauResultado; i++) {
        if (resultado[i] != 0) {
            printf("%.2fx^%d ", resultado[i], grauResultado - i);
            if (i < grauResultado) {
                printf("+ ");
            }
        }
    }
    printf("\n");
}


int main() {
    int opcao;

    printf("MENU\n\n");
    printf("1- Calcular o valor de um polinomio\n");
    printf("2- Calcular a soma de dois polinomios\n");
    printf("3- Calcular a multiplicação de dois polinomios\n");

    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            PolinomioX();
            printf("\n");
            main();
            break;
        case 2:
            somarPolinomios();
            printf("\n");
            main();
            break;
        case 3:
            multiplicarPolinomios();
            printf("\n");
            main();
            break;
        default:
            printf("Opção inválida\n");
            main();
            break;
    }
    
    return 0;
}