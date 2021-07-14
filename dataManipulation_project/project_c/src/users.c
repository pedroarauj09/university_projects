#include"../includes/users.h"

/*STRUCTS PARA AS FUNCOES*/
struct users{
    char *user_id;
    char *name;
    char *friends;    
};

struct tree_users{
    GTree *users;
}; 

/*---------------------------------------------------------*/

/*FUNCOES PARA USERS TREE*/

//Cria a Tree vazia
T_USERS initTreeUsers(){
	T_USERS us = malloc(sizeof(struct tree_users));
	us -> users = g_tree_new_full((GCompareDataFunc)compareUsers,NULL, NULL, (GDestroyNotify)destroyUsers);
	return us;
}

//Destroi a Tree
void destroy_tree_user(T_USERS u){
	g_tree_destroy (u->users);
	free(u);
}

//Destroi a Struct
void destroyUsers(USERS u){
	free(u->user_id);
	free(u->name);
	free(u->friends);
	free(u);
}

//Compara se 2 Users sao iguais
gint compareUsers(gconstpointer a, gconstpointer b){
	char *str_a = getId((USERS)a);
	char *str_b = getId((USERS)b);
	int result = strcmp(str_a,str_b);
	free(str_a);
	free(str_b);
	return result;
}

/*---------------------------------------------------------*/


/*FUNCAO DE ARMAZENAMENTO DAS INFORMAÇOES*/
T_USERS loadUserFile(T_USERS u,char* filename){
    char buffer[U_BUFF_SIZE];
    FILE* f = fopen(filename,"r");
    printf("Carregando user....\n");
    if (f==NULL){
      perror("Arquivo User não lido corretamente\n");
	  return NULL;
    }
	USERS us;
	if(fscanf(f, "%*[^\n]\n")){}; // descarta a primeira linha , *[^\n] => indica colocar todo caracter encontrado tirando o \n
	while(fgets(buffer, U_BUFF_SIZE, f)){
    	
	  us = initUser(buffer, ";");
      
	  g_tree_insert (u->users, us, us);
    }
    fclose(f);
	printf("Users carregado\n");

  return u;
}

/*---------------------------------------------------------*/

/*INIT DA STRUCT USER*/

//A partir dos dados argumentos armazena-os na Struct
USERS initUserAux(char* id, char* name, char* friends){
	USERS u = malloc(sizeof(struct users));
	u->user_id=strdup(id);
	u->name=strdup(name);
	u->friends=strdup(friends);
	return u;
}

//Chama a funcao acima passando-lhe os argumentos retirados 
USERS initUser(char* fileLine, char* fieldSeparator){
	char *id = strsep(&fileLine,fieldSeparator);
	char *name = strsep(&fileLine, fieldSeparator);
	char *friends = strsep(&fileLine, fieldSeparator);
	return initUserAux(id,name,friends);
}

/*---------------------------------------------------------*/

/*FUNCOES PARA DEVOLVER AS INFORMACOES CONTIDAS NA STRUCT*/

//Retrona a ID do User
char* getId(USERS u)
{
	return strdup(u->user_id);
}

//Retorna o nome do User
char* getName(USERS u)
{
	return strdup(u->name);
}

//Retorna a lista de amigos do User
char* getFriends(USERS u)
{
	return strdup(u->friends);
}

//Retorna as informacoes completas do User
char* get_user_info(USERS u){
	char info[256];
	sprintf(info, "ID: %s | Name: %s | Friends: %s",u->user_id,u->name,u->friends);
	return strdup(info);
}