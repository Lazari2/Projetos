#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "logradouros.fatec"
#define TAM 10

FILE *arq;


struct logradouro
{
    int id;
    char logradouro[60];
    char FaixaNumeros[25];
    int numbueiros;
    int e;
};

struct logradouro lista[TAM];

int menu();
void cabecalho();
void subConsultas();
void subConsultasRelatorios();
void subConsultasUtilitarios();
void consultar();
void consultarTodos();
int inserir();
void editar();
void excluirLogica();
void listarGeral();
void listarOrdemAlfabetica(int n);
void ordenarPorBueiros(int n, struct logradouro v[TAM]);
void bueiroMaior(struct logradouro arr[], int n);
void bueiroIgual(struct logradouro arr[], int n);
void bueiroMenor(struct logradouro arr[], int n);
void registrosExcluidosLogicamente();
void limparRegistrosExcluidos();
void backupRegistros();
void limparArquivosDados();

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
        cabecalho();
        printf("\n Menu Principal\n");
        printf("\n 1. Inserir");
        printf("\n 2. Consulta");
        printf("\n 3. Editar");
        printf("\n 4. Exclusao");
        printf("\n 5. Relatorios");
        printf("\n 6. Utilitarios");
        printf("\n 9. Sair");
        printf("\n ");

        printf("\n Informe a opcao desejada: ");
        setbuf(stdin, NULL);
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            inserir();
            break;
        case 2:
            subConsultas();
            break;
        case 3:
            editar();
            break;
        case 4:
            excluirLogica();
            break;
        case 5:
            subConsultasRelatorios();
            break;
        case 6:
            subConsultasUtilitarios();
            break;
        default:
            break;
        }

    } while (opc != 9);
    return opc;
}

void subConsultas()
{
    int opc = 1;
    do
    {
        system("cls");
        cabecalho();
        printf("\n2. MENU CONSULTAS");
        printf("\n 2-1 Individual");
        printf("\n 2-2 Todos");
        printf("\n 2-9 Voltar");

        printf("\n Informe a opcao desejada: ");
        setbuf(stdin, NULL);
        scanf("%d", &opc);

        if (opc == 1)
        consultar();
        if (opc == 2)
        consultarTodos();



    } while (opc != 9);
}

void cabecalho(){
    printf("````````````````````````````````````````````````````````");
    printf("\nDISCIPLINA: Linguagem de programacao - TURNO: Noite\n");
    printf("Aluno: Guilherme Augusto Lazari - ra: 0220482313013\n");
    printf("30/11/2023\n\n");
    printf("``````````````````````````````````````````````````````````");

}

void consultar()
{
    struct logradouro ficha;
    char logradouro[60];
    system("cls");
    cabecalho();
    printf("\n Consulta por Nome");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    printf("\n Informe o Nome do logradouro: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", logradouro);

    int i = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            if (strcmp(logradouro, ficha.logradouro) == 0)
            {
                printf("\n ID: %d | Logradouro: %s | Numero de faixas: %s | Numero de bueiros: %d", ficha.id, ficha.logradouro, ficha.FaixaNumeros, ficha.numbueiros);
                i = 1;
                break;
                getchar();
            }
        }
        getchar();
    }

    fclose(arq);

    if (i == 0)
    {
        printf("\n Falha, busca nao localizou o nome ");
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    getchar();
}

void consultarTodos()
{
    int i;
    struct logradouro ficha;
    system("cls");
    cabecalho();
    printf("\n Lista de Todos os Logradouros");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            printf("\n ID: %d | Logradouro: %s | Numero de Faixas: %s | Numero de Bueiros: %d", ficha.id, ficha.logradouro, ficha.FaixaNumeros, ficha.numbueiros);
        }
    }

    fclose(arq);
    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void subConsultasRelatorios()
{
    int opc = 1;
    do
    {
        system("cls");
        cabecalho();
        printf("\n5 - MENU RELATORIOS");
        printf("\n 5-1 Listagem Geral");
        printf("\n 5-2 Listagem Geral Ordenado por Ordem Alfabetica");
        printf("\n 5-3 Listagem Geral Ordenado por Numero de Bueiros");
        printf("\n 5-4 Listagem Filtrada por numero de bueiros igual a 5");
        printf("\n 5-5 Listagem Filtrada por numero de bueiros menor que 5");
        printf("\n 5-6 Listagem Filtrada por Numero de bueiros maior que 5");
        printf("\n 5-9 Voltar");

        printf("\n Informe a opcao desejada: ");
        setbuf(stdin, NULL);
        scanf("%d", &opc);

        if (opc == 1)
        listarGeral();
        if (opc == 2)
        listarOrdemAlfabetica(TAM);
        if (opc == 3)
        ordenarPorBueiros(TAM, lista);
        if (opc == 4)
        bueiroIgual(lista, TAM);
        if (opc == 5)
        bueiroMenor(lista, TAM);
        if (opc == 6)
        bueiroMaior(lista, TAM);


    } while (opc != 9);
}

