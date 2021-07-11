#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <fstream>
using namespace std;
//const int N = 7;
const int inf = 1000; //сокращенное от infinity
char Universum[] = "abcdefghijklmnopqrstuvwxyz"; 

class Graph{
private:
    int n, m; //кол-во вершин и ребер
    int **G; //матрица расстояний от каждой вершины до каждой
public:
    Graph(int);
    void exe(int start, int end, int N) const;
    ~Graph() {for (int i=0; i<n; i++) delete [] G[i]; delete [] G;};
};
char Ch(int c) { return c + 'a';}
int length(int a);
int enter(int N);

int main()
{
    srand(time(NULL));
    int N;
    cout << "Enter size of graph(<=26): ";
    cin >> N;
    while (N>26 || N<1)
    {
        cout << "Wrong size!\n";
        cin >> N;
    }
    Graph one(N);
    int start, end;
        
    cout << "\nEnter start vertex: ";
    
    start = enter(N);
    cout << "Enter final vertex: ";
    end = enter(N);

    one.exe(start, end, N);
    
    getch();
    return 0;
}

//нельзя допустить, чтобы в графе были бессвязные вершины (иначе данные будут недочитываться)
Graph::Graph(int N): n(0), m(0)
{
    int i, j;
    string s;
    /*ifstream myfile("file.txt");
    if (!myfile)
    {
        cout << "It's impossible to open the file";
        getch();
        exit(1);
    }*/

    G = new int*[N];
    for (i=0; i<N; i++)
    G[i] = new int[N];
    for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    G[i][j] = 0;

    //cout << "All sets are entered from file\n";
    cout << "\nMatrix";
    for (i=0; i<2*N; i++) cout << ' ';
    cout << "Dijkstra";
    do{
        s.resize(0);
        for (int k=0; k<N; k++)
        if (rand()%2 == 0) s += Universum[k];
        if (s.size() == 0) s += Universum[rand()%N];
        //myfile >> s; //чтение файла
        //cout << "v[" << Ch(n) << "] = " << s << endl;
        for (auto k : s)
            if (isalpha(k)){
                j = tolower(k) - 'a';
                G[n][j] = 1;
            }
        ++n;
    }while(isalpha(s[0]) && n<N);
    //myfile.close();

    for (i=0; i<N; ++i)
        for (j=0; j<N; ++j)
        G[i][j] *= rand()%8 + 1; //наращивание ребер
        //умножение на число от 1 до 9, чтобы красиво выводилась таблица
    n=m=0;
    for (i=0; i<N; ++i)
    {
        int f = 0;
        cout << endl << Ch(i) << ": ";
        for (j=0; j<N; ++j)
        if (G[i][j])
        {
            ++f;
            cout << Ch(j)<<' ';
        }
        else cout << "- ";
        m += f;
        if (f) ++n;
        else break;
        cout << "   ";
        //вывод нагруженных ребер
        for (j=0; j<N; ++j) cout << G[i][j] << ' ';
    }
    cout << "\n|V| = " << n << " |E| = " << m << endl;
}

void Graph::exe(int start, int end, int N) const
{
    int tmp, minindex, min, i;
    int d[N], //минимальное расстояние
        v[N]{}; //посещенные вершины
    for (i=0; i<N; i++) d[i] = inf;
    d[start] = 0;

    do{
    minindex = inf;
    min = inf;
    for (int i = 0; i<N; i++)
    { // if vertex isn't visited and it's weight < min
        if ((v[i] == 0) && (d[i]<min))
        {
            min = d[i];
            minindex = i;
        }
    }
    //Sum founded min weight to current weight
    if (minindex != inf)
    {
        for (int i = 0; i<N; i++)
            if (G[minindex][i] > 0)
            {
                tmp = min + G[minindex][i];
                if (tmp < d[i]) d[i] = tmp;  
            }
        v[minindex] = 1;
    }
    }while(minindex < inf);
    cout << "\nShortest distances to vertices: \n";
    for (i = 0; i<N; i++) 
    {
        cout << Ch(i);
        if (d[i] == inf) cout << ' ';
        else
        for (int j=0; j<length(d[i]); j++) cout << ' ';
    }
    cout << endl;
    for (i = 0; i<N; i++)
        if (d[i] == inf) cout << "- ";
        else cout << d[i] << ' ';
    cout << endl;
    //for (int i = 0; i<N; i++) cout << v[i] << ' ';

    //Going backwards
    int ver[N]; // массив посещенных вершин
    
    ver[0] = end + 1; // идем с конца
    int k = 1; // индекс предыдущей вершины
    int w = d[end]; // вес конечной вершины

    if (d[end] == inf) 
    {
        cout << "\nIt's impossible to reach this vertex\n ";
        getch();
        exit(1);
    }
    while (end != start) // пока не дошли до начальной вершины
    {
        for (int i = 0; i<N; i++) // просматриваем все вершины
        if (G[i][end] != 0)   // если связь есть
        {
            tmp = w - G[i][end]; // определяем вес пути из предыдущей вершины
            if (tmp == d[i]) // если вес совпал с рассчитанным
            {                 // значит из этой вершины и был переход
            w = tmp; 
            end = i;       // сохраняем предыдущую вершину
            ver[k] = i + 1; // и записываем ее в массив
            k++;
            }
        }
    }
    cout << "\nOutput of shortest way from " << Ch(ver[k-1] -1) << " to "<< Ch(ver[0]-1) << ":\n";
    for (int i = k - 1; i >= 0; i--)
    cout << Ch(ver[i] -1) << ' ';
}
int length(int a)
{
    int c=0;
    if (a != 0)
    while (a!=0) 
    {
        a /= 10;
        c++;
    }
    else c++;
    return c;
}

int enter(int N)
{
    char ch;
    cin >> ch;
    while (ch > 'a'+ N - 1 || ch < 'a')
    {
        cout << "Wrong option\n";
        cin >> ch;
    }
    return ch - 'a';
}