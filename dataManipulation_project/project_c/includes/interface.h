#ifndef INTERFACE_H
#define INTERFACE_H 

#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void initProgram();
void askFilePath(char* business_file, char* user_file, char * review_file);
void printQuery(TABLE tb);
void imprimeExecTime(double execT);
void loadingFiles();
void printExit();
void fileError();
char query2Interface();
char* query3Interface();
char* query4Interface();
float query5InterfaceStars();
char* query5InterfaceCity();
int query9InterfaceTop();
char* query9InterfaceWord();
int all_queries();

#endif