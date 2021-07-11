#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include <ctime>
const int inf = 1000;
int e;
using namespace std;
struct Edges {
    int v, u, w;
};
class Graph
{
private:
    vector <Edges> edge;
public:
    Graph(int n);
    //алгоритм Беллмана-Форда
    void bellman_ford(int n, int s, int end);
    ~Graph() = default;
};

char Ch(int c) {return c + 'a';}
int enter(int n);
int length(int a);
void entero(int &option);

int main()
{
    srand(time(NULL));
    int i, j, weight, start, end, n;
 
    cout << "Size of graph (<=26): "; cin >> n;
    while (n>26 || n<2)
    {
        cout << "Wrong size!\n";
        cin >> n;
    }
    Graph one(n);
    
    cout << "Start vertex > ";
    start = enter(n);
    cout << "Final vertex > "; 
    end = enter(n);
    
    one.bellman_ford(n, start - 1, end-1);
    getch();
    return 0;
}

Graph:: Graph(int n)
{
    edge.resize(n*n);
    int i, j, weight, option=-1, choice;
    e = 0;
    cout << "Which graph do you need?\n";
    cout << "[0] manual\n";
    cout << "[1] automatic\n";
    cout << "Enter: ";
    entero(option);
    if (option)
    {
        cout << "What edges do you want to see in the graph?\n";
        cout << "[0] Only positive ones\n";
        cout << "[1] Positive and negative\n";
        cout << "Enter: ";
        entero(choice);
    }
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (!option)
            {
                cout << Ch(i) << " -> " << Ch(j) << ": ";
                cin >> weight;
            }
            else
            {
                if (!choice) weight = rand()%10;
                else weight = rand()%17 -9;
                //чтобы красиво выводилась таблица
            }
                edge[e].v = i;
                edge[e].u = j;
                edge[e++].w = weight;
        }
        cout << endl;
    }
    //здесь е = n*n, однако
    //алгоритм не будет обрабатывать вершины с нулевым весом, 
    //то есть алгоритм будет работать (кол-во ребер) раз 
    
    cout << "  ";
    for (i = 0; i < n; i++) cout << setw(3) << (char)(i+'a');
    for (i=0, j=0; i<n*n; i++)
    {
        if (i%n == 0) 
        {
            cout << endl;
            cout << (char)(i%n + (j++)+'a') << ':'; 
        }
        cout<<setw(3) << edge[i].w;
    }
    cout << endl;
}

void Graph :: bellman_ford(int n, int s, int end)
{
    int i, j, x;
    vector <int> d(n, inf); //расстояние до всех вершин
    vector<int> p (n, -1); //массив предков соответсвующих вершин
    d[s] = 0;
 
    for (i=0;i<n ;i++)
    {   
        x = -1;
        for (j = 0; j < e; j++)
            if (d[edge[j].v] < inf && edge[j].w != 0) //выполняется (кол-во ребер) раз
				if (d[edge[j].u] > d[edge[j].v] + edge[j].w) {
					d[edge[j].u] = max(-inf, d[edge[j].v] + edge[j].w);
					p[edge[j].u] = edge[j].v;
					x = edge[j].u;
				}
    }
    
    //Восстановление пути
    if (x != -1) cout << "Negative cycle detected\n";
    else if (d[end] == inf) cout << "It's impossible to reach " << Ch(end) << endl;
    else
    {
        cout << endl << Ch(s) << "->" << Ch(end) << "=" << d[end] << endl;
	    cout << "No negative cycle from " << Ch(s) << endl;
        vector<int> path;
		for (int cur=end; cur!=-1; cur=p[cur])
			path.push_back (cur);
		reverse (path.begin(), path.end());
		cout << "Path from " << Ch(s) << " to " << Ch(end) << ": ";
		for (size_t i=0; i<path.size(); ++i)
			cout << Ch(path[i]) << ' ';
        
        cout << "\nShortest distances to vertices: \n";
        for (i = 0; i<n; i++) 
        {
            cout << Ch(i);
            if (d[i] == inf) cout << ' ';
            else
            for (int j=0; j<length(d[i]); j++) cout << ' ';
        }
        cout << endl;
        for (i = 0; i<n; i++)
            if (d[i] == inf) cout << "- ";
            else cout << d[i] << ' ';
        cout << endl;
    }
        
}

int enter(int n)
{
    char ch;
    cin >> ch;
    while (ch > 'a'+ n - 1 || ch < 'a')
    {
        cout << "Wrong option\n";
        cin >> ch;
    }
    return ch - 'a' + 1;
}

void entero(int &option)
{
    cin >> option;
    while (option < 0 || option > 1)
    {
        cout << "Wrong option!\n";
        cin >> option;
    }
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
