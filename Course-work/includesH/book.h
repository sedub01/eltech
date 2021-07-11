#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 80
#define TEXTBAR "+-------------------------------+-------------------+-----+------+----------+-------+"

#ifdef linux  //для линукса
#define CLS system("clear")
#elif __APPLE__ //для мака
#define CLS system("clear")
#else
#define CLS system("cls") //для винды
#endif

/* definition of node */
struct LNode
{
    char *name;//название книги
    char *author;//автор
    int year;//год создания
    int lists;//кол-во страниц
    float wordcount; //кол-во слов в тысячах
    float average;//средняя оценка
    struct LNode *prev; /* link to previous node */
    struct LNode *next; /* link to next node */
};
typedef struct LNode Node; /* datatype for node */

struct LHead
{
    int cnt; /* counter of nodes */
    Node *first; /* pointer to first element */
    Node *last; /* pointer to last element */
};
typedef struct LHead Head; /* datatype for head */

