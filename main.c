#include <stdio.h>
#include <string.h>
#include <time.h>

#include <cliente.h>
#include <estadias.h>
#include <estadias.h>
#include <estadias.h>

void main() {
    Cliente clientes[100];
    Funcionario funcionarios[100];
    Estadia estadias[100];
    Quarto quartos[100];

    int num_clientes = 0, num_funcionarios = 0, num_estadias = 0, num_quartos = 0;

    carregar_clientes(clientes, &num_clientes);
    carregar_funcionarios(funcionarios, &num_funcionarios);
    carregar_estadias(estadias, &num_estadias);
    carregar_quartos(quartos, &num_quartos);

    // QUARTOS GERADOS
    if (num_quartos == 0) {
        quartos[0] = (Quarto){101, 2, 150.0, "desocupado"};
        quartos[1] = (Quarto){102, 3, 200.0, "desocupado"};
        quartos[2] = (Quarto){103, 4, 250.0, "desocupado"};
        num_quartos = 3;
    }

    int opcao;
    do {
        printf("\n\nMenu:\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Estadia\n");
        printf("4. Dar Baixa em Estadia\n");
        printf("5. Pesquisar Cliente\n");
        printf("6. Pesquisar Funcionario\n");
        printf("7. Listar Estadias de um Cliente\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente(clientes, &num_clientes);
                salvar_clientes(clientes, num_clientes);
                break;
            case 2:
                cadastrar_funcionario(funcionarios, &num_funcionarios);
                salvar_funcionarios(funcionarios, num_funcionarios);
                break;
            case 3:
                cadastrar_estadia(estadias, &num_estadias, clientes, num_clientes, quartos, num_quartos);
                salvar_estadias(estadias, num_estadias);
                salvar_quartos(quartos, num_quartos);
                break;
            case 4:
                dar_baixa_estadia(estadias, &num_estadias, quartos, num_quartos);
                salvar_estadias(estadias, num_estadias);
                salvar_quartos(quartos, num_quartos);
                break;
            case 5:
                pesquisar_cliente(clientes, num_clientes);
                break;
            case 6:
                pesquisar_funcionario(funcionarios, num_funcionarios);
                break;
            case 7: {
                int codigo_cliente;
                printf("Digite o codigo do cliente: ");
                scanf("%d", &codigo_cliente);
                listar_estadias_cliente(estadias, num_estadias, codigo_cliente);
                break;
            }
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 8);

    return 0;

}
