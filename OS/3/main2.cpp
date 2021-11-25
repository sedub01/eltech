#include <time.h>
#include <iostream>
#include <omp.h>
using std::cout;
#define MAX_THREADS 4 //(1, 2, 4, 8, 12, 16).

const int numberTicket = 930831, N=1000000000;
 
typedef struct NumberOfPi{
    int i; //кол-во слагаемых в одном потоке
    double pi; //получившееся слагаемое (в одном потоке)
}NuOfPi,*PNuOfPi;
 
int main(){
    PNuOfPi pDataArray[MAX_THREADS];
    double pi=0;
    unsigned long t1, t2;
    int i, j=MAX_THREADS;

    cout<<"Wait, please...\n";
    for(i=0; i<j; i++){
        //возвращает указатель на неперемещаемый блок памяти из кучи (он пока равен 0)
        //pDataArray[i] = (PNuOfPi) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,sizeof(NuOfPi));
        pDataArray[i] = new NuOfPi();
        pDataArray[i]->i = i*numberTicket*10;
        pDataArray[i]->pi = 0;
    }
   
    t1=clock();

    #pragma omp parallel for schedule(dynamic, MAX_THREADS)
    {//без schedule то же самое
        double pi, x;
        //pDataArray[k]
        for (int k = 0; k < j; k++){
            pi = 0;
            cout << "k = " << k << "\n";
            cout << "pi[start] = " << pi << "\n";
            while(pDataArray[k]->i < N){
                for(int j = 0; j < numberTicket*10 && j + pDataArray[k]->i < N; j++){
                    x = (j+pDataArray[k]->i+0.5)*1/N;    
                    pi += 4/(1+x*x);
                }
                pDataArray[k]->i += MAX_THREADS * numberTicket*10;
            }
            pDataArray[k]->pi = pi;
            cout << "pi[end] = " << pi << "\n\n";
        }
    }
    
    t2=clock();
 
    //складываю получившиеся значения из каждого потока
    for (i=0; i<j; i++)
        pi += pDataArray[i]->pi;
    printf("pi: %lf",pi/N);
    cout << "\nTime " << (t2-t1) / (double)CLOCKS_PER_SEC << "\n";
    for (i = 0; i < j; i++)
        delete pDataArray[i];
    system("pause");
}
