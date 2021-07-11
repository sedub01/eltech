#include "../includesH/sort.h"

//----------------------------------
float YearValue(Node *str0)
{
    return str0->year;
}
//----------------------------------
float ListsValue(Node *str0)
{
    return str0->lists;
}
//-------------------------------------
float WordcountValue(Node *str0)
{
    return str0->wordcount;
}
//-------------------------------------
float RatingValue(Node *str0)
{
    return str0->average;
}
//------------------------------------



void swap(Node *tmp, Node *a) //просто меняем данные местами,не нарушая связей
{
    char *bookname, *author;
    int year, lists;
    float wordcount, average;

    year=tmp->year;
    tmp->year=a->year;
    a->year=year;

    lists=tmp->lists;
    tmp->lists=a->lists;
    a->lists=lists;

    bookname=tmp->name;
    tmp->name=a->name;
    a->name=bookname;

    author=tmp->author;
    tmp->author=a->author;
    a->author=author;

    wordcount=tmp->wordcount;
    tmp->wordcount=a->wordcount;
    a->wordcount=wordcount;

    average=tmp->average;
    tmp->average=a->average;
    a->average=average;
}

void sort_number(Head *head, float (*funcName)(Node*), int order)
{
    Node *tmp, *a;
    int i, flag=1;

    while(flag)
    {
        tmp=head->first;
        a=tmp->next;
        flag=0;
        for (i=0; i<head->cnt-1; i++)
        {
            if (order == 0)
            {
                if(funcName(tmp)>funcName(a))
                {
                    swap(tmp, a);
                    flag=1;
                }
            }
            //потому что может быть только 0 или 1
            else if(funcName(tmp)<funcName(a))
                {
                    swap(tmp, a);
                    flag=1;
                }

            tmp=tmp->next;
            a=a->next;
        }
    }
}

void sort_word(Head *head, int option, int order) //сделал под конец,сори
{
    Node *tmp, *a;
    int i, flag=1;

    while (flag)
    {
        tmp=head->first;
        a=tmp->next;
        flag=0;

        for (i=0; i<head->cnt-1; i++)
        {
            if (order == 0)
            {
                if (option==1)
                {
                    if (strcmp(tmp->name, a->name)>0)
                    {
                        swap(tmp, a);
                        flag=1;
                    }
                }
                else if (strcmp(tmp->author, a->author)>0)
                {
                    swap(tmp, a);
                    flag=1;
                }
            }
            else
            {
                if (option==1)
                {
                    if (strcmp(tmp->name, a->name)<0)
                    {
                        swap(tmp, a);
                        flag=1;
                    }
                }
                else if (strcmp(tmp->author, a->author)<0)
                {
                    swap(tmp, a);
                    flag=1;
                }
            }
            tmp=tmp->next;
            a=a->next;
        }
    }
}
