#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Tipo de dado novo para guardar os alunos */
typedef struct tipoAluno
{
    char sobrenome[20];
    char nome[20];
    unsigned long int telefone;
    unsigned int sexo : 1;
    unsigned int situacao_civil : 1;
    unsigned int empregado : 1;
} tipoAluno;

/* Tipo de dado novo para os nós da lista encadeada */
typedef struct tipoNo
{
    tipoAluno dado;
    struct tipoNo *prox;
} tipoNo;

/* Tipo de dado novo para guardar o elemento mais recente da lista */
typedef struct tipoLista
{
    tipoNo *topo;
} tipoLista;

/* Função para criar a lista */
void criaLista(tipoLista *Lista)
{
    Lista->topo = NULL;
}

/* Função para ordenar a lista alfabeticamente na ordem crescente por sobrenome */
int ordenaLista(tipoLista *Lista)
{
    tipoNo *pi = Lista->topo, *pj, *pfim = NULL;
    /* Lida com o caso de a lista estar vazia */
    if (Lista->topo == NULL || pi->prox == NULL)
    {
        return printf("Lista vazia.");
    }

    for (pi = Lista->topo; pi->prox != NULL; pi = pi->prox)
    {
        for (pj = Lista->topo; pj->prox != pfim; pj = pj->prox)
        {
            if (strcmp(pj->dado.sobrenome, pj->prox->dado.sobrenome) > 0)
            {
                tipoAluno temp = pj->dado;
                pj->dado = pj->prox->dado;
                pj->prox->dado = temp;
            }
        }
        pfim = pj;
    }
}

/* Função para inserir aluno na lista */
void insereAluno(tipoLista *Lista)
{
    tipoNo *aux;
    aux = (tipoNo *)malloc(sizeof(tipoNo)); /* Aloca espaço na memória para o novo Nó da lista */

    char sexo, situacao_civil, empregado; /* Variáveis para armazenar temporáriamente os valores */

    printf("Informe os dados do aluno:\n\n");
    /* Leitura das informações do aluno */
    printf("Nome: ");
    scanf("%s", &aux->dado.nome);

    printf("Sobrenome: ");
    scanf("%s", &aux->dado.sobrenome);

    printf("Telefone: ");
    scanf("%lu", &aux->dado.telefone);

    /* Sexo masculinho ou feminino, continuar perguntando se o valor digitado for diferente dos requisitados */
    do
    {
        fflush(stdin);
        printf("Sexo (M ou F): ");
        scanf(" %c", &sexo);
        if (sexo != 'M' && sexo != 'm' && sexo != 'F' && sexo != 'f')
        {
            printf("Valor inválido. Tente novamente.\n");
        }
    } while (sexo != 'M' && sexo != 'm' && sexo != 'F' && sexo != 'f');
    if (sexo == 'M' || sexo == 'm') /* Armazenar a resposta no campo de bit */
    {
        aux->dado.sexo = 0;
    }
    else
        aux->dado.sexo = 1;

    /* Situacao civil casado ou solteiro, continuar perguntando se o valor digitado for diferente dos requisitados */
    do
    {
        fflush(stdin);
        printf("Situação civil (C ou S): ");
        scanf(" %c", &situacao_civil);
        if (situacao_civil != 'C' && situacao_civil != 'c' && situacao_civil != 'S' && situacao_civil != 's')
        {
            printf("Valor inválido. Tente novamente.\n");
        }
        else
            break;
    } while (situacao_civil != 'C' && situacao_civil != 'c' && situacao_civil != 'S' && situacao_civil != 's');
    if (situacao_civil == 'C' || situacao_civil == 'c') /* Armazenar a resposta no campo de bit */
    {
        aux->dado.situacao_civil = 0;
    }
    else
        aux->dado.situacao_civil = 1;

    /* Situacao civil casado ou solteiro, continuar perguntando se o valor digitado for diferente dos requisitados */
    do
    {
        fflush(stdin);
        printf("Empregado (S ou N): ");
        scanf(" %c", &empregado);
        if (empregado != 'S' && empregado != 's' && empregado != 'N' && empregado != 'n')
        {
            printf("Valor inválido. Tente novamente.\n");
        }
    } while (empregado != 'S' && empregado != 's' && empregado != 'N' && empregado != 'n');
    if (empregado == 'S' || empregado == 's') /* Armazenar a resposta no campo de bit */
    {
        aux->dado.empregado = 0;
    }
    else
        aux->dado.empregado = 1;

    aux->prox = Lista->topo; /* prox(proximo) do novo aluno é igual ao topo
                                da lista(que é NULL se for o primeiro aluno inserido)             */
    Lista->topo = aux; /* topo da lista se torna o novo aluno */

    ordenaLista(Lista); /* Chamada da função ordenaLista para ordenar alfabeticamente pelo sobrenome */
}

