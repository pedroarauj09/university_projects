#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../includes/review.h"

/*STRUCTS PARA AS FUNCOES*/

struct review{
    char *review_id;
    char *user_id;
    char *business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    char *date;
    char *text;
};

struct tree_review{
    GTree *review;
};


/* FUNÇÕES AUXILIARES DAS QUERYS*/



/*Query 3*/

static int compareRevBusId(gpointer key, gpointer value, gpointer data){
  REVIEW r = ((REVIEW) value);
  AUX_STRUCT auxS = getElementStruct(data,0); 
  char *id = getBusId(auxS);
	char *position = getBusiness_id(r);
  if (!strcmp(id,position)){
     addNstars(auxS,getStars(r));
     setCount(auxS,1);
  }
	free(position);
	return FALSE;
}

// Faz o calculo da media de Stars de um negócio 
TABLE getReviewsById(T_REVIEW r,TABLE t){
    g_tree_foreach(r->review, compareRevBusId, t);
    AUX_STRUCT auxS = getElementStruct(t,0); 
    float starsTotal = getTableStars(auxS);
    if(starsTotal != 0){
      float mediaStars = starsTotal/getCount(auxS);
      setTableStars(auxS,mediaStars);
    }
    return t;
}

//-------------------------------------------------------///

/*Query 4*/


static int compare_u_id(gpointer key, gpointer value, gpointer data){

  REVIEW r = ((REVIEW) value);
  char *id = getUserId(getElementStruct(data,0));
  char *id_nodo = getUser_id(r);
  if (!strcmp(id,id_nodo)){        
      AUX_STRUCT auxS = initStruct();
      setBusId(auxS,getBusiness_id(r));                                                    
      addElementStruct(data,auxS);
  }
	return FALSE;
  
}

// Retorna com uma lista de negocios que o usuario fez
TABLE busReviewed(TABLE t ,T_REVIEW rvw){
  g_tree_foreach(rvw->review,compare_u_id ,t);
  return t;
  
}

//-------------------------------------------------------///


/* Query 5 */

//Salva as IDs dos negocios com mais de n estrelas no array auxiliar
static int findBusiWithStars (gpointer key, gpointer value, gpointer data){
  REVIEW r = ((REVIEW) value);
  int index = 0;
  float rstars = getStars(r);
  float tstars = getTableStars(getElementStruct(data,0));
  char* bus_id = getBusiness_id(r);

  if (rstars >= tstars)
  {
    g_ptr_array_add(getArrStructs(data), bus_id);
  }

  return FALSE;
}

//Monta o array auxiliar com as informacoes dos nodos e depoid usa como filtro com o array principal
TABLE getBusiWithStars(T_REVIEW tr, TABLE tab){
    g_tree_foreach(tr->review, findBusiWithStars, tab);
    removeElementStruct(tab, 0);
    filterPrint(tab);

    return tab;
  }


//--------------------------------------------------------//


/* Query 7  */


static int getUsers(gpointer key, gpointer value, gpointer data){
    REVIEW r = ((REVIEW) value);
    AUX_STRUCT auxS = initStruct();
    setTabUser_id(auxS,getUser_id(r));
    setBusId(auxS,getBusiness_id(r));
    addElementStruct(data, auxS);
    return FALSE;
}

// Retorna a lista com todos os usuarios que fizeram review de negocios
TABLE getAllUserByRev(T_REVIEW tr){
  TABLE tab = initTable();
  g_tree_foreach(tr->review, getUsers, tab);
  return tab;

}

//--------------------------------------------------------//

/* Query 9 */
//Funcao que confere se caracteres que veem antes e depois da palavra no texto são espaçoes ou pontuações
int check_before_after(char before, char after)
{
  int a, b;

  a = isspace(after) + ispunct(after);
  b = isspace(before) + ispunct(before);

  return a*b;
}

//Cria o formato para ser printado as informações
char* printQ9(char* id, int position)
{
  char info[256];
  sprintf(info, "| ID: %s | (%d)\n", id, position);
  return strdup(info);
}

//Procura no texto do determinado Nodo se há ocorrencia da palavra buscada. Se houver, sua informação é adicionada
static int findWordText(gpointer key, gpointer value, gpointer data){
    REVIEW r = ((REVIEW) value);
    char* text = getText(r);
    char* word = getWord(getElementStruct(data,0));

    char* result = strstr(text, word);

    int index = getCount(getElementStruct(data,0));

    if(result)
    {
      char after = result[strlen(word)];
      char before = text[strlen(text)-strlen(result)-1];

      if(check_before_after(before, after))
      {
        char* info = printQ9(getReview_Id(r), index+1);
        addElementPrint(data, info);
        setCount(getElementStruct(data, 0), 1);
      } 
    }

    free(text);

    return FALSE;
}

