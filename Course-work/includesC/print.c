#include "../includesH/print.h"

void print(Head *head)
{
    Node *p;
    p = head->first;
    printf("|%30s |%18s |%5s| %5s|%10s|%7s|\n",
    "name","author","year", "pages", "wordcount", "rating");
    puts(TEXTBAR);
    while (p)
    {
        printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
        p->name,p->author,
        p->year, p->lists,
        p->wordcount, p->average);
        p=p->next;
    }
    puts(TEXTBAR);
}

char **split(char *str, int length, char sep)
{
    char **str_array=NULL;
    int i,j,k=0,m=0;
    int key=0,count;
    for(j=0;j<length;j++) if(str[j]==sep) m++;

    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else
                {
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
            str_array[m][j-k]='\0';
        }
        else clear_str_array(str_array,count);
     }
     return str_array;
}

void clear_str_array(char **str, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;
}

