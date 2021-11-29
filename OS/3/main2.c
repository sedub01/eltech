#include <time.h>
#include <stdio.h>
#include <omp.h>
#include <unistd.h>
const int N = 100000000, numberTicket = 930831, MAX_THREADS = 8;

int main(){
    double pi = 0.0, x;
    omp_set_num_threads(MAX_THREADS);
    printf("Wait please...\n");
    unsigned long t1 = clock();
    #pragma omp parallel for schedule(dynamic, numberTicket) reduction(+:pi)
    for(int i = 0; i < N; ++i)
        pi += 4.0/(1.0 + ((i+0.5)/N)*((i+0.5)/N)); //иначе работает медленнее
    printf("Time %lf\n", (clock()-t1) / (double)CLOCKS_PER_SEC);
    printf("pi = %.10lf\n", pi/N);
}
