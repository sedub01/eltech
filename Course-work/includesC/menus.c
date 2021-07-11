#include "../includesH/menus.h"

void main_menu(Head *head)
{
    int option = -1;

    while (option)
    {
        puts("Choose the option:");
        puts("[666]Info about program");
        puts("[1]Print the table");
        puts("[2]Information about book");
        puts("[3]Adding new books");
        puts("[4]Change information about book");
        puts("[5]Delete book");
        puts("[6]Swap books");
        puts("[7]Selection of books in the range");
        puts("[8]Sorting");
        puts("[9]Save changes");
        puts("[0]Exit");

        option = safe_scanf();
        CLS;
        switch(option)
        {
        case 1:
            print(head);
            break;
        case 2:
            info_menu(head);
            break;
        case 3:
            getchar();
            adding_nodes_menu(head);
            break;
        case 4:
            change_info_about_book(head);
            break;
        case 5:
            delete_book(head);
            break;
        case 6:
            swap_books(head);
            break;
        case 7:
            range_books(head);
            break;
        case 8:
            sorting_menu(head);
            break;
        case 9:
            save_changes(head);
            break;
        case 666:
            program_info();
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Wrong option\n");
        }
    }
}

void adding_nodes_menu(Head *head)
{
    char option[MAXLEN]="No";
    int index;
    //ß âûáðàë èìåííî òàêîé ðàçìåð äëÿ òîãî, ÷òîáû ïîëüçîâàòåëü ìîã ââîäèòü áîëüøèå ñòðîêè
    //èíà÷å ïðîãðàììà ëàãàåò

    do
    {
        index = add_node(head);
        strcpy(option, "no");
        if (index)
        {
            printf("Do you want to enter something else? ");
            getchar();
            fgets(option, MAXLEN, stdin);
            option[strlen(option)-1]='\0';
            CLS;
        }
    }while (strcmp(option, "yes")==0);
    if (index) printf("Changes were saved\n\n");
}

void sorting_menu(Head *head)
{
    float (*kind[4])(Node*);
    int order=0, option = 4;

    kind[0] = YearValue;
    kind[1] = ListsValue;
    kind[2] = WordcountValue;
    kind[3] = RatingValue;

    do
    {
    if (option<0 || option>6) printf("Wrong option! Answer again\n");
    printf("What do you want to sort?\nPress:\n");
    printf("[1] for name\n");
    printf("[2] for author\n");
    printf("[3] for year\n");
    printf("[4] for number of pages\n");
    printf("[5] for number of words\n");
    printf("[6] for rating\n");
    printf("[0] for exit to main menu\n");
    option = safe_scanf();
    CLS;
    } while (option<0 || option>6);

    if (option)
    {
        do //âûáîð, â êàêîì ïîðÿäêå ñîðòèðîâàòü
        {
        if (order<0 || order>2) printf("Wrong option! Answer again\n");
        printf("How do you want to sort?\nPress:\n");
        printf("[1] in order\n[2] in backwards\n[0] Return to main menu\nEnter your choice ");
        order=safe_scanf();
        CLS;
        } while (order<0 || order>2);//òóò ÿ èñïðàâèë ñ 0 è 1 íà 1 è 2,äëÿ òîãî ÷òîáû ìîæíî áûëî âûéòè â ãëàâíîå ìåíþ

        if (order)
        {
            if (option>2 && option<7) sort_number(head, kind[option-3], order-1);
            else sort_word(head, option, order-1);//ïîòîìó ÷òî äðóãèõ ïàðàìåòðîâ è áûòü íå ìîæåò
            printf("Books were been sorted\n\n");
        }
    }
}

void info_menu(Head *head)
{
    Node *temp;
    int key=0;
    char bookname[MAXLEN];

    temp=head->first;
    printf("Enter the name of book: ");
    getchar();
    fgets(bookname, MAXLEN, stdin);
    bookname[strlen(bookname)-1]='\0';
    CLS;
    while (temp)
    {
        if (strcmp(bookname, temp->name)==0)
        {
            key=1;
            printf("_____Info about \"%s\"_____", bookname);
            printf("\nBook title: %s\n", temp->name);
            printf("Author of book: %s\n", temp->author);
            printf("Year of publishing: %d\n", temp->year);
            printf("Number of pages: %d\n", temp->lists);
            printf("Number of words: %.2f thousands\n", temp->wordcount);
            printf("Rating of book: %.2f\n", temp->average);
            //Èñêóññòâåííûé èíòåëëåêò ñîáñòâåííîãî ïðîèçâîäñòâà
            printf("My own opinion: this book was published ");
            if (temp->year<1950) printf("a long time ago, \n");
            else printf("recently, \n");
            if (temp->lists<300) printf("it won't take long to read this book, \n");
            else printf("you should set aside time for this book, \n");
            printf("and I think this book ");
            if (temp->average<4) printf("doesn't worth reading at all\n\n");
            else if (temp->average<4.6) printf("is worth your attention\n\n");
            else printf("is masterpiece itself\n\n");
        }
        temp=temp->next;
    }
    if (!key) printf("I haven't found required book\nYou can add it to the library\n\n");
}

