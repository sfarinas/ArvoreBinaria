package ava2;
import java.util.Scanner;

class Produto {
    String nome;
    float preco;

    Produto(String nome, float preco) {
        this.nome = nome;
        this.preco = preco;
    }
}

class No {
    int numero;
    Produto produto;
    No esquerda;
    No direita;

    No(int numero, Produto produto) {
        this.numero = numero;
        this.produto = produto;
        this.esquerda = null;
        this.direita = null;
    }
}

public class ArvoreBinaria {
    static Scanner scanner = new Scanner(System.in);
    static No[] pRaiz = new No[1];

    public static void main(String[] args) {
        int op;
        do {
            exibirMenu();
            System.out.print("\nEscolha uma opção: ");
            op = scanner.nextInt();

            switch (op) {
                case 1:
                    inserirNo();
                    break;
                case 2:
                    removerNo();
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
                    System.out.println("Encerrando o programa. Até mais!");
                    break;
                default:
                    System.out.println("Opção inválida. Tente novamente.");
                    break;
            }

            if (op != 0) {
                System.out.println("\nPressione Enter para continuar...");
                scanner.nextLine(); // Limpa o buffer do teclado
                scanner.nextLine(); // Aguarda o usuário pressionar Enter
            }

        } while (op != 0);
    }

    static void exibirMenu() {
        System.out.println("* * * MENU DE OPÇÕES * * *");
        System.out.println("1. Incluir nó");
        System.out.println("2. Remover nó");
        System.out.println("3. Buscar pré-ordem");
        System.out.println("4. Buscar em ordem");
        System.out.println("5. Buscar pós-ordem");
        System.out.println("0. Encerrar");
    }

    static void inserirNo() {
        limparTela();
        System.out.print("\nProduto: ");
        String nome = scanner.next();
        System.out.print("\nPreço do produto: ");
        float preco = scanner.nextFloat();
        Produto produto = new Produto(nome, preco);

        System.out.print("\nDigite um número (referência na árvore): ");
        int numero = scanner.nextInt();

        if (pRaiz[0] == null) {
            pRaiz[0] = new No(numero, produto);
        } else {
            inserirNoRecursivo(pRaiz[0], numero, produto);
        }

        System.out.println("Nó incluído com sucesso!");
    }

    static void inserirNoRecursivo(No no, int numero, Produto produto) {
        if (numero < no.numero) {
            if (no.esquerda == null) {
                no.esquerda = new No(numero, produto);
            } else {
                inserirNoRecursivo(no.esquerda, numero, produto);
            }
        } else if (numero > no.numero) {
            if (no.direita == null) {
                no.direita = new No(numero, produto);
            } else {
                inserirNoRecursivo(no.direita, numero, produto);
            }
        }
    }

    static void removerNo() {
        limparTela();
        System.out.print("\nDigite um número para remover: ");
        int numero = scanner.nextInt();

        removerNoRecursivo(pRaiz, numero);

        System.out.println("Nó removido com sucesso!");
    }

    static No maiorDireita(No no) {
        if (no.direita != null) {
            return maiorDireita(no.direita);
        } else {
            No aux = no;
            if (no.esquerda != null) {
                no = no.esquerda;
            } else {
                no = null;
            }
            return aux;
        }
    }

    static void removerNoRecursivo(No[] pRaiz, int numero) {
        if (pRaiz[0] != null) {
            if (numero < pRaiz[0].numero) {
                removerNoRecursivo(new No[]{pRaiz[0].esquerda}, numero);
            } else if (numero > pRaiz[0].numero) {
                removerNoRecursivo(new No[]{pRaiz[0].direita}, numero);
            } else {
                No pAux = pRaiz[0];

                if (pRaiz[0].esquerda == null && pRaiz[0].direita == null) {
                    pRaiz[0] = null;
                } else if (pRaiz[0].esquerda == null) {
                    pRaiz[0] = pRaiz[0].direita;
                    pAux.direita = null;
                } else if (pRaiz[0].direita == null) {
                    pRaiz[0] = pRaiz[0].esquerda;
                    pAux.esquerda = null;
                } else {
                    pAux = maiorDireita(pRaiz[0].esquerda);
                    pAux.esquerda = pRaiz[0].esquerda;
                    pAux.direita = pRaiz[0].direita;
                    pRaiz[0].esquerda = pRaiz[0].direita = null;
                    pRaiz[0] = pAux;
                }
            }
        }
    }

    
    
    static void buscarPreOrdem(No[] pRaiz) {
        limparTela();
        System.out.println("Busca Pré-Ordem:");
        buscarPreOrdemRecursivo(pRaiz[0]);
    }

    static void buscarPreOrdemRecursivo(No no) {
        if (no != null) {
            System.out.println("Número: " + no.numero + ", Produto: " + no.produto.nome + ", Preço: " + no.produto.preco);
            buscarPreOrdemRecursivo(no.esquerda);
            buscarPreOrdemRecursivo(no.direita);
        }
    }

    static void buscarEmOrdem(No[] pRaiz) {
        limparTela();
        System.out.println("Busca Em Ordem:");
        buscarEmOrdemRecursivo(pRaiz[0]);
    }

    static void buscarEmOrdemRecursivo(No no) {
        if (no != null) {
            buscarEmOrdemRecursivo(no.esquerda);
            System.out.println("Número: " + no.numero + ", Produto: " + no.produto.nome + ", Preço: " + no.produto.preco);
            buscarEmOrdemRecursivo(no.direita);
        }
    }

    static void buscarPosOrdem(No[] pRaiz) {
        limparTela();
        System.out.println("Busca Pós-Ordem:");
        buscarPosOrdemRecursivo(pRaiz[0]);
    }

    static void buscarPosOrdemRecursivo(No no) {
        if (no != null) {
            buscarPosOrdemRecursivo(no.esquerda);
            buscarPosOrdemRecursivo(no.direita);
            System.out.println("Número: " + no.numero + ", Produto: " + no.produto.nome + ", Preço: " + no.produto.preco);
        }
    }

    static void limparTela() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}
