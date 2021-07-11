#include "includesH/book.h"//стандартные библиотеки, структуры и константы
#include "includesC/nodes.c" //операции над списком
#include "includesC/enter.c"//ввод данных из файла в список
#include "includesC/print.c"//Стандартные общие функции
#include "includesC/sort.c"//сортировка
#include "includesC/menus.c"//разные меню

int main()
{
    Head *head;

    head = enter();
    if (head)
    {
        printf("There is data from file\n");
        print(head);
        main_menu(head);
        free_list(head);
    }
    return 0;
}



