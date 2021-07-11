#include "../includesH/print.h"
#include "../includesH/enter.h"
#include "../includesH/nodes.h"

Head *make_head() /* head initialization */
{
    Head *ph=NULL;

    ph=malloc(sizeof(Head));
    if(ph)
    {
        ph->cnt=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}

Node *create_node2(char *name,char *author, int year, int lists, float wordcount,float average)
{
    Node *temp=NULL;
    char *bookname=NULL;
    char *authorname=NULL;

    temp=malloc(sizeof(Node));
    bookname=(char*)malloc(MAXLEN*sizeof(char));
    authorname=(char*)malloc(MAXLEN*sizeof(char));
    if(temp&&bookname&&authorname)
    {
        strcpy(bookname,name);
        strcpy(authorname,author);
        temp->name = bookname;
        temp->author = authorname;
        temp->year = year;
        temp->lists = lists;
        temp->wordcount = wordcount;
        temp->average = average;

        temp->prev=NULL;
        temp->next=NULL;
    }
    return temp;
}

void add_first2(Head *my_head, Node *new_node)
{
    my_head->first = new_node;
    my_head->last = new_node;
    my_head->cnt++;
}

void insert_after2(Head *my_head,Node *current_node, Node *new_node) //ãîëîâà, àäðåñ äîáàâëÿåìîãî ýëåìåíòà, àäðåñ òîãî ýëåìåíòà, ïîñëå êîòîðîãî áóäåì äîáàâëÿòü
{
    Node *q=NULL; //êàê ýëåìåíò ñïèñêà

    if(my_head&&new_node&&current_node)
    {
        if (current_node == my_head->last)//êîãäà äîá. â êîíåö ñïèñêà //
        {
            current_node->next=new_node; //íîâûé ýë.ñòàíîâèòñÿ ñëåä. çà òåêóùèì
            new_node->prev=current_node; //äëÿ íîâ.ýë òåê. ñòàíîâèòñÿ ïðåä.
            //new_node->next = my_head->first;
            //my_head->first->prev=new_node;
            new_node->next=NULL;
            my_head->last=new_node; //íîâûé ýë ñòàíîâèòñÿ ïîñëåäíèì
        }
        else
        {
            q=current_node->next; //çàïîìèíàåì àäðåñ ýë, êîò ÿâë. ñëåäóþùèì çà òåê. äî âñòàâêè
            new_node->next=q; //äëÿ íîâîãî ýë. ñëåä ýë ñòàíîâèòñÿ òåê.
            new_node->prev=current_node;//äëÿ íîâîãî ýë. ïðåä. ñòàí. òåê.
            q->prev=new_node; //íóæíî ïåðåíàçíà÷èòü ñâÿçè
            //íîâûé ýë ñòàí ïðåä,
            current_node->next=new_node; //è îí æå ñòàí.ñëåä äëÿ òåê.

        }
        my_head->cnt++;
    }
}

Node *fill_node(FILE *myfile)//íàïîëíåíèå óçëà èíôîðìàöèåé
{
    char buffer[MAXLEN];
    char **buf_array=NULL;
    int slen;
    Node *my_node = NULL;

    fgets(buffer,MAXLEN,myfile);
    slen=strlen(buffer);
    buffer[slen-1]='\0';
    buf_array=split(buffer, slen, ';');


    my_node=create_node2(buf_array[0],
    buf_array[1], atoi(buf_array[2]),
    atoi(buf_array[3]), atof(buf_array[4]),
    atof(buf_array[5]));

    clear_str_array(buf_array,6);

    return my_node;
}

void free_list(Head *head) {
    Node *tmp = head->first;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp->name);
        tmp->name=NULL;
        free(tmp->author);
        tmp->author=NULL;
        free(tmp);
        tmp = NULL;
        tmp = next;
    }
    free(head);
    head = NULL;
}

int add_node(Head *head)
{
    Node *temp_node = NULL;
    Node *temp = NULL;
    int index, i=1;

    printf("Press [0] to return to main menu\n");
    printf("Enter the position of new book: ");
    index = safe_scanf();
    CLS;
    if (index)
    {
        temp_node=malloc(sizeof(Node));
        temp_node->name=(char*)malloc(MAXLEN*sizeof(char));
        temp_node->author=(char*)malloc(MAXLEN*sizeof(char));
        printf("Enter the book: ");
        getchar();
        fgets(temp_node->name, MAXLEN, stdin);
        temp_node->name[strlen(temp_node->name)-1]='\0';
        printf("Enter the author of this book: ");
        fgets(temp_node->author, MAXLEN, stdin);
        temp_node->author[strlen(temp_node->author)-1]='\0';
        printf("Enter the year of publishing: ");
        temp_node->year=safe_scanf();
        printf("Enter the number of pages: ");
        temp_node->lists=safe_scanf();
        printf("Enter the number of words: ");
        temp_node->wordcount=safe_scanf_f();
        printf("Enter rating of this book: ");
        temp_node->average=safe_scanf_f();

        temp=head->first;
        if (index>head->cnt) index = head->cnt+1;
        if (index<1) index = 1;
        if (index!=1)
        {//äîáàâëåíèå íà âûáðàííóþ ïîçèöèþ
            while(i < index-1 && temp != head->last){
            temp = temp -> next;
            i++;
            }
            insert_after2(head, temp, temp_node);
        }
        else{//äîáàâëåíèå íà ïåðâîå ìåñòî

            temp_node->next=head->first;
            temp_node->prev=NULL;
            (head->first)->prev=temp_node;
            head->first=temp_node;
            head->cnt++;
        }
    }
    return index;
}
