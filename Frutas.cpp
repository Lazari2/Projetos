//Cadastro Simples de uma Frutaria
// Guilherme Augusto Lázari

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50
#define FILENAME "frutas.dados"

FILE *arq;

struct fruta
{
    int id;
    char nome[50];
    char sabor[30];
    float custoCaixa;
    float estoque;
    int e;
};

struct fruta lista[TAM];

int menu();
int cadastrar();
void consultarTodos();
void consultar();
void alterar();
void excluirLogica();
void listarTodas();
void ordenarPorNome(int n);
void subConsultas();

int main()
{
    return menu();
}

int menu()
{
    int opc;
    do
    {
        system("cls");
        printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
        printf("\n 1. Cadastrar");
        printf("\n 2. Consultar");
        printf("\n 3. Alterar");
        printf("\n 4. Excluir");
        printf("\n 5. Listar Todas as Frutas");
        printf("\n 6. Listar por Ordem Alfabética");
        printf("\n 9. Finalizar");
        printf("\n ");

        printf("\n Informe a opcao desejada: ");
        setbuf(stdin, NULL);
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            subConsultas();
            break;
        case 3:
            alterar();
            break;
        case 4:
            excluirLogica();
            break;
        case 5:
            listarTodas();
            break;
        case 6:
            ordenarPorNome(TAM);
            break;
        default:
            break;
        }

    } while (opc != 9);
    return opc;
}

int cadastrar()
{
    int finalizar = 0;
    struct fruta ficha;
    system("cls");
    if ((arq = fopen(FILENAME, "rb+")) == NULL)
    {
        if ((arq = fopen(FILENAME, "wb")) == NULL)
        {
            printf("\n Erro");
            return 1;
        }
    }

    do
    {
        printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
        printf("\n Informe o ID: ");
        setbuf(stdin, NULL);
        scanf("%d", &ficha.id);
        printf("\n Informe o Nome da Fruta: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", ficha.nome);
        printf("\n Informe o Sabor da Fruta: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", ficha.sabor);
        printf("\n Informe o Custo por Caixa: ");
        setbuf(stdin, NULL);
        scanf("%f", &ficha.custoCaixa);
        printf("\n Informe o Estoque: ");
        setbuf(stdin, NULL);
        scanf("%f", &ficha.estoque);
        ficha.e = 0;

        fseek(arq, 0, 2);
        fwrite(&ficha, sizeof(ficha), 1, arq);

        printf("\n Deseja incluir outra fruta? \n Pressione [9] para voltar, outra tecla para continuar...");
        scanf("%d", &finalizar);
    } while (finalizar != 9);

    fclose(arq);
    return 0;
}

void consultarTodos()
{
    int i;
    struct fruta ficha;
    system("cls");
    printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
    printf("\n Lista de Todas as Frutas");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            printf("\n ID: %d | Nome: %s | Sabor: %s | Custo por Caixa: %.2f | Estoque: %.2f", ficha.id, ficha.nome, ficha.sabor, ficha.custoCaixa, ficha.estoque);
        }
    }

    fclose(arq);
    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void consultar()
{
    struct fruta ficha;
    char nome[50];
    system("cls");
    printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
    printf("\n Consulta por Nome");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    printf("\n Informe o Nome da Fruta: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome);

    int i = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            if (strcmp(nome, ficha.nome) == 0)
            {
                printf("\n ID: %d | Nome: %s | Sabor: %s | Custo por Caixa: %.2f | Estoque: %.2f", ficha.id, ficha.nome, ficha.sabor, ficha.custoCaixa, ficha.estoque);
                i = 1;
                break;
            }
        }
        getchar();
    }

    fclose(arq);

    if (i == 0)
    {
        printf("\n Falha, busca não localizou o nome ");
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    getchar();
}

