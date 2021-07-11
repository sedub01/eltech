Head *make_head();//инициализация головы
Node *create_node2(char *name,char *author, int year, int lists, float wordcount,float average); //создание узла и заполнение
void add_first2(Head *my_head, Node *new_node);//связывание головы и первого узла списка
void insert_after2(Head *my_head,Node *current_node, Node *new_node);//вставка
Node *fill_node(FILE *myfile);//заполнение узла информацией
int add_node(Head *head);//добавление книги на выбранную позицию
void free_list(Head *head);//очистка списка
