#include "../includesH/enter.h"

Head *enter()
{
    FILE *myfile = fopen("File.csv", "r+");
    int n=0, i;
    Head *head=NULL;
    Node *p, *my_node=NULL;
    char buffer[MAXLEN];
    int pos;

    if (!myfile) printf("Opening file error\n");
    else
    {
        fseek(myfile,0,SEEK_END);//проверка файла на пустоту
        pos=ftell(myfile);
        if (pos == 0) printf("File is empty\n");
        else
        {
            rewind(myfile);
            while ( fgets(buffer, MAXLEN, myfile) ) n++;
            rewind(myfile);

            head=make_head();//инициализация головы
            p=fill_node(myfile);//создание первого узла списка
            add_first2(head,p);//связывание узла с головой

            p=head->last;//прибавляем узлов к последнему эл.списка
            for (i=1; i<n; i++)
            {
                my_node=fill_node(myfile);
                insert_after2(head,p,my_node);
                p=my_node;
            }
        }

        fclose(myfile);
    }
    return head;
}

int safe_scanf()
{
    int chooce;
    char str[MAXLEN];

    scanf("%s", str);
    while(sscanf(str, "%d", &chooce) != 1) {
        printf("\nIncorrect input! Try again use only numbers!\n");
        scanf("%s" , str);
    }
    return chooce;
}

float safe_scanf_f()
{
    float chooce;
    char str[MAXLEN];

    scanf("%s" , str);
    while(sscanf(str, "%f", &chooce) != 1){
        printf("\nIncorrect input! Try again use only numbers!\n");
        scanf("%s" , str);
    }
    return chooce;
}