/* Função para mostrar aluno individualmente */
void mostraAluno(tipoAluno dado)
{
    char sexo, situacao_civil, empregado;
    if (dado.sexo == 0) /* Escaneamento da variável sexo para que possa ser exibida na tela. */
    {
        sexo = 'M';
    }
    else
        sexo = 'F';

    if (dado.situacao_civil == 0) /* Escaneamento da variável situacao_civil para que possa ser exibida na tela. */
    {
        situacao_civil = 'C';
    }
    else
        situacao_civil = 'S';

    if (dado.empregado == 0) /* Escaneamento da variável empregado para que possa ser exibida na tela. */
    {
        empregado = 'S';
    }
    else
        empregado = 'N';

    printf("%s \t %s \t %lu \t %c \t      %c \t\t     %c\n\n", dado.sobrenome, dado.nome, dado.telefone, sexo, situacao_civil, empregado);
}

/* Função para mostrar a lista inteira */
int mostraLista(tipoLista *Lista)
{
    tipoNo *aux;

    aux = Lista->topo;

    if (Lista->topo == NULL) /* Cuida do caso da lista não possuir nenhum elemento. */
    {
        return (printf("Lista não possui nenhum elemento.\n"));
    }

    printf("\nSOBRENOME \t\tNOME \t TELEFONE\tSEXO \t SITUAÇÃO CIVIL \t EMPREGADO\n\n");

    while (aux) /* Enquanto aux!=NULL */
    {
        mostraAluno(aux->dado);
        aux = aux->prox;
    }
    return 0;
}

/* Função para buscar um aluno específico dentre a lista pelo sobrenome */
tipoAluno *buscaSobrenome(tipoLista *Lista, char *sobrenome)
{
    tipoNo *aux; /* Variavel tipoNo auxiliar */
    aux = Lista->topo; /* é igual ao topo da lista */

    while (aux) /* Enquanto aux for diferente de NULL */
    {
        if (strcmp(sobrenome, aux->dado.sobrenome) == 0) /* Se os sobrenomes forem iguais... */
        {
            return &(aux->dado); /* Retornar o aluno encontrado */
        }
        aux = aux->prox; /* Senão, ir para o próximo da lista */
    }
    return NULL; /* Caso não tenha encontrado nada, retornar NULL */
}

/* Função para remover um aluno específico */
int removeAluno(tipoLista *Lista, char *sobrenome)
{
    tipoNo *aux, *temp; /* Duas variáveis auxiliares tipoNo */
    if (Lista->topo) /* Se o topo da lista for diferente de NULL */
    {
        if (!strcmp(sobrenome, Lista->topo->dado.sobrenome)) /* Se os sobrenomes forem iguais.. */
        {
            temp = Lista->topo; /* Temp é igual ao topo da lista */
            Lista->topo = temp->prox; /* Topo da lista é igual ao proximo */
            free(temp); /* Liberar a memória do aluno temp que era o topo da lista */
            return 1;
        }

        aux = Lista->topo; /* Aux é igual ao topo da lista */
        while (aux->prox) /* Enquanto o próximo da lista for diferente de NULL */
        {
            if (!strcmp(sobrenome, aux->prox->dado.sobrenome)) /* Se os sobrenomes forem iguais... */
            {
                temp = aux->prox; /* Temp é igual ao proximo da lista */
                aux->prox = temp->prox; /* Próximo da lista é igual ao próximo do próximo */
                free(temp); /* Liberar a memória do aluno temp que é o próximo da lista */
                return 1;
            }
            aux = aux->prox; /* Aux é igual ao proximo da lista */
        }
    }

    ordenaLista(Lista); /* Ordena a lista alfabéticamente por sobrenome */

    return 0;
}

