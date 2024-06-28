
typedef struct {
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[20];
} Cliente;

void cadastrar_cliente(Cliente clientes[], int *num_clientes) {
    Cliente novo_cliente;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &novo_cliente.codigo);

    int i = 0;
    while (i < *num_clientes) {
        if (clientes[i].codigo == novo_cliente.codigo) {
            printf("Erro: Ja existe um cliente com esse codigo.\n");
            return;
        }
        i++;
    }

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", novo_cliente.nome);
    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]s", novo_cliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]s", novo_cliente.telefone);

    clientes[*num_clientes] = novo_cliente;
    (*num_clientes)++;
    printf("Cliente cadastrado com sucesso.\n");
}

void pesquisar_cliente(Cliente clientes[], int num_clientes) {
    int codigo;
    char nome[100];
    int opcao;

    printf("Pesquisar por: 1. Codigo 2. Nome: ");
    scanf("%d", &opcao);

    int i = 0;
    if (opcao == 1) {
        printf("Digite o codigo do cliente: ");
        scanf("%d", &codigo);
        while (i < num_clientes) {
            if (clientes[i].codigo == codigo) {
                printf("Cliente encontrado:\n");
                printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
                return;
            }
            i++;
        }
    } else if (opcao == 2) {
        printf("Digite o nome do cliente: ");
        scanf(" %[^\n]s", nome);
        while (i < num_clientes) {
            if (strcmp(clientes[i].nome, nome) == 0) {
                printf("Cliente encontrado:\n");
                printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
                return;
            }
            i++;
        }
    }
    printf("Cliente não encontrado.\n");
}

void salvar_clientes(Cliente clientes[], int num_clientes) {
    FILE *file = fopen("clientes.dat", "wb");
    fwrite(&num_clientes, sizeof(int), 1, file);
    fwrite(clientes, sizeof(Cliente), num_clientes, file);
    fclose(file);
}

void carregar_clientes(Cliente clientes[], int *num_clientes) {
    FILE *file = fopen("clientes.dat", "rb");
    if (file) {
        fread(num_clientes, sizeof(int), 1, file);
        fread(clientes, sizeof(Cliente), *num_clientes, file);
        fclose(file);
    } else {
        *num_clientes = 0;
    }
}
