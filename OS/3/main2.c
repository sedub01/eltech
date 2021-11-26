#include <time.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 5 //(1, 2, 4, 8, 12, 16).
#define min(a,b) ((a) < (b) ? (a) : (b))

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

    printf("Wait, please...\n");
    for (i=0; i<j; i++){
        //возвращает указатель на неперемещаемый блок памяти из кучи (он пока равен 0)
        //pDataArray[i] = (PNuOfPi) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,sizeof(NuOfPi));
        //pDataArray[i] = new NuOfPi();
        pDataArray[i] = (PNuOfPi) malloc(sizeof(NuOfPi));
        pDataArray[i]->i = i*numberTicket*10;
        pDataArray[i]->pi = 0;
    }
   
    t1=clock();

    //что если запихать pragma в сам цикл?
    #pragma omp parallel shared(pDataArray) 
    {//без pragma omp то же самое
        double pi, x;
        //pDataArray[k]
        int k = omp_get_thread_num();
        //for (int k = 0; k < j; k++){
            pi = 0;
            printf("k = %d\n", k);
            printf("pi[start] = %lf\n", pi);
            while(pDataArray[k]->i < N){
                int flag = min(numberTicket*10, N - pDataArray[k]->i);
                #pragma omp for schedule(dynamic, MAX_THREADS)
                for ( int j=0; j<flag; j++ ){
                    x = (j+pDataArray[k]->i+0.5)*1/N;    
                    pi += 4/(1+x*x);
                }
                pDataArray[k]->i += MAX_THREADS * numberTicket*10;
            }
            pDataArray[k]->pi = pi;
            printf("pi[end] = %lf\n\n", pi);
        //}
    }
    
    t2=clock();
 
    //складываю получившиеся значения из каждого потока
    for (i=0; i<j; i++)
        pi += pDataArray[i]->pi;
    printf("pi: %lf",pi/N);
    printf("\nTime %lf\n", (t2-t1) / (double)CLOCKS_PER_SEC);
    // for (i = 0; i < j; i++)
    //     delete pDataArray[i];
    free(pDataArray);
}
