#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
    char nome[50];
    float preco;
};

struct No {
    int numero;
    struct Produto produto;
    struct No* esquerda;
    struct No* direita;
};

void exibirMenu();
void inserirNo(struct No** pRaiz);
void inserirNoRecursivo(struct No** no, int numero, struct Produto* produto);
void removerNo(struct No** pRaiz);
struct No* maiorDireita(struct No* no);
void removerNoRecursivo(struct No** pRaiz, int numero);
void buscarPreOrdem(struct No* pRaiz);
void buscarPreOrdemRecursivo(struct No* no);
void buscarEmOrdem(struct No* pRaiz);
void buscarEmOrdemRecursivo(struct No* no);
void buscarPosOrdem(struct No* pRaiz);
void buscarPosOrdemRecursivo(struct No* no);
void limparTela();

int main() {
    struct No* pRaiz = NULL;
    int op;

    do {
        exibirMenu();
        printf("\nEscolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                inserirNo(&pRaiz);
                break;
            case 2:
                removerNo(&pRaiz);
                break;
            case 3:
                buscarPreOrdem(pRaiz);
                break;
            case 4:
                buscarEmOrdem(pRaiz);
                break;
            case 5:
                buscarPosOrdem(pRaiz);
                break;
            case 0:
                printf("Encerrando o programa. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        if (op != 0) {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');  // Limpa o buffer do teclado
            getchar();  // Aguarda o usuário pressionar Enter
        }

    } while (op != 0);

    return 0;
}

void exibirMenu() {
    printf("* * * MENU DE OPÇÕES * * *\n");
    printf("1. Incluir nó\n");
    printf("2. Remover nó\n");
    printf("3. Buscar pré-ordem\n");
    printf("4. Buscar em ordem\n");
    printf("5. Buscar pós-ordem\n");
    printf("0. Encerrar\n");
}

void inserirNo(struct No** pRaiz) {
    limparTela();

    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;

    printf("\nProduto: ");
    getchar(); // Limpa o buffer do teclado
    fgets(novoNo->produto.nome, sizeof(novoNo->produto.nome), stdin);
    novoNo->produto.nome[strcspn(novoNo->produto.nome, "\n")] = '\0'; // Remove a quebra de linha

    printf("\nPreço do produto: ");
    scanf("%f", &novoNo->produto.preco);

    printf("\nDigite um número (referência na árvore): ");
    int numero;
    scanf("%d", &numero);

    inserirNoRecursivo(pRaiz, numero, &(novoNo->produto));

    printf("Nó incluído com sucesso!\n");
}


void inserirNoRecursivo(struct No** no, int numero, struct Produto* produto) {
    if (*no == NULL) {
        *no = (struct No*)malloc(sizeof(struct No));
        (*no)->numero = numero;
        (*no)->produto = *produto;
        (*no)->esquerda = NULL;
        (*no)->direita = NULL;
    } else if (numero < (*no)->numero) {
        inserirNoRecursivo(&(*no)->esquerda, numero, produto);
    } else if (numero > (*no)->numero) {
        inserirNoRecursivo(&(*no)->direita, numero, produto);
    }
}

void removerNo(struct No** pRaiz) {
    limparTela();
    printf("\nDigite um número para remover: ");
    int numero;
    scanf("%d", &numero);

    removerNoRecursivo(pRaiz, numero);

    printf("Nó removido com sucesso!\n");
}

struct No* maiorDireita(struct No* no) {
    if (no->direita != NULL) {
        return maiorDireita(no->direita);
    } else {
        struct No* aux = no;
        if (no->esquerda != NULL) {
            no = no->esquerda;
        } else {
            no = NULL;
        }
        return aux;
    }
}

void removerNoRecursivo(struct No** pRaiz, int numero) {
    if (*pRaiz != NULL) {
        if (numero < (*pRaiz)->numero) {
            removerNoRecursivo(&(*pRaiz)->esquerda, numero);
        } else if (numero > (*pRaiz)->numero) {
            removerNoRecursivo(&(*pRaiz)->direita, numero);
        } else {
            struct No* pAux = *pRaiz;

            if ((*pRaiz)->esquerda == NULL && (*pRaiz)->direita == NULL) {
                *pRaiz = NULL;
            } else if ((*pRaiz)->esquerda == NULL) {
                *pRaiz = (*pRaiz)->direita;
                pAux->direita = NULL;
            } else if ((*pRaiz)->direita == NULL) {
                *pRaiz = (*pRaiz)->esquerda;
                pAux->esquerda = NULL;
            } else {
                pAux = maiorDireita((*pRaiz)->esquerda);
                pAux->esquerda = (*pRaiz)->esquerda;
                pAux->direita = (*pRaiz)->direita;
                (*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
                *pRaiz = pAux;
            }

            free(pAux);
        }
    }
}

void buscarPreOrdem(struct No* pRaiz) {
    limparTela();
    printf("Busca Pré-Ordem:\n");
    buscarPreOrdemRecursivo(pRaiz);
}

void buscarPreOrdemRecursivo(struct No* no) {
    if (no != NULL) {
        printf("Número: %d, Produto: %s, Preço: %.2f\n", no->numero, no->produto.nome, no->produto.preco);
        buscarPreOrdemRecursivo(no->esquerda);
        buscarPreOrdemRecursivo(no->direita);
    }
}

void buscarEmOrdem(struct No* pRaiz) {
    limparTela();
    printf("Busca Em Ordem:\n");
    buscarEmOrdemRecursivo(pRaiz);
}

void buscarEmOrdemRecursivo(struct No* no) {
    if (no != NULL) {
        buscarEmOrdemRecursivo(no->esquerda);
        printf("Número: %d, Produto: %s, Preço: %.2f\n", no->numero, no->produto.nome, no->produto.preco);
        buscarEmOrdemRecursivo(no->direita);
    }
}

void buscarPosOrdem(struct No* pRaiz) {
    limparTela();
    printf("Busca Pós-Ordem:\n");
    buscarPosOrdemRecursivo(pRaiz);
}

void buscarPosOrdemRecursivo(struct No* no) {
    if (no != NULL) {
        buscarPosOrdemRecursivo(no->esquerda);
        buscarPosOrdemRecursivo(no->direita);
        printf("Número: %d, Produto: %s, Preço: %.2f\n", no->numero, no->produto.nome, no->produto.preco);
    }
}

void limparTela() {
    // Use "clear" no Linux/Mac e "cls" no Windows
    system("clear || cls");
}
