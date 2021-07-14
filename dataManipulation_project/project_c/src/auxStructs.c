#include "../includes/auxStructs.h"

//Struct auxiliar para transportar os argumentos
struct auxstruct{
	char p_letra;    //Salvar a primeira letra (Query 2)
	char *id_bus;    //Salvar o business_id (Query 3)
	float stars;     //Media stars (Query 3, 5)
	char *id_users;  //Salvar id do usuario (Query 4)
	char *name;      
	char *ncidade;   //Salvar nome da cidade (Query 5)
	int count;
	char *busi_name;  //Salvar o nome do negocio (Query 4) 
	char *state;	
	char* category;
	char* word;     //Salvar a palavra especifica (Query 9)
};

//Inicializador da Struct
AUX_STRUCT initStruct(){
    AUX_STRUCT aStr = malloc(sizeof(struct auxstruct));
    aStr->stars = 0;
    aStr->count = 0;
	aStr->id_bus = NULL;
	aStr->id_users = NULL;
	aStr->name = NULL;
	aStr->ncidade = NULL;
	aStr->busi_name = NULL;
	aStr->state = NULL;
	aStr->word = NULL;

	return aStr;
}

//Liberta a struct e seus elementos
void freeStruct(AUX_STRUCT aStr){
	free(aStr->id_bus);
	free(aStr->id_users);
	free(aStr->name);
	free(aStr->ncidade);
	free(aStr->busi_name);
	free(aStr->state);
	free(aStr->word);
	free(aStr);

}
 
/*-----------------------------------*/

//Funções para devolver e alterar o valor das determinadas variaveis

char getLetra(AUX_STRUCT t){
	return t->p_letra;
}

void setLetra(AUX_STRUCT t, char c){
	t->p_letra = c;
}


void addNstars(AUX_STRUCT t, float n){
	t->stars += n;
}

float getTableStars(AUX_STRUCT t){
	return t->stars;
}

void setTableStars(AUX_STRUCT t, float s){
	t->stars = s;
}

void setNCidade(AUX_STRUCT t, char *ncity){
	t->ncidade = strdup(ncity);
}

void setTabBusi_id(AUX_STRUCT t, char *name){
	t->id_bus = strdup(name);
}

char* getTabBusi_id(AUX_STRUCT t)
{
	return strdup(t->id_bus);
}

void setWord(AUX_STRUCT t, char *word){
	t->word = strdup(word);
}

char* getWord(AUX_STRUCT t)
{
	return strdup(t->word);
}

void setTabUser_id(AUX_STRUCT t,char *user_id){
	t->id_users = strdup(user_id);
}

char *getUserId(AUX_STRUCT t){
	return strdup(t->id_users);
}

char* getNCidade(AUX_STRUCT t ){
	return strdup(t->ncidade);
}

void setBusId(AUX_STRUCT t, char *business_id){
	t->id_bus = strdup(business_id);
}

char* getBusId(AUX_STRUCT t){
	return strdup(t->id_bus);
}

int getCount(AUX_STRUCT t){
	return t->count;
}

void setCount(AUX_STRUCT t, int n){
	t->count += n;
}

void setBusi_name(AUX_STRUCT t,char * business_name){
	t->busi_name = strdup(business_name);
}

char* getBusi_name(AUX_STRUCT t){
	return strdup(t->busi_name);
}

void setCity(AUX_STRUCT t,char * business_cidade){
	t->ncidade = strdup(business_cidade);
}

char* getTabCity(AUX_STRUCT t){
	return strdup(t->ncidade);
}

void setState(AUX_STRUCT t, char *business_state){
	t->state = strdup(business_state);
}

char *getTabState(AUX_STRUCT t){
	return strdup(t->state);
}

void setCategory(AUX_STRUCT t, char *category){
	t->category = strdup(category);
}