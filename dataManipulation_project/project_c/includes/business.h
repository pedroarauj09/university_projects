#ifndef BUSINESS_H
#define BUSINESS_H 

#include <glib.h> 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "table.h"
#include "auxStructs.h"

#pragma GCC diagnostic pop

#define B_BUFF_SIZE 8192

typedef struct business* BUSINESS; 
typedef struct tree_business* T_BUSINESS;

char* q2Print(char *bus);
TABLE getBusByLetter(T_BUSINESS tb, TABLE tab);
gint compareBusiness(gconstpointer a, gconstpointer b);
T_BUSINESS initTreeBusiness();
AUX_STRUCT getUserState(T_BUSINESS tb, AUX_STRUCT auxS);
void destroyBusiness(BUSINESS b);
T_BUSINESS loadBusinessFile(T_BUSINESS b,char* filename);
BUSINESS initBusinessAux(char *business_id,char *name,char *city,char *state,char *categories);
BUSINESS initBusiness(char* fileLine, char* fieldSeparator);
char* getBusiness_Id(BUSINESS b);
char *getBusi_Name(BUSINESS b);
char *getCity(BUSINESS b);
char *getState(BUSINESS b);
char *getCategories(BUSINESS b);
void destroy_tree_bus(T_BUSINESS t);
TABLE getInfoBus(T_BUSINESS tb, TABLE t);
char* q5Print(char* id, char* city);
PtrArray getAllBus(T_BUSINESS tb, PtrArray arr);
TABLE getBusWithCity(T_BUSINESS tb, TABLE tab);
AUX_STRUCT findBusInfo(T_BUSINESS tb, char* id);

#endif