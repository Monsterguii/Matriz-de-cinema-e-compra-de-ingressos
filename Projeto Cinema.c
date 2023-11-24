#include <stdio.h>

void obter_nome_filme(char nome_filme[]) {
    printf("Digite o nome do filme: ");
    scanf("%s", nome_filme);
    
    return nome_filme;
}

float calcular_desconto(int identidade) {
    float desconto = 0.0;

    switch (identidade) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            desconto = 0.5;
            break;
        default:
            desconto = 0.0;
    }

    return desconto;
}

int confirmar_identidade() {
    int identidade;

    printf("VOCÊ SE ENCAIXA EM ALGUM DESSES?\n");
    printf("0- NÃO ME ENCAIXO\n");
    printf("1- PESSOA COM DEFICIÊNCIA\n");
    printf("2- ESTUDANTE\n");
    printf("3- IDOSO\n");
    printf("4- DOADOR DE SANGUE\n");
    printf("5- MENOR QUE 12 ANOS\n");
    scanf("%d", &identidade);

    if (identidade < 0 || identidade >= 6) {
        printf("DIGITE UM VALOR VÁLIDO\n");
        return confirmar_identidade();
    } else {
        if (identidade != 0) {
            float desconto = calcular_desconto(identidade);
            printf("Desconto aplicado: %.2f%%\n", desconto * 100);
        }
        return identidade;
    }
}

void desenhar_sala_cinema(int num_cadeiras, char matriz_assentos[][10]) {
    int num_fileiras = num_cadeiras / 10 + (num_cadeiras % 10 != 0 ? 1 : 0);

    int cadeira_atual = 0;
    for (int i = 0; i < num_fileiras; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (cadeira_atual < num_cadeiras) {

                matriz_assentos[i][j] = 'D';
                cadeira_atual++;
            } else {
                matriz_assentos[i][j] = ' ';
            }
        }
    }
}

void imprimir_sala_cinema(int num_cadeiras, char matriz_assentos[][10]) {
    int num_fileiras = num_cadeiras / 10 + (num_cadeiras % 10 != 0 ? 1 : 0);

    for (int i = 0; i < num_fileiras; ++i) {
        for (int j = 0; j < 10; ++j) {
            char estado = matriz_assentos[i][j];
            switch (estado) {
                case 'D':
                    printf("\033[92m%c\033[0m ", estado);
                    break;
                case 'R':
                    printf("\033[91m%c\033[0m ", estado);
                    break;
                case 'C':
                    printf("\033[94m%c\033[0m ", estado);
                    break;
                default:
                    printf("%c ", estado);
            }
        }
        printf("\n");
    }
}

void reservar_assento(int rows, int cols, char matriz[rows][cols]) {
    int linha, coluna;

    printf("DIGITE A LINHA E A COLUNA PARA RESERVAR O ASSENTO (EX: 1 2): ");
    scanf("%d %d", &linha, &coluna);

    if (linha >= 1 && linha <= rows && coluna >= 1 && coluna <= cols) {
        if (matriz[linha - 1][coluna - 1] == 'D') {
            matriz[linha - 1][coluna - 1] = 'R';
            printf("ASSENTO RESERVADO COM SUCESSO!\n");
        } else {
            printf("ASSENTO JÁ ESTÁ RESERVADO OU OCUPADO.\n");
        }
    } else {
        printf("LINHA OU COLUNA INVÁLIDA.\n");
    }
}

void confirmar_compra(int rows, int cols, char matriz[rows][cols], float valor_ingresso, float *faturamento_total) {
    int linha, coluna;

    printf("DIGITE A LINHA E A COLUNA PARA CONFIRMAR A COMPRA DO ASSENTO (EX: 1 2): ");
    scanf("%d %d", &linha, &coluna);

    if (linha >= 1 && linha <= rows && coluna >= 1 && coluna <= cols) {
        if (matriz[linha - 1][coluna - 1] == 'R') {
            printf("Assento selecionado para compra: %d %d\n", linha, coluna);

            int identidade = confirmar_identidade();

            if (identidade == 0) {
                printf("Identidade: Não se aplica\n");
                matriz[linha - 1][coluna - 1] = 'C';
                printf("COMPRA CONFIRMADA! ASSENTO AGORA ESTÁ OCUPADO.\n");
                *faturamento_total += valor_ingresso;
            } else if (identidade > 0 && identidade < 6) {
                float desconto = calcular_desconto(identidade);
                printf("Desconto aplicado: %.2f%%\n", desconto * 100);
                float valor_final = valor_ingresso - (valor_ingresso * desconto);
                matriz[linha - 1][coluna - 1] = 'C';
                printf("COMPRA CONFIRMADA! ASSENTO AGORA ESTÁ OCUPADO.\n");
                *faturamento_total += valor_final;
            } else {
                printf("Identidade: %d\n", identidade);
                printf("COMPRA NÃO CONFIRMADA. Identidade não reconhecida.\n");
            }
        } else {
            printf("VOCÊ SÓ PODE CONFIRMAR A COMPRA DE ASSENTOS RESERVADOS.\n");
        }
    } else {
        printf("LINHA OU COLUNA INVÁLIDA.\n");
    }
}

void cancelar_reserva(int rows, int cols, char matriz[rows][cols]) {
    int linha, coluna;

    printf("DIGITE A LINHA E A COLUNA PARA CANCELAR A RESERVA DO ASSENTO: ");
    scanf("%d %d", &linha, &coluna);

    if (linha >= 1 && linha <= rows && coluna >= 1 && coluna <= cols) {
        if (matriz[linha - 1][coluna - 1] == 'R') {
            matriz[linha - 1][coluna - 1] = 'D';
            printf("RESERVA CANCELADA COM SUCESSO!\n");
        } else {
            printf("NÃO HÁ RESERVA PARA ESTE ASSENTO.\n");
        }
    } else {
        printf("A LINHA OU COLUNA DO CÓDIGO NÃO EXISTE NESTA SALA.\n");
    }
}

int main() {
    int num_cadeiras;
    char nome_filme[100];

    obter_nome_filme(nome_filme);
    printf("Quantas cadeiras você deseja na sala de %s? ", nome_filme);
    scanf("%d", &num_cadeiras);

    if (num_cadeiras <= 0) {
        printf("Erro: O número de cadeiras deve ser maior que zero.\n");
        return 1;
    }

    char matriz_assentos[100][10];
    desenhar_sala_cinema(num_cadeiras, matriz_assentos);

    int opcao;
    float valor_ingresso;

    printf("Digite o valor do ingresso: ");
    scanf("%f", &valor_ingresso);

    float faturamento_total = 0.0;

    do {
        printf("\n1 - EXIBIR ASSENTOS\n");
        printf("2 - RESERVAR ASSENTO\n");
        printf("3 - CONFIRMAR COMPRA\n");
        printf("4 - CANCELAR RESERVA\n");
        printf("0 - SAIR\n");

        printf("ESCOLHA UMA OPÇÃO: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimir_sala_cinema(num_cadeiras, matriz_assentos);
                break;
            case 2:
                reservar_assento(num_cadeiras, 10, matriz_assentos);
                break;
            case 3:
                confirmar_compra(num_cadeiras, 10, matriz_assentos, valor_ingresso, &faturamento_total);
                break;
            case 4:
                cancelar_reserva(num_cadeiras, 10, matriz_assentos);
                break;
            case 0:
                printf("SAINDO DO PROGRAMA.\n");
                break;
            default:
                printf("OPÇÃO INVÁLIDA.\n");
        }

    } while (opcao != 0);

    printf("Faturamento total: %.2f\n", faturamento_total);

    return 0;
}