#include"../includes/business.h"

/*STRUCTS PARA AS FUNCOES*/

struct business{
    char *business_id;        
    char *name;
    char *city;
    char *state;
    char *categories;
};

struct tree_business{  
    GTree *business; 
};


/*  FUNCOES AUXILIARES DAS QUERYS    */


/* Query 2 */

// Retorna uma string formatada para o Table
char* q2Print(char *bus){
	char info[256];
	sprintf(info, "- %s\n",bus);
	return strdup(info);
}

//Compara o nome na business
static int compareBusName(gpointer key, gpointer value, gpointer data){
  BUSINESS b = ((BUSINESS) value);
  AUX_STRUCT auxS = getElementStruct(data,0);
	char* position = getBusi_Name(b);
  if ((position[0]==getLetra(auxS))) { 
    char* bus_info = q2Print(position);
    setCount(auxS, 1);    
    addElementPrint(data, bus_info);
  }
	free(position);
	return FALSE;
}

//Retorna a table com os nomes dos business começados pela letra especificada 
TABLE getBusByLetter(T_BUSINESS tb, TABLE tab){
   	g_tree_foreach(tb->business, compareBusName , tab);
    return tab; 
}

/* Query 3 */

//Funcao compara o business_id, se achar, pega os dados dela e escreve
static int compareBusId(gpointer key, gpointer value, gpointer data){
  BUSINESS b = ((BUSINESS) value);
  AUX_STRUCT auxS = getElementStruct(data,0);
  char *position = getBusiness_Id(b);
  if (!strcmp(getBusId(auxS),position)) {
     setBusi_name(auxS,getBusi_Name(b));
     setCity(auxS,getCity(b));
     setState(auxS,getState(b));
     return TRUE;
     }
	free(position);
	return FALSE;
}


TABLE getInfoBus(T_BUSINESS tb,TABLE t){    
   	g_tree_foreach(tb->business, compareBusId , t);
    return t; 
}


//---------------------------------------------------------//
/*   query 4   */


// Faz a comparação para achar o id na arvore
static int findBus(gpointer key, gpointer value, gpointer data){
  BUSINESS b = ((BUSINESS) value);
	char *position = getBusiness_Id(b);
  if (!strcmp(getBusId(data),position)) {
    setBusi_name(data,getBusi_Name(b));
    return TRUE;
    }
	free(position);
	return FALSE;
}

// Retorna a struct contendo o nome do negocio junto com o id do mesmo
AUX_STRUCT findBusInfo(T_BUSINESS tb, char* id){
  AUX_STRUCT auxs = initStruct(); 
  setBusId(auxs,id);
  g_tree_foreach(tb->business, findBus, auxs);
  return auxs;
}

//---------------------------------------------------------//
/* Query 5 */

//Cria o formato para ser printado
char* q5Print(char* id, char* city)
{
  char info[256];
  sprintf(info,"| ID: %s | Name: %s\n", id, city);
  return strdup(info);
}

//Procura pelos IDs na determinada cidade e salva 1 elemento com apenas a ID e outro no formato de print
static int findBusCity(gpointer key, gpointer value, gpointer data){
  BUSINESS b = ((BUSINESS) value);
  
  char* bus_id = getBusiness_Id(b);
  char* city = getCity(b);
  char* tab_city = getNCidade(getElementStruct(data,0));
  
  if(!strcmp(city, tab_city))
  {
    addElementPrint(data,bus_id); 
    char* format = q5Print(bus_id, getBusi_Name(b));
    addElementPrint(data, format);
  }

  return FALSE;
  
}

//Funcao para aplicar em todos nodos da arvore
TABLE getBusWithCity(T_BUSINESS tb, TABLE tab){
  g_tree_foreach(tb->business, findBusCity, tab);
  return tab;
}

/*---------------------------------------------------------*/

/* Query 7 */

// Faz a comparação do business id na arvore, e retira seu Estado associado 
static int findState(gpointer key, gpointer value, gpointer data){
  BUSINESS b = ((BUSINESS) value);
	char *position = getBusiness_Id(b);
  if (!strcmp(getBusId(data),position)) {
    setState(data,getState(b));
    return TRUE;
    }
	free(position);
	return FALSE;
}




// Função que recolhe o Estado do negócio requerido
AUX_STRUCT getUserState(T_BUSINESS tb, AUX_STRUCT auxS){
  g_tree_foreach(tb->business, findState, auxS);
  return auxS;
}


/*---------------------------------------------------------*/

// Query 8 

/*----------------------------------------------------------*/

/* FUNÇÕES DA STRUCT */


/* Inicialização e Free da struct */

gint compareBusiness(gconstpointer a, gconstpointer b){
    char *str_a = getBusiness_Id((BUSINESS)a); // getname retrieves a copy of player name
    char *str_b =  getBusiness_Id((BUSINESS)b); // get
    int result = strcmp(str_a,str_b);
    free(str_a);
    free(str_b);
    return result;
}

T_BUSINESS initTreeBusiness(){ 
	T_BUSINESS bus = malloc(sizeof(struct tree_business));
	bus -> business = g_tree_new_full((GCompareDataFunc)compareBusiness,NULL, NULL, (GDestroyNotify) destroyBusiness);
	return bus;
}


void destroyBusiness(BUSINESS b){
	free(b->business_id);
	free(b->name);
	free(b->city);
	free(b->state);
	free(b->categories);
	free(b);
}

void destroy_tree_bus(T_BUSINESS t){
  g_tree_destroy (t->business);
	free(t);
}

//--------------------------------------------------------------//



/* Carregamento dos dados do arquivo */

T_BUSINESS loadBusinessFile(T_BUSINESS b,char* filename){
  char buffer[B_BUFF_SIZE];
  FILE* f;
  f = fopen(filename,"r");
  printf("Carregando business....\n");
  if (f==NULL){
    perror("Arquivo Business não lido corretamente\n");
		return NULL;
  }
  BUSINESS bus;
	if(fscanf(f, "%*[^\n]\n")){}; // descarta a primeira linha , *[^\n] => indica colocar todo caracter encontrado tirando o \n

  while(fgets(buffer, B_BUFF_SIZE, f)){
    bus = initBusiness(buffer, ";");
		g_tree_insert (b->business, bus, bus);    
  }

  fclose(f);
  printf("Business carregado\n");

  return b;
}


BUSINESS initBusinessAux(char *business_id,char *name,char *city,char *state,char *categories){
	BUSINESS b = malloc(sizeof(struct business));
	b->business_id=strdup(business_id);
	b->name=strdup(name);
	b->city=strdup(city);
  b->state= strdup(state);
  b->categories =strdup(categories);

	return b;
}


BUSINESS initBusiness(char* fileLine, char* fieldSeparator){
	 char *business_id= strsep(&fileLine, fieldSeparator);
   char *name= strsep(&fileLine, fieldSeparator);
   char *city= strsep(&fileLine, fieldSeparator);
   char *state= strsep(&fileLine, fieldSeparator);
   char *categories= strsep(&fileLine, fieldSeparator);
     
     
	return initBusinessAux(business_id,name,city,state,categories);
}

//---------------------------------------------------------------------//

/* Recolhe informacoes dos dados da business */

char* getBusiness_Id(BUSINESS b){
  return strdup(b->business_id);
}

char *getBusi_Name(BUSINESS b){
  return strdup(b->name);
}

char *getCity(BUSINESS b){
  return strdup(b->city);
}

char *getState(BUSINESS b){
  return strdup(b->state);
}

char *getCategories(BUSINESS b){
  return strdup(b->categories);
}
