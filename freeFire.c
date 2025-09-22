#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura do item
struct Item
{
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // Novo campo adicionado
};

// Variaveis globais
struct Item mochila[10];
int totalItens = 0;
int ordenadoPorNome = 0; // Flag para controlar se está ordenado por nome

// Funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void organizarMochila();
void buscaBinariaComponente();
void ordenarPorNome();
void ordenarPorTipo();
void ordenarPorPrioridade();
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
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("5. Organizar Mochila (Ordenar Componentes)\n");
        printf("6. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (sair)\n");
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
        case 4:
            buscarItem();
            break;
        case 5:
            organizarMochila();
            break;
        case 6:
            buscaBinariaComponente();
            break;
        case 0:
            printf("Ativando Torre de Fuga... Saindo do sistema...\n");
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

    // Inserir prioridade
    printf("Prioridade (1-10, onde 10 é mais importante): ");
    scanf("%d", &mochila[totalItens].prioridade);
    limparBuffer();

    // Validar prioridade
    if (mochila[totalItens].prioridade < 1)
        mochila[totalItens].prioridade = 1;
    if (mochila[totalItens].prioridade > 10)
        mochila[totalItens].prioridade = 10;

    printf("\nItem '%s' adicionado com sucesso!\n", mochila[totalItens].nome);
    totalItens++;
    ordenadoPorNome = 0; // Marcar como não ordenado após inserção
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
            ordenadoPorNome = 0; // Marcar como não ordenado após remoção
            listarItens();
            return;
        }
    }

    printf("Item '%s' não encontrado na mochila!\n", nomeBusca);
}

void listarItens()
{
    printf("\nITENS DA MOCHILA (%d/10)\n", totalItens);
    printf("-------------------------------------------------\n");
    printf("%-20s %-15s %-10s %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++)
    {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
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
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\n--- Buscar Item na Mochila ---\n");
    char nomeBusca[30];

    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Busca sequencial
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Prioridade: %d\n", mochila[i].prioridade);
            printf("------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n", nomeBusca);
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void organizarMochila()
{
    if (totalItens == 0)
    {
        printf("Mochila vazia! Não há itens para organizar.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    int opcao;
    do
    {
        printf("\n--- Estrategia de Organização ---\n");
        printf("Como deseja ordernar os componentes?\n");
        printf("1. Por Nome (Ordem Alfabetica)\n");
        printf("2. Por Tipo\n");
        printf("3. Por Prioridade de Montagem\n");
        printf("0. Cancelar\n");
        printf("Ecolha o criterio: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            ordenarPorNome();
            break;
        case 2:
            ordenarPorTipo();
            break;
        case 3:
            ordenarPorPrioridade();
            break;
        case 0:
            printf("Operação cancelada.\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao < 0 || opcao > 3);
}

void ordenarPorNome()
{
    // Bubble Sort por nome
    for (int i = 0; i < totalItens - 1; i++)
    {
        for (int j = 0; j < totalItens - i - 1; j++)
        {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0)
            {
                // Troca os itens
                struct Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    ordenadoPorNome = 1; // Marcar como ordenado por nome
    printf("Itens ordenados por nome com sucesso!\n");
    listarItens();
}

void ordenarPorTipo()
{
    // Bubble Sort por tipo
    for (int i = 0; i < totalItens - 1; i++)
    {
        for (int j = 0; j < totalItens - i - 1; j++)
        {
            if (strcmp(mochila[j].tipo, mochila[j + 1].tipo) > 0)
            {
                // Troca os itens
                struct Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por tipo com sucesso!\n");
    listarItens();
}

void ordenarPorPrioridade()
{
    // Bubble Sort por prioridade (decrescente)
    for (int i = 0; i < totalItens - 1; i++)
    {
        for (int j = 0; j < totalItens - i - 1; j++)
        {
            if (mochila[j].prioridade < mochila[j + 1].prioridade)
            {
                // Troca os itens
                struct Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por prioridade com sucesso!\n");
    listarItens();
}

void buscaBinariaComponente()
{
    if (totalItens == 0)
    {
        printf("Mochila vazia! Não há itens para buscar.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    if (!ordenadoPorNome)
    {
        printf("AVISO: A mochila não está ordenada por nome.\n");
        printf("Deseja ordenar antes da busca binária? (s/n): ");
        char resposta;
        scanf("%c", &resposta);
        limparBuffer();

        if (resposta == 's' || resposta == 'S')
        {
            ordenarPorNome();
        }
        else
        {
            printf("Busca binária requer ordenação por nome. Use a busca sequencial.\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            return;
        }
    }

    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    char nomeBusca[30];

    printf("Digite o nome do componente-chave: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Busca binária
    int inicio = 0, fim = totalItens - 1, meio;
    int encontrado = -1;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);

        if (comparacao == 0)
        {
            encontrado = meio;
            break;
        }
        else if (comparacao < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    if (encontrado != -1)
    {
        printf("\n--- Componente-Chave Encontrado! ---\n");
        printf("Nome: %s\n", mochila[encontrado].nome);
        printf("Tipo: %s\n", mochila[encontrado].tipo);
        printf("Quantidade: %d\n", mochila[encontrado].quantidade);
        printf("Prioridade: %d\n", mochila[encontrado].prioridade);
        printf("------------------------------------\n");
        printf("✅ Componente crítico localizado! Torre de fuga pode ser ativada.\n");
    }
    else
    {
        printf("\nResultado: Componente-chave '%s' NAO foi encontrado.\n", nomeBusca);
        printf("Componente crítico em falta. Torre de fuga não pode ser ativada.\n");
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}