void alterar()
{
    int achou, confirmacao;
    struct fruta ficha;
    char nome[50];
    system("cls");
    printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
    printf("\n Alterar Registro por Nome");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb+")) == NULL)
    {
        printf("\n Erro");
    }

    printf("\n Informe o Nome da Fruta: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome);

    achou = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if ((ficha.e == 0) && (strcmp(nome, ficha.nome) == 0))
        {
            fseek(arq, ftell(arq) - sizeof(ficha), 0);

            printf("\n ID: [%d] ", ficha.id);
            scanf("%d", &ficha.id);

            printf("\n Nome da Fruta: [%s]: ", ficha.nome);
            setbuf(stdin, NULL);
            scanf("%[^\n]", ficha.nome);

            printf("\n Sabor da Fruta: [%s]: ", ficha.sabor);
            setbuf(stdin, NULL);
            scanf("%[^\n]", ficha.sabor);

            printf("\n Custo por Caixa: [%.2f]: ", ficha.custoCaixa);
            setbuf(stdin, NULL);
            scanf("%f", &ficha.custoCaixa);

            printf("\n Estoque: [%.2f]: ", ficha.estoque);
            setbuf(stdin, NULL);
            scanf("%f", &ficha.estoque);

            printf("\n\n Deseja alterar a ficha? \n Pressione [1] para SIM e outra tecla para cancelar ...");
            scanf("%d", &confirmacao);

            if (confirmacao == 1)
            {
                fwrite(&ficha, sizeof(ficha), 1, arq);
            }

            fseek(arq, 0, 2);
            achou = 1;
        }
    }

    fclose(arq);

    if (achou == 0)
    {
        printf("\n Falha, busca não localizou o nome ");
        printf("\n");
        printf("\n Tecle qualquer tecla para finalizar ...");
        getchar();
    }
}

void excluirLogica()
{
    int achou, confirmacao;
    struct fruta ficha;
    char nome[50];
    system("cls");
    printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
    printf("\n Exclusao Registro por Nome");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb+")) == NULL)
    {
        printf("\n Erro");
    }

    printf("\n Informe o Nome da Fruta: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome);

    achou = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            if (strcmp(nome, ficha.nome) == 0)
            {
                fseek(arq, ftell(arq) - sizeof(ficha), 0);

                printf("\n ID: %d", ficha.id);
                printf("\n Nome: %s", ficha.nome);
                printf("\n Sabor: %s", ficha.sabor);
                printf("\n Custo por Caixa: %.2f", ficha.custoCaixa);
                printf("\n Estoque: %.2f", ficha.estoque);

                printf("\n\n Deseja excluir a ficha? \n Pressione [1] para SIM e outra tecla para cancelar ...");
                scanf("%d", &confirmacao);

                if (confirmacao == 1)
                {
                    ficha.e = 1;
                    fwrite(&ficha, sizeof(ficha), 1, arq);
                }

                fseek(arq, 0, 2);
                achou = 1;
            }
        }
    }

    fclose(arq);

    if (achou == 0)
    {
        printf("\n Falha, busca não localizou o nome ");
        printf("\n");
        printf("\n Tecle qualquer tecla para finalizar ...");
        getchar();
    }
}

void listarTodas()
{
    int i;
    struct fruta ficha;
    system("cls");
    printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
    printf("\n Lista de Todas as Frutas");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    i = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            printf("\n ID: %d | Nome: %s | Sabor: %s | Custo por Caixa: %.2f | Estoque: %.2f", ficha.id, ficha.nome, ficha.sabor, ficha.custoCaixa, ficha.estoque);
            i++;
        }
    }

    fclose(arq);
    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void ordenarPorNome(int n)
{
    int i, j;
    struct fruta aux;

    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    i = 0;
    while (fread(&lista[i], sizeof(struct fruta), 1, arq))
    {
        i++;
    }

    fclose(arq);

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(lista[i].nome, lista[j].nome) > 0)
            {
                aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }

    printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
    printf("\n Lista Ordenada por Ordem Alfabética");
    printf("\n");

    for (i = 0; i < n; i++)
    {
        if (lista[i].e == 0)
        {
            printf("\n ID: %d | Nome: %s | Sabor: %s | Custo por Caixa: %.2f | Estoque: %.2f", lista[i].id, lista[i].nome, lista[i].sabor, lista[i].custoCaixa, lista[i].estoque);
        }
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}
void subConsultas()
{
    int opc = 1;
    do
    {
        system("cls");
        printf("\n Cadastro de Frutas - Desenvolvedor: Guilherme Lazari");
        printf("\n 1. Todos");
        printf("\n 2. Individual");
        printf("\n 9. Voltar");

        printf("\n Informe a opcao desejada: ");
        setbuf(stdin, NULL);
        scanf("%d", &opc);

        if (opc == 1)
            consultarTodos();
        if (opc == 2)
            consultar();

    } while (opc != 9);
}
