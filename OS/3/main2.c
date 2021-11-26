#include <time.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 4 //(1, 2, 4, 8, 12, 16).
#define min(a,b) ((a) < (b) ? (a) : (b))
//https://www.youtube.com/watch?v=p0woqF2XCeg

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

        double x;
        int k;

        #pragma omp shedule(auto) parallel for  private(pi)
        for (k = 0; k < j; k++){
            omp_set_num_threads(MAX_THREADS);
            //omp_set_dynamic(MAX_THREADS);
            pi = 0;
            printf("k = %d\n", k);
            printf("thread %d\n", omp_get_num_threads);
            printf("pi[start] = %lf\n", pi);
            while(pDataArray[k]->i < N){
                int flag = min(numberTicket*10, N - pDataArray[k]->i);

                for ( int j=0; j<flag; j++ ){
                    x = (j+pDataArray[k]->i+0.5)*1/N;
                    pi += 4/(1+x*x);
                }
                pDataArray[k]->i += MAX_THREADS * numberTicket*10;
            }
            pDataArray[k]->pi = pi;
            printf("pi[end] = %lf\n\n", pi);
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