//Aplica a findWordText em todos os nodos da arvore
TABLE reviewWord(T_REVIEW tr, TABLE tab)
{
  g_tree_foreach(tr->review, findWordText, tab);
  return tab;
}

//--------------------------------------------------------//

/* FUNÇÕES DA STRUCT */

// FUNCOES PARA LIBERTAR OS STRCUTS 

gint compareReview(gconstpointer a,gconstpointer b){
    char *str_a = getReview_Id((REVIEW)a);
    char *str_b = getReview_Id((REVIEW)b);
    int result = strcmp(str_a,str_b);
    free(str_a);
    free(str_b);
    return result;
}

T_REVIEW initTreeReview(){
    T_REVIEW rev = malloc(sizeof(struct tree_review));
    rev->review = g_tree_new_full((GCompareDataFunc)compareReview,NULL, NULL, (GDestroyNotify) destroyReview);
    return rev;
}
void destroyReview(REVIEW r){
    free(r->review_id);
    free(r->user_id);
    free(r->business_id);
    free(r->date);
    free(r->text);
    free(r);
}


void destroy_tree_review(T_REVIEW r){
  g_tree_destroy (r->review);
  free(r);
}

//--------------------------------------------------------//

// Faz o carregamento dos dados do Arquivo

T_REVIEW loadReviewFile(T_REVIEW r,char* filename){
    char buffer[R_BUFF_SIZE];
    FILE* f = fopen(filename,"r");
    printf("Carregando review....\n");
    if (f==NULL){
      perror("Arquivo Review não lido corretamente\n");
      return NULL;
    }

    if(fscanf(f, "%*[^\n]\n")){}; // descarta a primeira linha , *[^\n] => indica colocar todo caracter encontrado tirando o \n
    
    REVIEW rev;
    while(fgets(buffer, R_BUFF_SIZE, f)){
      rev = initReview(buffer, ";");
      g_tree_insert (r->review, rev, rev);
    }

    fclose(f);
    printf("Review carregado\n");

  return r;
}


REVIEW initReviewAux(char *review_id,char *user_id,char *business_id,float stars,int useful,int funny,
                    int cool,char *date,char *text){

	REVIEW r = malloc(sizeof(struct review));
	r->review_id=strdup(review_id);
	r->user_id=strdup(user_id);
	r->business_id=strdup(business_id);
  r->stars= stars;
  r->useful = useful;
  r->funny = funny;
  r->cool = cool;
  r->date =strdup(date);
  r->text =strdup(text);


	return r;
}


REVIEW initReview(char* fileLine, char* fieldSeparator){
     
	   char *review_id= strsep(&fileLine, fieldSeparator);
     char *user_id= strsep(&fileLine, fieldSeparator);
     char *business_id= strsep(&fileLine, fieldSeparator);
     float stars= atof(strsep(&fileLine, fieldSeparator));
     int useful= atoi(strsep(&fileLine, fieldSeparator));
     int funny= atoi(strsep(&fileLine, fieldSeparator));
     int cool= atoi(strsep(&fileLine, fieldSeparator));
     char *date= strsep(&fileLine, fieldSeparator);
     char *text= strsep(&fileLine, fieldSeparator);
     
	return initReviewAux(review_id,user_id,business_id,stars,useful,funny,cool,date,text);
}

/*---------------------------------------------------------------------*/

/* FUNCOES PARA RETORNAR OS VALORES DA STRUCT*/

char* getReview_Id(REVIEW r){
  return strdup(r->review_id);
}
char *getUser_id(REVIEW r){
  return strdup(r->user_id);
}

char *getBusiness_id(REVIEW r){
  return strdup(r->business_id);
}

float getStars(REVIEW r){
  return r->stars;
}

int getUseful(REVIEW r){
  return r->useful;
}

int getFunny(REVIEW r){
  return r->funny;
}
                    
int getCool(REVIEW r){
  return r->cool;
}

char *getDate(REVIEW r){
  return strdup(r->date);
}

char *getText(REVIEW r){
  return strdup(r->text);
}