void subConsultasUtilitarios()
{
    int opc = 1;
    do
    {
        system("cls");
        cabecalho();
        printf("\n6. MENU UTILITARIOS");
        printf("\n 6-1 Relatorio Registros Excluidos logicamente");
        printf("\n 6-2 Limpar Registros Excluidos");
        printf("\n 6-3 Fazer Backup de Registros");
        printf("\n 6-4 Limpar arquivos Dados");
        printf("\n 6-9 Voltar");

        printf("\n Informe a opcao desejada: ");
        setbuf(stdin, NULL);
        scanf("%d", &opc);

        if (opc == 1)
        registrosExcluidosLogicamente();
        if (opc == 2)
        limparRegistrosExcluidos();
        if (opc == 3)
        backupRegistros();
        if (opc == 4)
        limparArquivosDados();

    } while (opc != 9);
}

int inserir()
{
    int finalizar = 0;
    struct logradouro ficha;
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
        cabecalho();
        printf("\n Informe o ID: ");
        setbuf(stdin, NULL);
        scanf("%d", &ficha.id);
        printf("\n Informe o Logradouro: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", ficha.logradouro);
        printf("\n Informe Numero da faixa: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", ficha.FaixaNumeros);
        printf("\n Informe o Numero de bueiros: ");
        setbuf(stdin, NULL);
        scanf("%d", &ficha.numbueiros);
        ficha.e = 0;

        fseek(arq, 0, 2);
        fwrite(&ficha, sizeof(ficha), 1, arq);

        printf("\n Deseja incluir outro logradouro? \n Pressione [9] para voltar, outra tecla para continuar...");
        scanf("%d", &finalizar);
    } while (finalizar != 9);

    fclose(arq);
    return 0;
}

