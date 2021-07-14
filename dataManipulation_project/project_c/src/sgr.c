#include"../includes/sgr.h"

struct sgr{
    T_BUSINESS tb;
    T_REVIEW tr;
    T_USERS tu;
};

/*------------------------------------------------------------*/

/*          INIT AND FREE DA STRUCT SGR                 */

// inicializa a struct sgr
SGR init_sgr(){
    SGR sgr = malloc(sizeof(struct sgr));
    sgr->tb = initTreeBusiness();
    sgr->tu = initTreeUsers();
    sgr->tr = initTreeReview();
 
    return sgr;
}

// faz o free da struct sgr
void free_sgr(SGR sgr){
    destroy_tree_bus (sgr->tb);
    destroy_tree_user(sgr->tu);
    destroy_tree_review(sgr->tr);
    free(sgr);
}

/*------------------------------------------------------------*/


/* query 1 */
SGR load_sgr(char *users, char *businesses, char *reviews){
    SGR s = init_sgr();
    if(!(s->tr = loadReviewFile(s->tr, reviews))) return NULL;
    if(!(s->tb = loadBusinessFile(s->tb, businesses))) return NULL;
    if(!(s->tu = loadUserFile(s->tu, users)))return NULL;
    printf("Query 1 feita!\n");

    return s;
}

/* query 2 */
/* Determinar a lista de nomes de negócios e o número total de negócios cujo nome inicia
 por uma dada letra. Note que a procura não deverá ser case sensitive*/

// Faz o formato do  numero total de negocios
char* q2FinalPrint(AUX_STRUCT a){
	
    char info[256];
	sprintf(info, "Número total de negócios:  | %d | \n", getCount(a));
	return strdup(info);
    
}

// Função principal
TABLE businesses_started_by_letter(SGR sgr, char letter){
    TABLE t = initTable();
    AUX_STRUCT aStr = initStruct();
    setLetra(aStr,letter);
    addElementStruct(t,aStr);
    t = getBusByLetter(sgr->tb,t);
    char*info = q2FinalPrint(getElementStruct(t,0));
    addElementPrint(t,info);
    return t; 
}

/* query 3 */
/*
Dado um id de negócio,determinar a sua 
informação:nome,cidade,estado,stars,e número total reviews
*/

// Faz o formato da Table a ser imprimida
char* q3Print(AUX_STRUCT t){
  char info[256];
  sprintf(info, "ID: %s | Name: %s | City: %s | Estado: %s | Stars: %f | Numero total de Reviews: %d\n",getTabBusi_id(t),getBusi_name(t), 
                                                                           getTabCity(t), getTabState(t),getTableStars(t),getCount(t));
  return strdup(info);
}


// Função principal
TABLE business_info(SGR sgr, char *business_id){
    TABLE t = initTable();
    AUX_STRUCT aStr = initStruct();
    setBusId(aStr,business_id);
    addElementStruct(t,aStr);
    t = getInfoBus(sgr->tb,t);
    t = getReviewsById(sgr->tr,t);
    char* info = q3Print(getElementStruct(t,0));
    addElementPrint(t,info);
    return t;  
  
}

/* query 4 */
/*
Dado um id de utilizador,determinar a lista de negócios os quais fez review.
A informação associada a cada negócio deve ser o id e o nome.
*/


// Faz o formato do id do negocio e nome do mesmo
char *q4print(AUX_STRUCT aux){
  char info[256];
  sprintf(info, "Id Business: %s | Name Businesses: %s\n",getBusId(aux),getBusi_name(aux));
  return strdup(info);
}

// Função principal
TABLE businesses_reviewed(SGR sgr, char *user_id){
    TABLE t = initTable();
    AUX_STRUCT ts = initStruct();
    setTabUser_id(ts,user_id);
    addElementStruct(t,ts);
    t = busReviewed(t,sgr->tr);
    for(int i = 1; i < getLengthStructs(t);i++){
        AUX_STRUCT as = getElementStruct(t,i);
        char *id = getBusId(as);
        as = findBusInfo(sgr->tb,id);
        char *info = q4print(as);
        addElementPrint(t,info);
    }
    
    return t;
    
}


/* query 5 */
/*
Dado um número n de stars e uma cidade,determinar a lista de negócios os quais
com n ou mais stars na dada cidade. A informação associada
a cada negócio deve ser o seu id e nome.
*/
TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city){
   TABLE tab = initTable();
   AUX_STRUCT ts = initStruct();
   setTableStars(ts, stars);
   setNCidade(ts, city);
   addElementStruct(tab,ts);
   tab = getBusWithCity(sgr->tb, tab);
   tab = getBusiWithStars(sgr->tr,tab);
   
   return tab;

}


/* query 6 */
/*
Dado um número inteiro n,determinar a lista dos top n negócios(tendo em conta o número médio de stars)em cada cidade.
A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.
 */

