#include <iostream>
#include <windows.h>
#include <time.h>
#include <omp.h>
using std::cout;
using std::endl;

const int N = 100000000, BLOCKSIZE = 9308310, MAX_THREADS = 16, TIMES = 10;

int main(){
    DWORD t1;

    long double pi = 0.0, averageTime = 0.0;

    for (int j = 0; j < TIMES; j++){
        pi = 0.0;
        t1 = clock();

        #pragma omp parallel shared(t1) reduction (+:pi) num_threads(MAX_THREADS)
        {
            #pragma omp for schedule(dynamic, BLOCKSIZE) nowait
            for (int i = 0; i < N; ++i){
                long double x = (i + 0.5) / N;
                pi += 4 / (1 + x * x);
            }
        }

        pi /= (long double)N;
        averageTime += clock() - t1;
    }

    cout << "pi: " << pi << endl;
    cout << "Average time: " << (long double)(averageTime / TIMES) / CLOCKS_PER_SEC << endl;
}
