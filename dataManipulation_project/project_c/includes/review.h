#ifndef REVIEW_H
#define REVIEW_H 

#include <glib.h>
#include <ctype.h>
#include "table.h"


#define R_BUFF_SIZE 32768

typedef struct review* REVIEW; 
typedef struct tree_review* T_REVIEW;

TABLE busReviewed(TABLE t ,T_REVIEW rvw);
gint compareReview(gconstpointer a,gconstpointer b);
T_REVIEW initTreeReview();
T_REVIEW loadReviewFile(T_REVIEW r,char* filename);
REVIEW initReviewAux(char *review_id,char *user_id,char *business_id,float stars,int useful,int funny,
                    int cool,char *date,char *text); 
REVIEW initReview(char* fileLine, char* fieldSeparator);
char* q3Print(AUX_STRUCT t);
TABLE getReviewsById(T_REVIEW r, TABLE t);
char* q5AuxPrint(char* id, float stars);
TABLE getBusiWithStars(T_REVIEW tr, TABLE tab);
char* getReview_Id(REVIEW r);
char *getUser_id(REVIEW r);
char *getBusiness_id(REVIEW r);
float getStars(REVIEW r);
int getUseful(REVIEW r);
int getFunny(REVIEW r);
int getCool(REVIEW r);
char *getDate(REVIEW r);
char *getText(REVIEW r);
void destroyReview(REVIEW r);
void destroy_tree_review(T_REVIEW r);
TABLE getAllUserByRev(T_REVIEW tr);
PtrArray getAllRevBusIds(T_REVIEW tr, PtrArray arr);
int check_before_after(char before, char after);
char* printQ9(char* id, int position);
TABLE reviewWord(T_REVIEW tr, TABLE tab);


#endif