/* 
    
    **RACIOCÍNIO:
    
    *Objetivo: top n stars dos business de cada cidade

    *Passos: 
        -> 1: Fazer uma lista de business id e nome para cada cidade.
            - COMO FAZER? 
                # sugestão eficiente mas mais difícil: criar uma hashTable na leitura do arquivo business, e tornar a cidade como key, e como valor associado uma lista de business_id 
                # sugestão ineficiente mas mais fácil: Após a arvore Bus feita, percorrer ela pegando todos os estados e colocando em uma lista, depois para cada estado percorrer novamente coletando os bus_ids

        -> 2: Coletar a media de Stars de cada negocio no review. 
            - COMO FAZER?
                # Coletar os business_ids , calcular media stars, eliminar bus_ids repetidos.

        -> 3: Associar os bus_ids do review com os do Business , e depois selecionar os top n por estado      
*/



// FUNÇÃO PRINCIPAL
TABLE top_businesses_by_city(SGR sgr, int top){}
    
//--------------------------------------------------------------------------------------------------------
    
/* query 7 */
/*
Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado mais de um estado,
i.e.que tenham feito reviews em negócios de diferentes estados. */

/*
        **RACIOCÍNIO:

        *Objetivo: Listar os utilizadores e o numero total deles que tenham visitado mais de um estado  

        *Passos:
            1) Ir no review, dar uma lista ordenada pelo id do user , associado tambem ao seu business_id
            2) Fazer a filtragem daqueles que tenham visitado mais de um estado, e colocar um contador para cada um achado

*/


// Função auxiliar de comparação(pelo user_id) para o sort 
 static gint sortBusIds(gconstpointer a, gconstpointer b)
{  
  AUX_STRUCT a1 = *(AUX_STRUCT*)a;
  AUX_STRUCT a2 = *(AUX_STRUCT*)b;

  return g_strcmp0(getUserId(a1),getUserId(a2));

}

// Faz o formato do numero total de usuarios
char* finalQ7Print(int nUsers){
    char info[256];
	sprintf(info, "\nNUMERO TOTAL DE USUARIOS QUE VISITARAM + DE 1 ESTADO: %d\n",nUsers);
	return strdup(info);
}

// Faz o formato dos user_id
char* listUsersPrint(char*user){
    char info[256];
	sprintf(info, "%s\n",user);
	return strdup(info);
}

// Inicializa o formato a ser imprimido
char* initQ7Print(){
    char info[256];
	sprintf(info, "USUARIOS QUE VISITARAM MAIS DE UM ESTADO:\n\n");
	return strdup(info);
}


// Função principal
TABLE international_users(SGR sgr){
    TABLE t = getAllUserByRev(sgr->tr); // pega todos os users ids e bus_id associado (está no módulo review.c)
    PtrArray pA = getArrStructs(t);
    g_ptr_array_sort(pA, sortBusIds); // coloca os user_ids repetidos juntos
    int countAll = 0; // contador para quantos usuarios visitaram estados diferentes
    int countAux; // contador para estados diferentes
    int j;
    char* init = initQ7Print();
    addElementPrint(t,init);
    for(int i = 0; i < getLengthStructs(t)-1;i++){
        AUX_STRUCT a1 = getElementStruct(t, i);
        AUX_STRUCT a2 = getElementStruct(t, i+1);
        
        a1 = getUserState(sgr->tb, a1); // retorna o Estado relacionado ao negocio que o usuario visitou( está no módulo business.c)
        countAux=0;
        char *user1 = getUserId(a1);
        char *user2 = getUserId(a2);
        for(j=i+1; (!strcmp(user1,user2)) && j < getLengthStructs(t);){ // compara os estados 
            
            if(countAux>0);
            else{
                a2 = getUserState(sgr->tb, a2);
                if((strcmp(getTabState(a1),getTabState(a2))) != 0){
    
                    countAux++;
                    
                }
            }
            removeElementStruct(t, j);
            a2 = getElementStruct(t,j);
            user2 = getUserId(a2);
        }
        if (countAux == 0) removeElementStruct(t, j); 
        else{
            countAll++;
            char *info = listUsersPrint(user1);
            addElementPrint(t,info);
        }
    }
    char *info = finalQ7Print(countAll);
    addElementPrint(t,info);
    return t;
}
    




/* query 8 */
/*
Dado um número inteiro n e uma categoria,determinar a lista dos top n negócios(tendo em conta o número médio de stars)
que pertencem a uma determinada categoria.A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas
*/
TABLE top_businesses_with_category(SGR sgr, int top, char *category){
    /*
        **RACIOCÍNIO:

        *Objetivo: dado uma categoria peagar os top n negocios 
    */

      //  *Passos:
      //      1) calcular a media de stars de cada bus associado a categoria e ao seu nome. 
      //      2) Ir no business e filtrar os ids da categoria especificada.
      //      3) Fazer o match dos busIds da categoria com os do review, e associar as stars



}

/* query 9 
Dada uma palavra, determinar a lista de ids de reviews que a referem no campo text. 
Note que deverá ter em conta os vários possíveis símbolos de pontuação para
delimitar cada palavra que aparece no texto.*/

TABLE reviews_with_word(SGR sgr, int top, char *word){
    TABLE tab = initTable();
    AUX_STRUCT ts = initStruct();
    setWord(ts, word);
    addElementStruct(tab, ts);
    tab = reviewWord(sgr->tr, tab);
    filterQ9(tab,top);
    
    return tab;
}