typedef struct {
    int numero_quarto;
    int quantidade_hospedes;
    float valor_diaria;
    char status[20]; // OCUPADO - DESOCUPADO
} Quarto;

void salvar_quartos(Quarto quartos[], int num_quartos) {
    FILE *file = fopen("quartos.dat", "wb");
    fwrite(&num_quartos, sizeof(int), 1, file);
    fwrite(quartos, sizeof(Quarto), num_quartos, file);
    fclose(file);
}

void carregar_quartos(Quarto quartos[], int *num_quartos) {
    FILE *file = fopen("quartos.dat", "rb");
    if (file) {
        fread(num_quartos, sizeof(int), 1, file);
        fread(quartos, sizeof(Quarto), *num_quartos, file);
        fclose(file);
    } else {
        *num_quartos = 0;
    }
}
