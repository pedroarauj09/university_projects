#ifndef AUX_H
#define AUX_H 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<glib.h>
#include <gmodule.h>



typedef struct auxstruct* AUX_STRUCT; 



AUX_STRUCT initStruct();
char getLetra(AUX_STRUCT t);
void setLetra(AUX_STRUCT t, char c);
void addNstars(AUX_STRUCT t, float n);
float getTableStars(AUX_STRUCT t);
void setTableStars(AUX_STRUCT t, float s);
void setNCidade(AUX_STRUCT t, char *ncity);
void setTabBusi_id(AUX_STRUCT t, char *name);
char* getTabBusi_id(AUX_STRUCT t);
void setWord(AUX_STRUCT t, char *word);
char* getWord(AUX_STRUCT t);
void setTabUser_id(AUX_STRUCT t,char *user_id);
char *getUserId(AUX_STRUCT t);
char* getNCidade(AUX_STRUCT t );
void setBusId(AUX_STRUCT t, char *business_id);
void setBusi_name(AUX_STRUCT t,char * business_name);
char* getBusId(AUX_STRUCT t );
int getCount(AUX_STRUCT t);
void setCount(AUX_STRUCT t, int n);
void setCity(AUX_STRUCT t,char * business_cidade);
void setState(AUX_STRUCT t, char *business_state);
char *getTabState(AUX_STRUCT t);
char* getTabCity(AUX_STRUCT t);
char* getBusi_name(AUX_STRUCT t);
void freeStruct(AUX_STRUCT t);
void setCategory(AUX_STRUCT t, char *category);


#endif