/* Função para armazenar a lista no disco por um arquivo txt */
int exportarLista(tipoLista *Lista)
{
    FILE *Dados; /* Ponteiro para o arquivo */
    tipoNo *aux; /* Variável tipoNo auxiliar */

    char sexo, situacao_civil, empregado; /* Variáveis para armazenamento e tradução desses dados */

    if (Lista->topo == NULL) /* Cuida do caso da lista não possuir nenhum elemento. */
    {
        return (printf("Lista não possui nenhum elemento.\n"));
    }

    /* aux é igual ao topo da lista */
    aux = Lista->topo;

    Dados = fopen("Dados.txt", "w"); /* Criar o arquivo Dados.txt com permissão de escrita */

    while (aux) /* Enquanto a lista não acabar, continuar armazenando alunos no arquivo */
    {
        if (aux->dado.sexo == 0) /* Escaneamento da variável sexo para que possa ser exibida no arquivo. */
        {
            sexo = 'M';
        }
        else
            sexo = 'F';

        if (aux->dado.situacao_civil == 0) /* Escaneamento da variável situacao_civil para que possa ser exibida no arquivo. */
        {
            situacao_civil = 'C';
        }
        else
            situacao_civil = 'S';

        if (aux->dado.empregado == 0) /* Escaneamento da variável empregado para que possa ser exibida no arquivo. */
        {
            empregado = 'S';
        }
        else
            empregado = 'N';

        /* Imprimir dados do aluno atual no arquivo txt */
        fprintf(Dados, "%s %s %lu %c %c %c\n",
                aux->dado.sobrenome, aux->dado.nome, aux->dado.telefone, sexo, situacao_civil, empregado);

        /* Ir para o próximo da lista */
        aux = aux->prox;
    }

    fclose(Dados); /* Fechar o arquivo aberto */
    return 1;
}

/* Função para importar a lista armazenada no disco pelo arquivo txt */
int importarLista(tipoLista *Lista)
{
    FILE *Dados; /* Ponteiro para o arquivo */
    tipoNo *aux; /* Variável tipoNo auxiliar */

    aux = Lista->topo; /* Aux é igual ao topo da lista */

    char sexo, situacao_civil, empregado; /* Variáveis para armazenamento e tradução desses dados */

    Dados = fopen("Dados.txt", "r"); /* Abrir o arquivo Dados.txt com permissão de leitura */

    if (Dados != NULL) /* Se o arquivo Dados existir */
    {
        while (!feof(Dados)) /* Enquanto não chegar no final do arquivo... */
        {
            aux = (tipoNo *)malloc(sizeof(tipoNo)); /* realocação de memória para cada aluno no arquivo. */

            fscanf(Dados, "%s %s %lu %c %c %c\n", aux->dado.sobrenome, aux->dado.nome,
                   &aux->dado.telefone, &sexo, &situacao_civil, &empregado); /* Leitura dos dados de cada aluno do arquivo. */

            if (sexo == 'M' || sexo == 'm') /* if para decisão de qual valor armazenar na variável. */
            {
                aux->dado.sexo = 0; /* Masculino */
            }
            else
                aux->dado.sexo = 1; /* Feminino */

            if (situacao_civil == 'C' || situacao_civil == 'c') /* if para decisão de qual valor armazenar na variável. */
            {
                aux->dado.situacao_civil = 0; /* Casado */
            }
            else
                aux->dado.situacao_civil = 1; /* Solteiro */

            if (empregado == 'S' || empregado == 's') /* if para decisão de qual valor armazenar na variável. */
            {
                aux->dado.empregado = 0; /* Sim */
            }
            else
                aux->dado.empregado = 1; /* Não */

            aux->prox = Lista->topo; /* Próximo da lista é igual ao topo da lista */
            Lista->topo = aux; /* Topo da lista é igual a aux */
        }
    }
    else /* Senão... */
    {
        return printf("Arquivo não existente.\n\n");
    }

    fclose(Dados); /* Fechar o arquivo aberto */

    ordenaLista(Lista); /* Ordenar a lista alfabeticamente pelo sobrenome */
    return 1;
}

