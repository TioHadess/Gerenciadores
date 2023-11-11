#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo{
    int id;
    char marca[20];
    char modelo[20];
    char placa[20];
    int ano;
}Veiculo;

static int ultimoId = 1;

typedef struct ponteiro {
    Veiculo dados;
    struct ponteiro* proximo;
} ponteiro;

ponteiro* criarPonteiro(Veiculo veiculo) {
    ponteiro* novoPonteiro = (ponteiro*)malloc(sizeof(ponteiro));
    novoPonteiro->dados = veiculo;
    novoPonteiro->proximo = NULL;
    return novoPonteiro;
}

void cadastrarVeiculo(ponteiro** lista, Veiculo veiculo) {
    veiculo.id = ultimoId++;
    ponteiro* novoPonteiro = criarPonteiro(veiculo);

    if (*lista == NULL) {
        *lista = novoPonteiro;
    } else {
        ponteiro* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novoPonteiro;
    }
}

void listarVeiculos(ponteiro* lista) {
    ponteiro* temp = lista;
    while (temp != NULL) {
        printf("ID: %d, Marca: %s, Modelo: %s, Placa: %s, Ano: %d\n", temp->dados.id, temp->dados.marca, temp->dados.modelo, temp->dados.placa, temp->dados.ano);
        temp = temp->proximo;
    }
}

void alterarVeiculo(ponteiro* lista, int id, char marca[], char modelo[], char placa[], int* ano) {
    ponteiro* temp = lista;
    while (temp != NULL) {
        if (temp->dados.id == id) {
            printf("Nova marca para o veiculo %d: ", id);
            scanf("%s", temp->dados.marca);
            printf("Novo modelo para o veiculo %d: ", id);
            scanf("%s", temp->dados.modelo);
            printf("Nova placa para o veiculo %d: ", id);
            scanf("%s", temp->dados.placa);
            printf("Novo ano para o veiculo %d: ", id);
            scanf("%d", &temp->dados.ano);
            return;
        }
        temp = temp->proximo;
    }
    printf("Veiculo com ID %d nao encontrado.\n", id);
}

void apagarVeiculo(ponteiro** lista, int id) {
    ponteiro* temp = *lista;
    ponteiro* anterior = NULL;

    while (temp != NULL && temp->dados.id != id) {
        anterior = temp;
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Veiculo com ID %d nao encontrado.\n", id);
        return;
    }

    if (anterior == NULL) {
        *lista = temp->proximo;
    } else {
        anterior->proximo = temp->proximo;
    }

    free(temp);
    printf("Veiculo removido com sucesso.\n");
}

void liberarLista(ponteiro* lista) {
    ponteiro* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

void salvarLista(ponteiro* lista) {
    FILE* arquivo = fopen("veiculos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    ponteiro* temp = lista;
    while (temp != NULL) {
        fprintf(arquivo, "%d %s %s %s %d\n", temp->dados.id, temp->dados.marca, temp->dados.modelo, temp->dados.placa, temp->dados.ano);
        temp = temp->proximo;
    }
    fclose(arquivo);
    printf("Lista salva com sucesso.\n");
}

void carregarLista(ponteiro** lista) {
    FILE* arquivo = fopen("veiculos.txt", "r");

    if (arquivo == NULL) {
        printf("Arquivo nao encontrado. Iniciando com lista vazia.\n");
        return;
    }

    Veiculo veiculo;
    while (fscanf(arquivo, "%d %s %s %s %d", &veiculo.id, veiculo.marca, veiculo.modelo, veiculo.placa, &veiculo.ano) == 5) {
        cadastrarVeiculo(lista, veiculo);
    }

    fclose(arquivo);
    printf("Lista carregada com sucesso.\n");
}

int main() {
    ponteiro* lista = NULL;
    int opcao, id, ano;
    char marca[20], modelo[20], placa[20];
    Veiculo novoVeiculo;

    do {
        printf("1 - Cadastrar Veiculo\n");
        printf("2 - Alterar Veiculo\n");
        printf("3 - Apagar Veiculo\n");    
        printf("4 - Listar Veiculos\n");
        printf("5 - Salvar Lista\n");
        printf("6 - Carregar Lista\n");
        printf("0 - Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Cadastrando novo Veiculo...\n");
                printf("Marca do veiculo: ");
                scanf("%s", novoVeiculo.marca);
                printf("Modelo do veiculo: ");
                scanf("%s", novoVeiculo.modelo);
                printf("Placa do veiculo: ");
                scanf("%s", novoVeiculo.placa);
                printf("Ano do Veiculo: ");
                scanf("%d", &novoVeiculo.ano);
                cadastrarVeiculo(&lista, novoVeiculo);
                break;
            case 2:
                printf("Alterando Veiculo...\n");
                printf("Digite o ID do veiculo que deseja alterar: ");
                scanf("%d", &id);
                alterarVeiculo(lista, id, marca, modelo, placa, &ano);
                break;
            case 3:
                printf("Removendo Veiculo...\n");
                printf("Digite o ID do veiculo que deseja apagar: ");
                scanf("%d", &id);
                apagarVeiculo(&lista, id);
                break;
            case 4:
                printf("Listando Veiculos...\n");
                listarVeiculos(lista);
                break;
            case 5:
                printf("Salvando Lista...\n");
                salvarLista(lista);
                break;
            case 6:
                printf("Carregando Lista...\n");
                carregarLista(&lista);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarLista(lista);
    return 0;
}

