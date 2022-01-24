#include <iostream>
#include <windows.h>
using std::cout;
const int size = 128;

bool ConnectToPipe(HANDLE&, HANDLE&);
bool SendMyMessage(HANDLE&, HANDLE&, bool&);

int main(){
    HANDLE pipeHandle = nullptr, 
        eventHandle = nullptr;
    bool isConnected = false, endFlag = false;

    isConnected = ConnectToPipe(pipeHandle, eventHandle);

    if (isConnected){
        cout << "Chanell connected successfully\n";
        printf("Enter the messages below %d characters (or empty string to quit):\n\n", size);
        while(!endFlag){
            isConnected = SendMyMessage(pipeHandle, eventHandle, endFlag);
            if (endFlag) cout << "Message thread is over\n";
            else if (isConnected) cout << "Message was delivered\n";
            else cout << "Message wasn't delivered\n";
        }

        if (DisconnectNamedPipe(pipeHandle))
            cout << "Server disconnected successfully\n";
        else cout << "Server disconnected unsuccessfully\n";

        if (pipeHandle != INVALID_HANDLE_VALUE) CloseHandle(pipeHandle);
        if (eventHandle!= INVALID_HANDLE_VALUE) CloseHandle(eventHandle);

        system("pause");
    }
    else cout << "Chanell wasn't connected\n";    
}

bool ConnectToPipe(HANDLE& hPipe, HANDLE& hEvent){
    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\pipename"), PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES, size, size, 0, NULL);
    
    hEvent = CreateEvent(NULL, false, false, NULL);
    OVERLAPPED overlapped = OVERLAPPED();
    bool isConnected = false;
    if (hPipe != INVALID_HANDLE_VALUE && hEvent != INVALID_HANDLE_VALUE){
        overlapped.hEvent = hEvent;
        isConnected = ConnectNamedPipe(hPipe, &overlapped);
        WaitForSingleObject(hEvent, INFINITE);
    }
    return isConnected;
}

bool SendMyMessage(HANDLE& hPipe, HANDLE& hEvent, bool& endFlag){
    std::string message;
    OVERLAPPED overlapped = OVERLAPPED();
    overlapped.hEvent = hEvent;

    cout << "Enter the message:\n";
    std::getline(std::cin, message);
    if (message.length() > size){
        printf("Message is above %d characters\n", size);
        return false;
    }
    if (!strcmp(message.c_str(), "")) endFlag = true;
    return (WriteFile(hPipe, message.c_str(), size, NULL, &overlapped) && WaitForSingleObject(overlapped.hEvent, INFINITE) == WAIT_OBJECT_0);
}