/* Função principal */
int main()
{
    system("chcp 65001");    /* Para fazer o cmd aceitar acentos e caracteres da língua portuguesa */
    system("cls");           /* Limpando a tela */
    char sobrenome[20];      /* Variável para armazenar o sobrenome para as funções removerAluno e buscaSobrenome */
    int menu = 0, lista = 0; /* Variável para o menu e para saber se a lista foi criada */
    tipoLista l1;            /* Criação da lista */
    tipoAluno *Aluno;        /* Variável para armazenar o aluno retornado pela função buscaSobrenome */

    do /* doWhile para repetir o menu até que o usuário queira sair */
    {
        switch (menu) /* Switch...case para o menu do programa */
        {
        case 0: /* Menu principal */
            system("cls");
            printf("Bem-vindo ao seu banco de dados de colegas de classe.\n");
            printf("O que você quer fazer?\n\n\n\n\n\n\n\n\n\n");
            printf("[1] Criar lista          ");
            printf("[2] Inserir node          ");
            printf("[3] Deletar node          ");
            printf("[4] Buscar dados          ");
            printf("[5] Imprimir lista          ");
            printf("[6] Armazenar dados          ");
            printf("[7] Recuperar dados          ");
            printf("[8] Sair\n\n");

            scanf("%d", &menu); /* Leitura para ver qual menu o usuário deseja ir */
            /* Se o usuário digitar algo diferente dos números requeridos, mandar ele de volta para o menu principal */
            if (menu != 0 && menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6 && menu != 7 && menu != 8)
            {
                system("cls");
                printf("Valor para o menu inválido.\n\n");
                system("pause");
                menu = 0;
            }

            break;
        case 1: /* Criar lista */
            system("cls");
            lista = 1;
            criaLista(&l1);
            printf("Lista criada...\n\n");
            system("pause");
            menu = 0;
            break;
        case 2: /* Inserir nó */
            system("cls");

            if (lista == 0)
            {
                printf("Você não criou uma lista...\n");
                system("pause");
                menu = 0;
                break;
            }

            insereAluno(&l1);
            menu = 0;
            break;
        case 3: /* Deletar nó */
            system("cls");

            if (lista == 0) /* Cuida do caso de o usuário não ter criado uma lista */
            {
                printf("Você não criou uma lista...\n");
                system("pause");
                menu = 0;
                break;
            }

            if (l1.topo == 0) /* Cuida do caso da lista estar vazia */
            {
                printf("Sua lista não possui alunos.\n\n");
                menu = 0;
                system("pause");
                break;
            }

            if (l1.topo->prox == NULL) /* Cuida do caso de ter apenas um aluno na lista */
            {
                printf("Sua lista possui apenas um aluno.\n\n");
                mostraLista(&l1);
                printf("\nTem certeza que deseja remover este aluno? [S ou N]\n");
                char aux;
                fflush(stdin);
                scanf("%c", &aux);

                if (aux == 'S' || aux == 's') /* Lida para remover um aluno da lista. */
                {
                    removeAluno(&l1, l1.topo->dado.sobrenome);
                }
                menu = 0;
                break;
            }

            printf("Digite o sobrenome do aluno que quer remover: \n");
            scanf("%s", sobrenome); /* Lê o sobrenome do aluno que o usuário quer remover */

            Aluno = buscaSobrenome(&l1, sobrenome); /* Busca o aluno para mostrar as informações */

            if (Aluno) /* Se aluno for diferente de NULL exibir as informações */
            {
                printf("\nEncontrado na Lista:\n");
                printf("\nSOBRENOME \t\tNOME \t TELEFONE\tSEXO \t SITUACÃO CIVIL \t EMPREGADO\n\n");
                mostraAluno(*Aluno); /* Mostra as informações do aluno */
            }
            else /* Senão, o aluno não foi encontrado na lista, voltar para o menu principal */
            {
                printf("\n\nO aluno %s não foi encontrado.\n", sobrenome);
                system("pause");
                menu = 0;
                break;
            }

            printf("\nTem certeza que deseja remover este aluno? [S ou N]\n"); /* Prompt para confirmar a decisão */
            char aux;
            fflush(stdin);
            scanf("%c", &aux);

            if (aux == 'S' || aux == 's') /* Se sim, prosseguir com a remoção */
            {
                removeAluno(&l1, sobrenome);
            }

            menu = 0;
            break;
        case 4: /* Buscar sobrenome */
            system("cls");

            if (lista == 0) /* Cuida do caso de o usuário não ter criado uma lista */
            {
                printf("Você não criou uma lista...\n");
                system("pause");
                menu = 0;
                break;
            }

            if (l1.topo == 0) /* Cuida do caso da lista estar vazia */
            {
                printf("Sua lista não possui alunos.\n\n");
                menu = 0;
                system("pause");
                break;
            }

            if (l1.topo->prox == NULL) /* Cuida do caso de ter apenas um aluno na lista */
            {
                printf("Sua lista possui apenas um aluno.\n\n");
                mostraLista(&l1);
                menu = 0;
                system("pause");
                break;
            }

            printf("Digite o sobrenome do aluno que quer achar: \n");
            scanf("%s", sobrenome); /* Lê o sobrenome do aluno que o usuário quer ver */

            Aluno = buscaSobrenome(&l1, sobrenome); /* Salva o aluno achado em uma variável tipoAluno */

            if (Aluno) /* Se o aluno for diferente de NULL */
            {
                printf("\nEncontrado na Lista:\n");
                printf("\nSOBRENOME \t\tNOME \t TELEFONE\tSEXO \t SITUAÇÃO CIVIL \t EMPREGADO\n\n");
                mostraAluno(*Aluno);
            }
            else /* Senão... */
            {
                printf("\n\nO aluno %s não foi encontrado.\n", sobrenome);
            }
            menu = 0;
            system("pause");
            break;
        case 5: /* Imprimir lista */
            system("cls");

            if (lista == 0) /* Cuida do caso de o usuário não ter criado uma lista */
            {
                printf("Voce não criou uma lista...\n");
                system("pause");
                menu = 0;
                break;
            }

            printf("Elementos da lista: \n\n");
            mostraLista(&l1); /* Chamada da função para imprimir a lista inteira */
            system("pause");
            menu = 0;
            break;
        case 6: /* Exportar */
            system("cls");
            if (lista == 0) /* Cuida do caso de o usuário não ter criado uma lista */
            {
                printf("Voce não criou uma lista...\n");
                system("pause");
                menu = 0;
                break;
            }

            if (l1.topo == NULL) /* Cuida do caso da lista estar vazia */
            {
                printf("A lista não tem nada para exportar.\n\n");
            }
            else /* Se não estiver vazia, exportar para txt */
            {
                exportarLista(&l1);
            }

            system("pause");
            menu = 0;
            break;
        case 7: /* Importar */
            system("cls");
            if (lista == 0) /* Cuida do caso de o usuário não ter criado uma lista */
            {
                printf("Voce não criou uma lista...\n");
                system("pause");
                menu = 0;
                break;
            }
            importarLista(&l1); /* Importar lista do arquivo txt */
            if (l1.topo != NULL) /* Se a lista não estiver vazia, imprimir mensagem */
            {
                printf("Lista importada com sucesso.\n\n");
            }

            system("pause");
            menu = 0;
            break;
        case 8: /* Sair do programa */
            system("cls");
            break;
        default:
            break;
        }
    } while (menu != 8);

    system("cls");
    printf("\nPrograma encerrado.\n\n");

    return 0;
}
