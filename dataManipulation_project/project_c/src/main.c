#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/sgr.h"

#define PATH_FILE 1024


int main(){
	if(system("clear")){};
	initProgram();
	int i = 0;
	clock_t begin = clock();
	SGR sg = init_sgr();
	while(i == 0){ // ciclo que limita o usuario digitar o path do caminho dos arquivos corretos 
		char* business_file = malloc(PATH_FILE * sizeof(char)) ; // "../../input-files/business_full.csv" |
		char *user_file = malloc(PATH_FILE * sizeof(char)) ; // "../../input-files/users_full.csv"		  | NOSSA DIRETORIA
		char *review_file = malloc(PATH_FILE * sizeof(char)) ; // "../../input-files/reviews_1M.csv"      |	
		askFilePath(business_file,user_file, review_file); 
		loadingFiles();
		
		if(!(sg = load_sgr(user_file, business_file , review_file))){
			fileError();
		}
		else{
			i++;
		}
		free(business_file);
		free(user_file);
		free(review_file);
	}
	
	TABLE tb = initTable();
	int query;
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	imprimeExecTime(time_spent);
	
	while(i == 1){ // ciclo das querys
		begin = clock();
		query = all_queries();
		switch(query)
		{
			case 1:
				printf("Já foi feita!\n");
				break;
			case 2:
				tb = businesses_started_by_letter(sg,query2Interface());
				break;
			case 3:
				tb = business_info(sg,query3Interface());
				break;
			case 4:
				tb = businesses_reviewed(sg,query4Interface());
				break;
			case 5:
				tb =businesses_with_stars_and_city(sg, query5InterfaceStars(), query5InterfaceCity());
				break;
			case 7:
				tb = international_users(sg);
				break;
			case 9:
				tb = reviews_with_word(sg, query9InterfaceTop(), query9InterfaceWord());
				break;	
			default:
				printf("Error! operator is not correct\n");

		}	
		printQuery(tb);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		imprimeExecTime(time_spent);

		printf("\nDeseja continuar? (Digite 1 para continuar e 0 para sair!)\n");
		if(scanf("%d",&i)){};

		resetTable(tb);
	}

	free_table(tb);
	free_sgr(sg);

	printExit();
	

   return 0;
}