void editar()
{
    int achou, confirmacao;
    struct logradouro ficha;
    char logradouro[60];
    system("cls");
    cabecalho();
    printf("\n Alterar Registro por Logradouro");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb+")) == NULL)
    {
        printf("\n Erro");
    }

    printf("\n Informe o Logradouro: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", logradouro);

    achou = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if ((ficha.e == 0) && (strcmp(logradouro, ficha.logradouro) == 0))
        {
            fseek(arq, ftell(arq) - sizeof(ficha), 0);

            printf("\n ID: [%d] ", ficha.id);
            scanf("%d", &ficha.id);

            printf("\n Logradouro: [%s]: ", ficha.logradouro);
            setbuf(stdin, NULL);
            scanf("%[^\n]", ficha.logradouro);

            printf("\n Numero de faixas: [%s]: ", ficha.FaixaNumeros);
            setbuf(stdin, NULL);
            scanf("%[^\n]", ficha.FaixaNumeros);

            printf("\n Numero de bueiros [%.d]: ", ficha.numbueiros);
            setbuf(stdin, NULL);
            scanf("%d", &ficha.numbueiros);

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
    struct logradouro ficha;
    char logradouro[60];
    system("cls");
    cabecalho();
    printf("\n Exclusao Registro por Nome");
    printf("\n");
    if ((arq = fopen(FILENAME, "rb+")) == NULL)
    {
        printf("\n Erro");
    }

    printf("\n Informe o Logradouro ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", logradouro);

    achou = 0;
    while (fread(&ficha, sizeof(ficha), 1, arq))
    {
        if (ficha.e == 0)
        {
            if (strcmp(logradouro, ficha.logradouro) == 0)
            {
                fseek(arq, ftell(arq) - sizeof(ficha), 0);

                printf("\n ID: %d", ficha.id);
                printf("\n Logradouro: %s", ficha.logradouro);
                printf("\n Numero de faixas: %s", ficha.FaixaNumeros);
                printf("\n Numero de bueiros %d", ficha.numbueiros);

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

void listarGeral()
{
    int i;
    struct logradouro ficha;
    system("cls");
    cabecalho();
    printf("\n Lista de Todos os Logradouros: ");
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
            printf("\n ID: %d | Logradouro: %s | Numero de Faixa: %s | Numero de bueiros: %d", ficha.id, ficha.logradouro, ficha.FaixaNumeros, ficha.numbueiros);
            i++;
        }
    }

    fclose(arq);
    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void listarOrdemAlfabetica(int n)
{
    int i, j;
    struct logradouro aux;

    if ((arq = fopen(FILENAME, "rb")) == NULL)
    {
        printf("\n Erro");
    }

    i = 0;
    while (fread(&lista[i], sizeof(struct logradouro), 1, arq))
    {
        i++;
    }

    fclose(arq);

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(lista[i].logradouro, lista[j].logradouro) > 0)
            {
                aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }

    cabecalho();
    printf("\n Lista Ordenada por Ordem Alfabética");
    printf("\n");

    for (i = 0; i < n; i++)
    {
        if (lista[i].e == 0)
        {
            printf("\n ID: %d | Logradouro: %s | Numero De Faixa: %s | Numero de Bueiros %d", lista[i].id, lista[i].logradouro, lista[i].FaixaNumeros, lista[i].numbueiros);
        }
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void ordenarPorBueiros(int n, struct logradouro v[TAM]) {
    int i, j;
    struct logradouro aux;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (v[i].numbueiros > v[j].numbueiros) {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }

    printf("\n Lista dos Logradouros ordenados por numero de bueiros");
    for (i = 0; i < n; i++) {
        if (v[i].e == 0) {
            printf("\n ID: %d", v[i].id);
            printf("\n Logradouro: %s", v[i].logradouro);
            printf("\n Numero de faixas: %s", v[i].FaixaNumeros);
            printf("\n Numero de bueiros: %d", v[i].numbueiros);
            printf("\n------------------------");
        }
    }
    getchar();
    getchar();
}


void bueiroMaior(struct logradouro arr[], int n) {
    system("cls");
    cabecalho();
    printf("\n Lista de Logradouros com Numero de Bueiros Maior que 5: ");
    printf("\n");

    int i;
    for (i = 0; i < n; i++) {
        if (arr[i].e == 0 && arr[i].numbueiros > 5) {
            printf("\n ID: %d | Logradouro: %s | Numero de Faixa: %s | Numero de bueiros: %d", arr[i].id, arr[i].logradouro, arr[i].FaixaNumeros, arr[i].numbueiros);
        }
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void bueiroIgual(struct logradouro arr[], int n) {
    system("cls");
    cabecalho();
    printf("\n Lista de Logradouros com Numero de Bueiros Igual a 5: ");
    printf("\n");

    int i;
    for (i = 0; i < n; i++) {
        if (arr[i].e == 0 && arr[i].numbueiros == 5) {
            printf("\n ID: %d | Logradouro: %s | Numero de Faixa: %s | Numero de bueiros: %d", arr[i].id, arr[i].logradouro, arr[i].FaixaNumeros, arr[i].numbueiros);
        }
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void bueiroMenor(struct logradouro arr[], int n) {
    system("cls");
    cabecalho();
    printf("\n Lista de Logradouros com Numero de Bueiros Menor que 5: ");
    printf("\n");

    int i;
    for (i = 0; i < n; i++) {
        if (arr[i].e == 0 && arr[i].numbueiros < 5) {
            printf("\n ID: %d | Logradouro: %s | Numero de Faixa: %s | Numero de bueiros: %d", arr[i].id, arr[i].logradouro, arr[i].FaixaNumeros, arr[i].numbueiros);
        }
    }

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void registrosExcluidosLogicamente() {
    struct logradouro ficha;
    system("cls");
    cabecalho();
    printf("\n Lista de Registros Excluidos Logicamente: ");
    printf("\n");

    if ((arq = fopen(FILENAME, "rb")) == NULL) {
        printf("\n Erro ao abrir o arquivo.");
        return;
    }

    while (fread(&ficha, sizeof(ficha), 1, arq)) {
        if (ficha.e == 1) {
            printf("\n ID: %d | Logradouro: %s | Numero de Faixa: %s | Numero de bueiros: %d (Excluido)", ficha.id, ficha.logradouro, ficha.FaixaNumeros, ficha.numbueiros);
        }
    }

    fclose(arq);

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void limparRegistrosExcluidos() {
    struct logradouro ficha;
    FILE *tempArq;

    if ((arq = fopen(FILENAME, "rb")) == NULL) {
        printf("\n Erro ao abrir o arquivo.");
        return;
    }

    if ((tempArq = fopen("temp.fatec", "wb")) == NULL) {
        printf("\n Erro ao criar o arquivo temporário.");
        fclose(arq);
        return;
    }

    while (fread(&ficha, sizeof(ficha), 1, arq)) {
        if (ficha.e == 0) {
            fwrite(&ficha, sizeof(ficha), 1, tempArq);
        }
    }

    fclose(arq);
    fclose(tempArq);

    remove(FILENAME);
    rename("temp.fatec", FILENAME);
    printf("\n Registros excluidos logicamente foram removidos com sucesso.");

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void backupRegistros() {
    struct logradouro ficha;
    FILE *backupArq;

    if ((arq = fopen(FILENAME, "rb")) == NULL) {
        printf("\n Erro ao abrir o arquivo.");
        return;
    }

    if ((backupArq = fopen("backup.fatec", "wb")) == NULL) {
        printf("\n Erro ao criar o arquivo de backup.");
        fclose(arq);
        return;
    }

    while (fread(&ficha, sizeof(ficha), 1, arq)) {
        fwrite(&ficha, sizeof(ficha), 1, backupArq);
    }

    fclose(arq);
    fclose(backupArq);

    printf("\n Backup dos registros foi concluido com sucesso.");

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}

void limparArquivosDados() {
    FILE *limparArq;

    if ((limparArq = fopen(FILENAME, "wb")) == NULL) {
        printf("\n Erro ao limpar o arquivo de dados.");
        return;
    }

    fclose(limparArq);

    printf("\n Todos os dados do arquivo foram limpos com sucesso.");

    printf("\n Tecle qualquer tecla para finalizar ...");
    setbuf(stdin, NULL);
    getchar();
}



