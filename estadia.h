
typedef struct {
    int codigo_estadia;
    struct tm data_entrada;
    struct tm data_saida;
    int quantidade_diarias;
    int codigo_cliente;
    int numero_quarto;
} Estadia;

void salvar_estadias(Estadia estadias[], int num_estadias) {
    FILE *file = fopen("estadias.dat", "wb");
    fwrite(&num_estadias, sizeof(int), 1, file);
    fwrite(estadias, sizeof(Estadia), num_estadias, file);
    fclose(file);
}

void carregar_estadias(Estadia estadias[], int *num_estadias) {
    FILE *file = fopen("estadias.dat", "rb");
    if (file) {
        fread(num_estadias, sizeof(int), 1, file);
        fread(estadias, sizeof(Estadia), *num_estadias, file);
        fclose(file);
    } else {
        *num_estadias = 0;
    }
}

void listar_estadias_cliente(Estadia estadias[], int num_estadias, int codigo_cliente) {
    printf("Estadias do cliente %d:\n", codigo_cliente);

    int i = 0;
    while (i < num_estadias) {
        if (estadias[i].codigo_cliente == codigo_cliente) {
            printf("Codigo da Estadia: %d\nQuarto: %d\nData de Entrada: %02d/%02d/%04d %02d:%02d\nData de Saida: %02d/%02d/%04d %02d:%02d\nQuantidade de Diarias: %d\n",
                   estadias[i].codigo_estadia, estadias[i].numero_quarto,
                   estadias[i].data_entrada.tm_mday, estadias[i].data_entrada.tm_mon + 1, estadias[i].data_entrada.tm_year + 1900, estadias[i].data_entrada.tm_hour, estadias[i].data_entrada.tm_min,
                   estadias[i].data_saida.tm_mday, estadias[i].data_saida.tm_mon + 1, estadias[i].data_saida.tm_year + 1900, estadias[i].data_saida.tm_hour, estadias[i].data_saida.tm_min,
                   estadias[i].quantidade_diarias);
        }
        i++;
    }
}

void dar_baixa_estadia(Estadia estadias[], int *num_estadias, Quarto quartos[], int num_quartos) {
    int codigo_estadia;
    printf("Digite o codigo da estadia: ");
    scanf("%d", &codigo_estadia);

    int i = 0;
    while (i < *num_estadias) {
        if (estadias[i].codigo_estadia == codigo_estadia) {
            int numero_quarto = estadias[i].numero_quarto;
            int quantidade_diarias = estadias[i].quantidade_diarias;
            float valor_diaria = 0;

            int j = 0;
            while (j < num_quartos) {
                if (quartos[j].numero_quarto == numero_quarto) {
                    valor_diaria = quartos[j].valor_diaria;
                    strcpy(quartos[j].status, "desocupado");
                    break;
                }
                j++;
            }

            float valor_total = quantidade_diarias * valor_diaria;
            printf("Valor total a ser pago: Rs%.2f\n", valor_total);

            int k = i;
            while (k < *num_estadias - 1) {
                estadias[k] = estadias[k + 1];
                k++;
            }
            (*num_estadias)--;
            printf("Estadia finalizada com sucesso.\n");
            return;
        }
        i++;
    }
    printf("Erro: Estadia nao encontrada.\n");
}

void cadastrar_estadia(Estadia estadias[], int *num_estadias, Cliente clientes[], int num_clientes, Quarto quartos[], int num_quartos) {
    Estadia nova_estadia;
    int codigo_cliente, quantidade_hospedes;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    int cliente_encontrado = 0;
    int i = 0;
    while (i < num_clientes) {
        if (clientes[i].codigo == codigo_cliente) {
            cliente_encontrado = 1;
            break;
        }
        i++;
    }
    if (!cliente_encontrado) {
        printf("Erro: Cliente nao cadastrado.\n");
        return;
    }

    printf("Digite a quantidade de hospedes: ");
    scanf("%d", &quantidade_hospedes);

    int quarto_encontrado = 0;
    i = 0;
    while (i < num_quartos) {
        if (quartos[i].quantidade_hospedes >= quantidade_hospedes && strcmp(quartos[i].status, "desocupado") == 0) {
            nova_estadia.numero_quarto = quartos[i].numero_quarto;
            strcpy(quartos[i].status, "ocupado");
            quarto_encontrado = 1;
            break;
        }
        i++;
    }
    if (!quarto_encontrado) {
        printf("Erro: Nao ha quartos disponiveis para a quantidade de hospedes desejada.\n");
        return;
    }

    printf("Digite a data de entrada (dd mm yyyy hh mm): ");
    scanf("%d %d %d %d %d", &nova_estadia.data_entrada.tm_mday, &nova_estadia.data_entrada.tm_mon, &nova_estadia.data_entrada.tm_year, &nova_estadia.data_entrada.tm_hour, &nova_estadia.data_entrada.tm_min);
    nova_estadia.data_entrada.tm_mon -= 1;
    nova_estadia.data_entrada.tm_year -= 1900;

    printf("Digite a data de saída (dd mm yyyy hh mm): ");
    scanf("%d %d %d %d %d", &nova_estadia.data_saida.tm_mday, &nova_estadia.data_saida.tm_mon, &nova_estadia.data_saida.tm_year, &nova_estadia.data_saida.tm_hour, &nova_estadia.data_saida.tm_min);
    nova_estadia.data_saida.tm_mon -= 1;
    nova_estadia.data_saida.tm_year -= 1900;

    time_t entrada = mktime(&nova_estadia.data_entrada);
    time_t saida = mktime(&nova_estadia.data_saida);
    double segundos = difftime(saida, entrada);
    nova_estadia.quantidade_diarias = (segundos / (60 * 60 * 24)) + 1;

    nova_estadia.codigo_cliente = codigo_cliente;
    nova_estadia.codigo_estadia = *num_estadias + 1;
    estadias[*num_estadias] = nova_estadia;
    (*num_estadias)++;
    printf("Estadia cadastrada com sucesso.\n");
}
