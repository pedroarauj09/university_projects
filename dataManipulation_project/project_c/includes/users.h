#ifndef USERS_H
#define USERS_H 

#include <glib.h> 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define U_BUFF_SIZE 2097152

typedef struct users* USERS;
typedef struct tree_users* T_USERS;


T_USERS initTreeUsers();
void destroy_tree_user(T_USERS u);
void destroyUsers(USERS u);
gint compareUsers(gconstpointer a, gconstpointer b);
T_USERS loadUserFile(T_USERS u,char* filename);
USERS initUserAux(char* id, char* name, char* friends);
USERS initUser(char* fileLine, char* fieldSeparator);
char * getId(USERS u);
char * getName(USERS u);
char * getFriends(USERS u);
char* get_user_info(USERS u);

#endif