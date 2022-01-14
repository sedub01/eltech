#include <iostream>
#include <windows.h>
#include <time.h>
using std::cout;
using std::endl;

const int N = 100000000, BLOCKSIZE = 9308310, MAX_THREADS = 8, TIMES = 10;

int currentPos = 0;
double pi = 0.0;
LPCRITICAL_SECTION section = new CRITICAL_SECTION;

DWORD WINAPI MyThreadFunction(LPVOID lpParam){
    int* first = (int*)lpParam;
    int end = *first + BLOCKSIZE;
    long double x, tempPi;

    while (*first < N){
        tempPi = 0.0;
        for (int i = *first; (i < end) && (i < N); ++i){
            x = (i + 0.5) / N;
            tempPi += (4 / (1 + x*x));
        }
        EnterCriticalSection(section);
        pi += tempPi;
        currentPos += BLOCKSIZE;
        *first = currentPos;
        LeaveCriticalSection(section);
        end = *first + BLOCKSIZE;
    }
    return 0;
}

int main(){   
    DWORD t1;
    HANDLE hThreadArray[MAX_THREADS];
    int position[MAX_THREADS];
    double averageTime = 0.0;
    for (int j = 0; j < TIMES; j++){
        pi = 0.0;
        InitializeCriticalSection(section);

        for (int i = 0; i < MAX_THREADS; ++i){
            position[i] = BLOCKSIZE * i;
            currentPos = position[i];
            hThreadArray[i] = CreateThread(
                NULL,               // default security attributes
                0,                  // use default stack size  
                MyThreadFunction,   // thread function name
                &position[i],       // аргументы для поточной функции
                CREATE_SUSPENDED,   // создается остановленным
                NULL);              // returns the thread identifier
        }
        t1 = clock();

        for (int i = 0; i < MAX_THREADS; ++i)
            ResumeThread(hThreadArray[i]);
        WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

        pi /= (long double)N;
        DeleteCriticalSection(section);
        averageTime += clock() - t1;
        for (int i = 0; i < MAX_THREADS; ++i)
            CloseHandle(hThreadArray[i]);
    }
    
    printf("pi: %.10lf\n",pi);
    cout << "Average time: " << (long double)(averageTime / TIMES) / CLOCKS_PER_SEC << endl;

}
