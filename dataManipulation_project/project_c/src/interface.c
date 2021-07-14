#include "../includes/interface.h"

// Inicialização do programa
void initProgram(){
    printf("----------------------------------------------------\n");
	printf("|        Ola, bem vindo ao nosso programa          |\n");
	printf("----------------------------------------------------\n\n");
}

// Pede ao usuario o path dos files
void askFilePath(char* business_file, char* user_file, char * review_file){
    printf("Digite o path dos arquivos que deseja ler:\n");
    printf("Caminho para o ficheiro do user: ");
    if(scanf("%s",user_file)){};
    printf("Caminho para o ficheiro do business: ");
    if(scanf("%s",business_file)){};
    printf("Caminho para o ficheiro do review: ");
    if(scanf("%s",review_file)){};
    putchar('\n');
}

// Imprime tempo de execução
void imprimeExecTime(double execT){
    printf("Tempo de execução: %.2f(s)\n", execT);
}


// Imprime titulo dizendo que está a carregar os files
void loadingFiles(){
    printf("\n\n------------------------------------\n");
	printf("        Carregando Files            \n");
	printf("------------------------------------\n");
}


// Imprime erro
void fileError(){
    printf("Arquivos lidos incorretamente, tente novamente\n");
}

// Printa a table da Query
void printQuery(TABLE tb)
{
    if(!getLengthPrint(tb)) printf("Não há! Insira os dados corretamente, por favor\n");

    else for (int i = 0; i < getLengthPrint(tb); ++i)
    {
        printf("%s", getElementPrint(tb, i)); 
    }
    putchar('\n');
}

//Faz um print na tela quando sair do programa
void printExit(){
    printf("----------------------------------------------------\n");
    printf("|                Até logo!! ;)                      |\n");
    printf("----------------------------------------------------\n");
}


/* INTERFACE DAS QUERYS */

char query2Interface(){
    char letter;
    printf("Digite sua letra(Upper case):\n");
	printf("    Exemplo: B\n");
    if(scanf(" %c",&letter)){}
    return letter;
}

char* query3Interface(){
    char id[128];
    printf("Digite o ID(Business):\n");
    printf("    Exemplo: tCbdrRPZA0oiIYSmHG3J0w\n");
	if(scanf("%s", id)){};
    return strdup(id);
}

char* query4Interface(){
    char id[128];
    printf("Digite o ID(User):\n");
    printf("    Exemplo: ak0TdVmGKo4pwqdJSTLwWw\n");
	if(scanf("%s", id)){};
    return strdup(id);
}

char* query5InterfaceCity(){
    char city[128];
    printf("Digite o nome da Cidade:\n");
    printf("    Exemplo: Orlando\n");
	if(scanf("%s", city)){};
    return strdup(city);
}

float query5InterfaceStars(){
    float stars;
    printf("Digite a quantidade de Estrelas: (0 - 5)\n");
	if(scanf("%f", &stars)){};
    return stars;
				
}

int query9InterfaceTop(){
    int top;
    printf("Digite a quantidade de IDs que deseja:\n");
	if(scanf("%d", &top)){};
    return top;				
}

char* query9InterfaceWord(){
	char word[128];
    printf("Digite a palavra procurada:\n");
	if(scanf("%s", word)){};
    return strdup(word);
}

int all_queries()
{
    int query;

    printf("\nLista de Querys disponiveis:\n");
    printf("\n1->Carrega os arquivos\n");
    printf("\n2->Procura os Business que começam com uma letra\n");
    printf("\n3->Dado 1 Business ID, devolve as informações do mesmo\n");
    printf("\n4->Dado 1 User ID, determina os negocios que fez review\n");
    printf("\n5->Dado um numero de stars, devolve os negocios com o numero maior ou igual de dada cidade\n");
    printf("\n7->Devolve a lista de utilizadores que visitaram mais de 1 Estado\n");
    printf("\n9->Fornece os n primeiros reviews com a dada palavra\n");
    printf("\nQual Query deseja fazer?\n");

    if(scanf("%d", &query)){};

    return query;
}		