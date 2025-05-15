#include <stdio.h>
#include <math.h>

void menu() {
    printf("=== Calculadora ===\n");
    printf("1. Soma\n");
    printf("2. Subtração\n");
    printf("3. Multiplicação\n");
    printf("4. Divisão\n");
    printf("5. Potência\n");
    printf("6. Raiz Quadrada\n");
    printf("7. Seno (em radianos)\n");
    printf("8. Cosseno (em radianos)\n");
    printf("9. Tangente (em radianos)\n");
    printf("0. Sair\n");
    printf("===================\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    double num1, num2, resultado;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite dois números: ");
                scanf("%lf %lf", &num1, &num2);
                resultado = num1 + num2;
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 2:
                printf("Digite dois números: ");
                scanf("%lf %lf", &num1, &num2);
                resultado = num1 - num2;
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 3:
                printf("Digite dois números: ");
                scanf("%lf %lf", &num1, &num2);
                resultado = num1 * num2;
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 4:
                printf("Digite dois números: ");
                scanf("%lf %lf", &num1, &num2);
                if (num2 != 0) {
                    resultado = num1 / num2;
                    printf("Resultado: %.2lf\n", resultado);
                } else {
                    printf("Erro: Divisão por zero!\n");
                }
                break;
            case 5:
                printf("Digite a base e o expoente: ");
                scanf("%lf %lf", &num1, &num2);
                resultado = pow(num1, num2);
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 6:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                if (num1 >= 0) {
                    resultado = sqrt(num1);
                    printf("Resultado: %.2lf\n", resultado);
                } else {
                    printf("Erro: Raiz quadrada de número negativo!\n");
                }
                break;
            case 7:
                printf("Digite um ângulo em radianos: ");
                scanf("%lf", &num1);
                resultado = sin(num1);
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 8:
                printf("Digite um ângulo em radianos: ");
                scanf("%lf", &num1);
                resultado = cos(num1);
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 9:
                printf("Digite um ângulo em radianos: ");
                scanf("%lf", &num1);
                resultado = tan(num1);
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        printf("\n");
    } while (opcao != 0);

    return 0;
}