void delete_book(Head *head)
{
    char bookname[MAXLEN];
    int key=0;
    Node *temp;
    if (head->cnt==1)
            printf("You can't delete the last book of this library\n\n");
    else
    {
        temp=head->first;
        printf("Enter the name of the book to delete it: ");
        getchar();
        fgets(bookname, MAXLEN, stdin);
        bookname[strlen(bookname)-1]='\0';
        CLS;
        while (temp)
        {
            if (strcmp(bookname, temp->name)==0)
            {
                if(temp==head->last)
                {
                    head->last=temp->prev;
                    (temp->prev)->next=NULL;
                    free(temp);
                }
                else if (temp->prev!=NULL)
                {
                    (temp->prev)->next=temp->next;
                    (temp->next)->prev=temp->prev;
                    free(temp);
                }
                else //if (temp->prev==NULL)
                {
                    head->first = temp->next;
                    head->first->prev=NULL;
                    free(temp);
                }
                key=1;
                head->cnt--;
            }
            temp=temp->next;
        }
        if (!key) printf("I haven't found required book\n\n");
        else printf("The book successfully deleted!\n\n");
    }
}

void save_changes(Head *head)
{
    char save[MAXLEN];
    FILE *myfile;
    Node *temp;

    printf("Do you really want to save changes in file? ");
    getchar();
    fgets(save, MAXLEN, stdin);
    CLS;
    if (strcmp(save, "yes\n")==0)
    {
        myfile = fopen("File.csv", "w");
        temp=head->first;
        while (temp)
        {
            fprintf(myfile, "%s;%s;%d;%d;%.2f;%.2f\n", temp->name, temp->author, temp->year, temp->lists, temp->wordcount, temp->average);
            temp=temp->next;
        }
        printf("Changes were saved\n\n");
        fclose(myfile);
    } else printf("Changes weren't saved\n\n");
}

