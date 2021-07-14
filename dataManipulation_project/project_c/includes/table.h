#ifndef TABLE_H
#define TABLE_H 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<glib.h>
#include <gmodule.h> 
#include "auxStructs.h" 

typedef struct table* TABLE; 
typedef GPtrArray *PtrArray;

#define TABLE_SIZE 1024

TABLE initTable();
int getLengthPtr( PtrArray pt);
TABLE resetTable(TABLE tb);
void free_table(TABLE tb);
PtrArray getArrStructs(TABLE t);
int getLengthStructs(TABLE t);
int getLengthPrint(TABLE t);
AUX_STRUCT getElementStruct(TABLE t, int index);
void removeElementStruct(TABLE t, int index);
char* getElementPrint(TABLE t, int index);
void addElementStruct(TABLE t, AUX_STRUCT s);
void addElementPrint(TABLE t, char* s);
void sortPrintArr(TABLE t);
void removePrintArr(TABLE t, int index);
int findAuxArray(TABLE t, char* element);
void filterPrint(TABLE t); 
void filterDupStars(PtrArray arrBusRev);
void filterQ9(TABLE t, int top);

#endif