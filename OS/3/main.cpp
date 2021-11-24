#include <windows.h>
#include <time.h>
#include <iostream>
using std::cout;
#define MAX_THREADS 8 //(1, 2, 4, 8, 12, 16).
 
DWORD WINAPI MyThreadFunction(LPVOID lpParam);
const int numberTicket = 930831, N=1000000000;
 
typedef struct NumberOfPi{
    int i; //кол-во слагаемых в одном потоке
    double pi; //получившееся слагаемое (в одном потоке)
}NuOfPi,*PNuOfPi;
 
int main(){
    DWORD  dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS];
    PNuOfPi pDataArray[MAX_THREADS];
    double pi=0;
    unsigned long t1, t2;
    int i, j=MAX_THREADS;

    cout<<"Wait, please...\n";
    for(i=0; i<j; i++){
        //возвращает указатель на неперемещаемый блок памяти из кучи (он пока равен 0)
        pDataArray[i] = (PNuOfPi) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,sizeof(NuOfPi));
       
        pDataArray[i]->i = i*numberTicket*10;
        pDataArray[i]->pi = 0;
 
        hThreadArray[i] = CreateThread(
        NULL,                   // default security attributes
        0,                      // use default stack size  
        MyThreadFunction,       // thread function name
        pDataArray[i],          // аргументы для поточной функции
        CREATE_SUSPENDED,       // создается остановленным
        &dwThreadIdArray[i]);   // returns the thread identifier
    }
   
    t1=clock();
    for (i=0; i<j; i++)
        //продолжает потоки, так как они созданы "остановленными"
        ResumeThread(hThreadArray[i]);      
    //Ожидает, пока все указанные объекты не перейдут в сигнальное состояние
    if (!WaitForMultipleObjects(j, hThreadArray, TRUE, INFINITE)) //j=length(hThreadArray)
        cout << "All threads are closed\n\n";
        else cout << "Something went wrong!\n\n";
    //теперь остался поток main
    t2=clock();
 
    //складываю получившиеся значения из каждого потока
    for (i=0; i<j; i++){
        pi += pDataArray[i]->pi;
        CloseHandle(hThreadArray[i]);
        HeapFree(GetProcessHeap(), 0, pDataArray[i]);
    }
    printf("pi: %lf",pi/N);
    cout << "\nTime " << (t2-t1) / (double)CLOCKS_PER_SEC << "\n";
    system("pause");
}
DWORD WINAPI MyThreadFunction(LPVOID lpParam){
    PNuOfPi pDataArray = (PNuOfPi)lpParam;
    double pi=0, x;
 
    while(pDataArray->i < N){
        for(int j = 0; j < numberTicket*10 && j + pDataArray->i < N; j++){
            x = (j+pDataArray->i+0.5)*1/N;    
            pi += 4/(1+x*x);
        }
        pDataArray->i += MAX_THREADS * numberTicket*10;
    }
    pDataArray->pi = pi;
    return 0;
}