void program_info()
{
    printf("There is information about how to use this program\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("Compatible with Windows32, Linux and Mac\n");
    printf("All you can do is in main menu\n");
    printf("This program recognizes letters if it's allowed to enter numbers\n");
    printf("Number of pages appears in thousands in field \"wordcount\"\n");
    printf("If you accidentally pressed an option, you can enter any line or 0, \nwhere it's written, to go to the main menu\n");
    printf("After changes of library table isn't shown up automatically\n");
    printf("If you want to see the result, press [1]\n");
    printf("All changes are saved in library\n");
    printf("If you want to save changes in file, press [9] and enter \"yes\" \n");
    printf("If the question starts with \"Do you want to...\", it means that \nyou can answer \"yes\" or \"no\" \n");
    printf("If you answer on this question with random input, program recognizes it as \"no\"\n");
    printf("Some functions ask to enter name of book instead of index of this book\n");
    printf("I've made it specially because I prefer enter full names instead of pathetic indexes\n");
    printf("In option [7] table isn't saved in list, it just shows required books\n");
    printf("Powered by Semen Dubenkov in May 2020 with cup of tea and cookies\n\n");
}
void change_info_about_book(Head *head)
{
    char bookname[MAXLEN];
    Node *temp;
    int option=-1;
    char word[MAXLEN];

    print(head);
    printf("Enter the book: ");
    getchar();
    fgets(bookname, MAXLEN, stdin);
    bookname[strlen(bookname)-1]='\0';
    temp=head->first;
    while (temp)
    {
        if (strcmp(bookname, temp->name)==0)
        {
            while(option<0|| option>6)
            {
                printf("Enter what do you want to change\n");
                puts("[1] Name");
                puts("[2] Author");
                puts("[3] Year");
                puts("[4] Number of pages");
                puts("[5] Number of words");
                puts("[6] Rating");
                puts("[0] Return to main menu");
                option = safe_scanf();
                CLS;
                if (option<0 || option>6) printf("Wrong option\n");
            }

            if (option)
            switch (option)
            {
            case 1:
                printf("Enter new name of book: ");
                getchar();
                fgets(word, MAXLEN, stdin);
                word[strlen(word)-1]='\0';
                strcpy(temp->name, word);
                break;
            case 2:
                printf("Enter new author of book: ");
                getchar();
                fgets(word, MAXLEN, stdin);
                word[strlen(word)-1]='\0';
                strcpy(temp->author, word);
                break;
            case 3:
                printf("Enter new year of publishing: ");
                temp->year = safe_scanf();
                break;
            case 4:
                printf("Enter new number of pages: ");
                temp->lists = safe_scanf();
                break;
            case 5:
                printf("Enter new number of words(in thousands): ");
                temp->wordcount = safe_scanf_f();
                break;
            case 6:
                printf("Enter new rating of this book: ");
                temp->average = safe_scanf_f();
                break;
            }
        }
        temp=temp->next;
    }
    CLS;
    if (option == -1) printf("I haven't found required book\n\n");
    else if (option) printf("Changes were saved\n\n");
}

void swap_books(Head *head)
{
    char bookname1[MAXLEN], bookname2[MAXLEN];
    Node *temp1, *temp2;
    int key=1;

    print(head);
    printf("Enter books you want to swap:\n");
    getchar();
    fgets(bookname1, MAXLEN, stdin);
    bookname1[strlen(bookname1)-1]='\0';
    temp1=head->first;
    fgets(bookname2, MAXLEN, stdin);
    bookname2[strlen(bookname2)-1]='\0';
    CLS;
    temp2=head->first;

    while(temp1&&key)
        {
            if (strcmp(bookname1, temp1->name)!=0) temp1=temp1->next;
            else key=0;
        }
    key=1;
    while(temp2&&key)
        {
            if (strcmp(bookname2, temp2->name)!=0) temp2=temp2->next;
            else key=0;
        }
    if (temp1&&temp2)
    {
        swap(temp1, temp2);
        printf("Books were been swaped\n\n");
    }
    else printf("I can't find one of chosen books\n\n");
}

void range_books(Head *head)
{
    int option=-1;
    float min, max, a;
    char string[MAXLEN], min_ch, max_ch, b;
    Node *temp;
    int key=0;

    while(option<0 || option>6)
    {
        printf("Select which field to search for books in\n");
        printf("[1] Name of the book\n");
        printf("[2] Author\n");
        printf("[3] Year\n");
        printf("[4] Number of pages\n");
        printf("[5] Number of words\n");
        printf("[6] Rating\n");
        printf("[0] Exit menu\n");
        option=safe_scanf();//scanf("%d", &option);
        CLS;
        if (option<0 || option>6) printf("Wrong option\n");
    }
    if (option)
    {
        if (option>=3 && option<=6)//äëÿ ÷èñëîâûõ ïîëåé
        {
            printf("Enter the lower and upper limits:\n");
            min = safe_scanf_f();
            max = safe_scanf_f();
            CLS;
            if (min>max)
            {
                a=max;
                max=min;
                min=a;
            }
        }
        else //äëÿ òåêñòîâûõ ïîëåé
        {
            printf("Enter via space from which to which letter search for:\n");
            getchar();
            fgets(string, MAXLEN, stdin);
            min_ch=toupper(string[0]);
            max_ch=toupper(string[2]);
            CLS;
            if (min_ch>max_ch)
            {
                b=max_ch;
                max_ch=min_ch;
                min_ch=b;
            }
        }

        temp=head->first;
        //Çäåñü ìû äîëæíû ïðîâåðèòü ÷èñëà è áóêâû â ïîëÿõ, ÷òî îíè ïîïàäàþò â äèàïàçîí ìåæäó min è max
        while(temp)
        {
            if ( ( (toupper(temp->name[0]))>min_ch && (toupper(temp->name[0])<max_ch) && option==1)     ||
                 ( (toupper(temp->author[0]))>min_ch && (toupper(temp->author[0])<max_ch) && option==2) ||
                 ( (temp->year>min && temp->year<max) && option==3)           ||
                 ( (temp->lists>min && temp->lists<max) && option==4)         ||
                 ( (temp->wordcount>min && temp->wordcount<max) && option==5) ||
                 ( (temp->average>min && temp->average<max) && option==6)
               ) key=1;
            temp = temp->next;
        }

        temp=head->first;

        if (key)
        {
            printf("|%30s |%18s |%5s| %5s|%10s|%7s|\n",
            "name","author","year", "pages", "wordcount", "rating");
            puts(TEXTBAR);
            while (temp)
            {
                switch(option)
                {
                case 1:
                    if ((toupper(temp->name[0]))>=min_ch && (toupper(temp->name[0])<=max_ch))
                    printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
                    temp->name,temp->author,
                    temp->year, temp->lists,
                    temp->wordcount, temp->average);
                    temp=temp->next;
                    break;
                case 2:
                    if ((toupper(temp->author[0]))>=min_ch && (toupper(temp->author[0])<=max_ch))
                    printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
                    temp->name,temp->author,
                    temp->year, temp->lists,
                    temp->wordcount, temp->average);
                    temp=temp->next;
                    break;
                case 3:
                    if (temp->year >= min && temp->year <= max)
                    printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
                    temp->name,temp->author,
                    temp->year, temp->lists,
                    temp->wordcount, temp->average);
                    temp=temp->next;
                    break;
                case 4:
                    if (temp->lists >= min && temp->lists <= max)
                    printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
                    temp->name,temp->author,
                    temp->year, temp->lists,
                    temp->wordcount, temp->average);
                    temp=temp->next;
                    break;
                case 5:
                    if (temp->wordcount >= min && temp->wordcount <= max)
                    printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
                    temp->name,temp->author,
                    temp->year, temp->lists,
                    temp->wordcount, temp->average);
                    temp=temp->next;
                    break;
                case 6:
                    if (temp->average >= min && temp->average <= max)
                    printf("|%30s |%18s |%5d| %5d|%10.2f|%7.2f|\n",
                    temp->name,temp->author,
                    temp->year, temp->lists,
                    temp->wordcount, temp->average);
                    temp=temp->next;
                    break;
                }
            }
            puts(TEXTBAR);
        }
        else printf("Your values don't match\n\n");//çíà÷èò, ÷òî íè îäíî ÷èñëî íå ïîïàëî â äèàïîçîí
    }
}
