#include <iostream>
#include <windows.h>
using std::cout;
using std::cin;
const int size = 128;
bool ConnectToPipe(HANDLE&);
bool GetMyMessage(HANDLE&, char[]);
void WINAPI Callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    cout << "\nMessage recieved\n";
}

int main(){
    HANDLE pipeHandle = nullptr;
    char message[size];

    if (ConnectToPipe(pipeHandle)){
        cout << "Connection completed\n";
        while(GetMyMessage(pipeHandle, message))
            printf("Message: \"%s\"\n", message);
    } 
    else cout << "Connection failed\n";
    if (CloseHandle(pipeHandle))
        cout << "Chanell closed successfully\n";
    else cout << "Chanell wasn't closed\n";
    system("pause");
}

bool ConnectToPipe(HANDLE& hPipe){
    hPipe = CreateFile(TEXT("\\\\.\\pipe\\pipename"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    return hPipe != INVALID_HANDLE_VALUE;
}

bool GetMyMessage(HANDLE& hPipe, char message[]){
    OVERLAPPED overlapped = OVERLAPPED();
    bool flag = ReadFileEx(hPipe, message, size, &overlapped, Callback);
    SleepEx(INFINITE, true);
    if (!strcmp(message, "")) flag = false;
    return flag;
}