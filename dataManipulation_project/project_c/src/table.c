#include "../includes/table.h"

struct table{
	PtrArray arrStructs; // array of structs
	PtrArray print; // array do formato string 
};


// Inicializa a TABLE
TABLE initTable(){
     TABLE t = malloc(sizeof(struct table));
	 t->arrStructs = g_ptr_array_new();
	 t->print = g_ptr_array_new();
	 return t;
}

// Renicia a table, free ^ init
TABLE resetTable(TABLE tb)
{
	g_ptr_array_free(tb->arrStructs,TRUE);
	g_ptr_array_free(tb->print,TRUE);
	tb->arrStructs = g_ptr_array_new();
	tb->print = g_ptr_array_new(); 

	return tb; 
}

// Liberta o espaço ocupado pela Table
void free_table(TABLE tb){

	g_ptr_array_free(tb->arrStructs,TRUE);
	g_ptr_array_free(tb->print,TRUE);          
	free(tb);
}

// Retorna o Array de Structs da table
PtrArray getArrStructs(TABLE t){
	return t->arrStructs;
}

// Retorna o tamanho de qualquer PtrArray
int getLengthPtr( PtrArray pt){
	return pt->len;
}

// Retorna o tamanho do array de structs
int getLengthStructs(TABLE t){
	return t->arrStructs->len;
}

// Retorna o tamanho do array de Print
int getLengthPrint(TABLE t){
	return t->print->len;
}

// Retorna o elemento index do array de structs
AUX_STRUCT getElementStruct(TABLE t, int index){
	return  g_ptr_array_index(t->arrStructs,index);
}

// Retorna o elemento index do array de print
char* getElementPrint(TABLE t, int index){
	return  (char*) g_ptr_array_index(t->print,index);
}

// Adiciona uma struct no fim do array
void addElementStruct(TABLE t, AUX_STRUCT s){
    g_ptr_array_add(t->arrStructs, s);
}

// Adiciona uma string no array
void addElementPrint(TABLE t, char* s){
    g_ptr_array_add(t->print, s);

}


// Remove a struct index do array de structs 
void removeElementStruct(TABLE t, int index){
    g_ptr_array_remove_index (t->arrStructs, index);
}

// ------------------------------------------------------------------------

/* QUERY FUNCTIONS */	

static gint sort_filelist (gconstpointer a, gconstpointer b)
{
  const char *entry1 = *((char **) a);
  const char *entry2 = *((char **) b);

  return g_strcmp0(entry1, entry2);
}

void sortPrintArr(TABLE t){
	g_ptr_array_sort(t->print, sort_filelist);
}

void removePrintArr(TABLE t, int index){
	g_ptr_array_remove_index (t->print, index);
}

static int element_compare(gconstpointer a, gconstpointer b)
{
	char* new_a = ((char*) a);
	char* new_b = ((char*) b);
	return strcmp(new_a, new_b);
}

int findAuxArray(TABLE t, char* element)
{
	int i;
	return g_ptr_array_find_with_equal_func (t->arrStructs,element,element_compare,&i);
}

//Filtro para Query 5
void filterPrint(TABLE t) 
{
	int i = 0; 
	char* current;

	while(i<getLengthPrint(t)) 
	{
		current = getElementPrint(t,i);

		if(findAuxArray(t, current))
		{
			removePrintArr(t,i);
			i++;
		}
		else
		{
			removePrintArr(t,i);
			removePrintArr(t,i);
		}
	}
	
}



void filterQ9(TABLE t, int top)
{
	int i = top;
	while (i < getLengthPrint(t)) removePrintArr(t,i);
}