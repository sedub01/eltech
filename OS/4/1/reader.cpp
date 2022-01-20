#include "consts.hpp"
#include <ctime>
HANDLE handleStdOut;
void LogWrite(string data){
    WriteFile(handleStdOut, data.c_str(), data.length(), NULL, NULL);
}

int main(){
    srand(time(NULL));

    HANDLE writeSemaphores[pageCount],
        readSemaphores[pageCount],
        IOMutex = OpenMutex(MUTEX_MODIFY_STATE | SYNCHRONIZE, false, mutexName.c_str()),
        mapFile = OpenFileMapping(GENERIC_READ, false, mapName.c_str());
    handleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD page = 0;

    for (int i = 0; i < pageCount; i++){
        string semaphoreName = "writeSemaphore #" + to_string(i);
        writeSemaphores[i] = OpenSemaphore(SEMAPHORE_MODIFY_STATE | SYNCHRONIZE, FALSE, semaphoreName.c_str());
        semaphoreName = "readSemaphore #" + to_string(i);
        readSemaphores[i] = OpenSemaphore(SEMAPHORE_MODIFY_STATE | SYNCHRONIZE, FALSE, semaphoreName.c_str());
    }

    for (int i = 0; i < 3; i++){
        LogWrite("Wait | Semaphore | " + to_string(GetTickCount()) + "\n");

        page = WaitForMultipleObjects(pageCount, readSemaphores, FALSE, INFINITE);
        LogWrite("Take | Semaphore | " + to_string(GetTickCount()) + "\n");

        WaitForSingleObject(IOMutex, INFINITE);
        LogWrite("Take | Mutex | " + to_string(GetTickCount()) + "\n");

        Sleep(500 + rand() % 1000);
        LogWrite("Read | Page: " + to_string(page) + " | " + to_string(GetTickCount()) + "\n");

        ReleaseMutex(IOMutex);
        LogWrite("Free | Mutex | " + to_string(GetTickCount()) + "\n");

        ReleaseSemaphore(writeSemaphores[page], 1, NULL);
        LogWrite("Free | Semaphore | " + to_string(GetTickCount()) + "\n\n");
    }

    for (int i = 0; i < pageCount; i++){
        CloseHandle(writeSemaphores[i]);
        CloseHandle(readSemaphores[i]);
    }
    CloseHandle(IOMutex);
	CloseHandle(mapFile);
	CloseHandle(handleStdOut);
}