
typedef struct {
    int codigo;
    char nome[100];
    char telefone[20];
    char cargo[50];
    float salario;
} Funcionario;

void cadastrar_funcionario(Funcionario funcionarios[], int *num_funcionarios) {
    Funcionario novo_funcionario;
    printf("Digite o codigo do funcionario: ");
    scanf("%d", &novo_funcionario.codigo);

    int i = 0;
    while (i < *num_funcionarios) {
        if (funcionarios[i].codigo == novo_funcionario.codigo) {
            printf("Erro: Ja existe um funcionario com esse codigo.\n");
            return;
        }
        i++;
    }

    printf("Digite o nome do funcionario: ");
    scanf(" %[^\n]s", novo_funcionario.nome);
    printf("Digite o telefone do funcionario: ");
    scanf(" %[^\n]s", novo_funcionario.telefone);
    printf("Digite o cargo do funcionario: ");
    scanf(" %[^\n]s", novo_funcionario.cargo);
    printf("Digite o salario do funcionario: ");
    scanf("%f", &novo_funcionario.salario);

    funcionarios[*num_funcionarios] = novo_funcionario;
    (*num_funcionarios)++;
    printf("Funcionario cadastrado com sucesso.\n");
}

void pesquisar_funcionario(Funcionario funcionarios[], int num_funcionarios) {
    int codigo;
    char nome[100];
    int opcao;

    printf("Pesquisar por: 1. Codigo 2. Nome: ");
    scanf("%d", &opcao);

    int i = 0;
    if (opcao == 1) {
        printf("Digite o codigo do funcionario: ");
        scanf("%d", &codigo);
        while (i < num_funcionarios) {
            if (funcionarios[i].codigo == codigo) {
                printf("Funcionario encontrado:\n");
                printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
                return;
            }
            i++;
        }
    } else if (opcao == 2) {
        printf("Digite o nome do funcionario: ");
        scanf(" %[^\n]s", nome);
        while (i < num_funcionarios) {
            if (strcmp(funcionarios[i].nome, nome) == 0) {
                printf("Funcionario encontrado:\n");
                printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
                return;
            }
            i++;
        }
    }
    printf("Funcionario nao encontrado.\n");
}

void salvar_funcionarios(Funcionario funcionarios[], int num_funcionarios) {
    FILE *file = fopen("funcionarios.dat", "wb");
    fwrite(&num_funcionarios, sizeof(int), 1, file);
    fwrite(funcionarios, sizeof(Funcionario), num_funcionarios, file);
    fclose(file);
}

void carregar_funcionarios(Funcionario funcionarios[], int *num_funcionarios) {
    FILE *file = fopen("funcionarios.dat", "rb");
    if (file) {
        fread(num_funcionarios, sizeof(int), 1, file);
        fread(funcionarios, sizeof(Funcionario), *num_funcionarios, file);
        fclose(file);
    } else {
        *num_funcionarios = 0;
    }
}
