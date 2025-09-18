#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura do item
struct Item
{
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Variaveis globais
struct Item mochila[10];
int totalItens = 0;

// Funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();

int main()
{
    int opcao;

    do
    {
        // Menu principal
        printf("\n=========================================\n");
        printf("MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("=========================================\n");
        printf("Itens da Mochila: %d/10\n\n", totalItens);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        // Limpar o buffer do teclado
        limparBuffer();
        switch (opcao)
        {
        case 1:
            inserirItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            listarItens();
            break;
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void inserirItem()
{
    if (totalItens >= 10)
    {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");

    // Inserir nome do item
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0'; // Remover quebra de linha

    // Inserir tipo do item
    printf("Tipo do item (arma, munição, cura, etc.): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    // Inserir quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();

    printf("\nItem '%s' adicionado com sucesso!\n", mochila[totalItens].nome);
    totalItens++;
    listarItens();
}

void removerItem()
{
    if (totalItens == 0)
    {
        printf("Mochila vazia! Não há itens para remover.\n");
        return;
    }

    printf("\n--- Remover Item ---\n");
    char nomeBusca[30];

    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Buscar item pelo nome para remoçao
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            // Remover item movendo os proximos itens uma posição para trás
            for (int j = i; j < totalItens - 1; j++)
            {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item '%s' removido com sucesso!\n", nomeBusca);
            listarItens();
            return;
        }
    }

    printf("Item '%s' não encontrado na mochila!\n", nomeBusca);
}

void listarItens()
{
    printf("\nITENS DA MOCHILA (%d/10)\n", totalItens);
    printf("-----------------------------------------------\n");
    printf("%-20s %-15s %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < totalItens; i++)
    {
        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    if (totalItens == 0)
    {
        printf("          Mochila vazia!\n");
    }

    printf("\nPressione Enter para continuar...");
    // Espera o usuario pressionar Enter
    getchar();
}

void buscarItem()
{
    if (totalItens == 0)
    {
        printf("Mochila vazia! Não há itens para buscar.\n");
        return;
    }

    printf("\n--- Buscar Item ---\n");
    char nomeBusca[30];

    printf("Digite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Busca sequencial
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("\nPressione Enter para continuar...");
            getchar();
            return;
        }
    }

    printf("Item '%s' não encontrado!\n", nomeBusca);
    printf("\nPressione Enter para continuar...");
    getchar();
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}