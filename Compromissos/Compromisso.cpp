#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Compromisso {
    char dataRef[11];
    char descricaoCompromisso[100];
    struct Compromisso *proximo;
};

struct PilhaCompromissos {
    struct Compromisso *topo;
};

void inicializarPilha(struct PilhaCompromissos *pilha) {
    pilha->topo = NULL;
}

void empilharCompromisso(struct PilhaCompromissos *pilha, char *dataRef, char *descricaoCompromisso) {
    struct Compromisso *novoCompromisso = (struct Compromisso *)malloc(sizeof(struct Compromisso));
    if (novoCompromisso == NULL) {
        printf("Erro ao alocar memória para novo compromisso.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novoCompromisso->dataRef, dataRef);
    strcpy(novoCompromisso->descricaoCompromisso, descricaoCompromisso);

    novoCompromisso->proximo = pilha->topo;
    pilha->topo = novoCompromisso;
}

struct Compromisso *desempilharCompromisso(struct PilhaCompromissos *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }

    struct Compromisso *compromissoRemovido = pilha->topo;
    pilha->topo = compromissoRemovido->proximo;
    compromissoRemovido->proximo = NULL;
    return compromissoRemovido;
}

void listarCompromissosPilha(struct PilhaCompromissos pilha) {
    printf("Compromissos na Pilha:\n");
    struct Compromisso *atual = pilha.topo;
    while (atual != NULL) {
        printf("Data: %s\n", atual->dataRef);
        printf("Descrição: %s\n", atual->descricaoCompromisso);
        printf("\n");
        atual = atual->proximo;
    }
}

void liberarPilha(struct PilhaCompromissos *pilha) {
    struct Compromisso *atual = pilha->topo;
    while (atual != NULL) {
        struct Compromisso *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    pilha->topo = NULL;
}

void salvarPilha(struct PilhaCompromissos pilha, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        exit(EXIT_FAILURE);
    }

    struct Compromisso *atual = pilha.topo;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s\n", atual->dataRef, atual->descricaoCompromisso);
        atual = atual->proximo;
    }

    fclose(arquivo);
}

void carregarPilha(struct PilhaCompromissos *pilha, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar.\n");
        exit(EXIT_FAILURE);
    }

    liberarPilha(pilha);

    char dataRef[11];
    char descricaoCompromisso[100];
    while (fscanf(arquivo, "%10[^;];%99[^\n]\n", dataRef, descricaoCompromisso) == 2) {
        empilharCompromisso(pilha, dataRef, descricaoCompromisso);
    }

    fclose(arquivo);
}

int main() {
    struct PilhaCompromissos minhaPilha;
    inicializarPilha(&minhaPilha);

    int opcao;
    char data[11];
    char descricao[100];

    do {
        printf("\n1 - Adicionar compromisso\n");
        printf("2 - Desempilhar compromisso\n");
        printf("3 - Listar compromissos\n");
        printf("4 - Salvar pilha em arquivo\n");
        printf("5 - Carregar pilha de arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a data (dd/mm/yyyy): ");
                scanf("%s", data);
                printf("Digite a descrição do compromisso: ");
                getchar(); // Limpar o buffer do teclado
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = '\0'; // Remover o caractere de nova linha
                empilharCompromisso(&minhaPilha, data, descricao);
                break;

            case 2:
                if (minhaPilha.topo != NULL) {
                    struct Compromisso *compromissoDesempilhado = desempilharCompromisso(&minhaPilha);
                    printf("Compromisso desempilhado:\n");
                    printf("Data: %s\n", compromissoDesempilhado->dataRef);
                    printf("Descrição: %s\n", compromissoDesempilhado->descricaoCompromisso);
                    free(compromissoDesempilhado);
                } else {
                    printf("Pilha vazia, nenhum compromisso desempilhado.\n");
                }
                break;

            case 3:
                listarCompromissosPilha(minhaPilha);
                break;

            case 4:
                salvarPilha(minhaPilha, "pilha_compromissos.txt");
                printf("Pilha salva em arquivo.\n");
                break;

            case 5:
                carregarPilha(&minhaPilha, "pilha_compromissos.txt");
                printf("Pilha carregada do arquivo.\n");
                break;

            case 0:
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarPilha(&minhaPilha);

    return 0;
}