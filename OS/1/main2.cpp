#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;
using std::cin;

int callback = 0;
// хэндлы на файлы, учавствующие в операции копирования
HANDLE firstHandle, secondHandle;

// Функция завершения, которая будет вызываться всякий раз при завершении операции ввода-вывода (для ReadFileEx и WriteFileEx)
VOID CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {
    // количество вызовов
    callback++;
}
void ReadFileOverlapped(long long, DWORD, int, OVERLAPPED*, char**);
void WriteFileOverlapped(long long, DWORD, int, OVERLAPPED*, char**);
// Функция асинхронного копирования
void copyFile(DWORD, int);

void menu(int&);
int safe_cin();
bool isFile(LPCSTR strFileName);

int main(){
    int part = 0, operations = 0, sizeToCopy;
    char fileName[256], filePath[256];
    DWORD startTime;

    // Ввод множителя для размера блока
    cout << "Enter the read-write block size(in bytes):\n";
    do {
        cout << "> 4096*";
        part = safe_cin();
        if (part <= 0) cout << "Try again!\n";
    } while (part <= 0);
    //Ввод количества операций
    cout << "Enter number of operations(multiple of two): ";
    do {
        operations = safe_cin();
        if (operations <= 0) cout << "Try again!\n";
    } while (operations <= 0);

    cout << "Enter the name of copied file(e.g. test.txt or dir\\test.txt(make sure the directory exists)): ";
    do{
        //проверяет как по абсолютному, так и по относительному пути
        cin >> fileName;
        if (!isFile(fileName))
            cout << "This file doesn't exist\nTry again\n";
    } while (!isFile(fileName));
    cout << "Enter the path to copy to(e.g. test1.txt or dir1\\test1.txt): ";
    cin >> filePath;

    if (strlen(fileName) < MAX_PATH && strlen(filePath) < MAX_PATH){
        firstHandle = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
        secondHandle = CreateFile(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);

        if (firstHandle != INVALID_HANDLE_VALUE){
            sizeToCopy = 4096 * part;
            startTime = GetTickCount();
            copyFile(sizeToCopy, operations);
            cout << "Copying took " << GetTickCount() - startTime << " milliseconds\n";
        }
        else cout << "Error 0x" << GetLastError() << endl;
    }

    if (!CloseHandle(firstHandle)) cout << "Unable to close first file\n";
    if (!CloseHandle(secondHandle))cout << "Unable to close second file\n";
}

int safe_cin(){
    int choice = -1;
    char str[50];
    cin >> str;
    while (sscanf(str, "%d", &choice) != 1){
        printf("Incorrect input! Try again use only numbers: ");
        cin >> str;
    }
    return choice;
}
bool isFile(LPCSTR strFileName){
    DWORD ret = GetFileAttributesA(strFileName);
    return ((ret != INVALID_FILE_ATTRIBUTES) && !(ret & FILE_ATTRIBUTE_DIRECTORY));
}

void copyFile(DWORD blockSize, int count){
    DWORD high = 0;
    long long fileSize = GetFileSize(firstHandle, &high),
              curSize = fileSize;
    char** buffer = new char*[count];
    OVERLAPPED *over_1 = new OVERLAPPED[count],
               *over_2 = new OVERLAPPED[count];
    
    for (int i=0; i < count; i++){
        buffer[i] = new char[blockSize];

        over_1[i].Offset = over_2[i].Offset = i*blockSize;
        over_1[i].OffsetHigh = over_2[i].OffsetHigh = i*high;
        over_1[i].hEvent = over_2[i].hEvent = NULL;
    }
    do{
        ReadFileOverlapped(fileSize, blockSize, count, over_1, buffer);
        WriteFileOverlapped(fileSize, blockSize, count, over_2, buffer);
        curSize -= (long long)(blockSize*count);
    }while(curSize > 0);

    SetFilePointer(secondHandle, fileSize, NULL, FILE_BEGIN);
    SetEndOfFile(secondHandle);

    for (int i = 0; i < count; i++)
        delete[] buffer[i];
    delete[] buffer;
    delete[] over_1;
    delete[] over_2;
}

void ReadFileOverlapped(long long fileSize, DWORD blockSize, int operationsCount, OVERLAPPED* overlappeds, char** buffer){
    int operations_counter = 0;
    for (int i=0; i<operationsCount; i++)
        if (fileSize>0){
            operations_counter++;
            ReadFileEx(firstHandle, buffer[i], blockSize, &overlappeds[i], FileIOCompletionRoutine);
            fileSize -= blockSize;
        }
    while (callback < operations_counter)
        SleepEx(-1, true);
    for (int i=0; i<operationsCount; i++)
        overlappeds[i].Offset += blockSize*operationsCount;
    callback = 0;
}

void WriteFileOverlapped(long long fileSize, DWORD blockSize, int operationsCount, OVERLAPPED* overlappeds, char** buffer){
    int operations_counter = 0;
    for (int i=0; i<operationsCount; i++)
        if (fileSize>0){
            operations_counter++;
            WriteFileEx(secondHandle, buffer[i], blockSize, &overlappeds[i], FileIOCompletionRoutine);
            fileSize -= blockSize;
        }
    while (callback < operations_counter)
        SleepEx(-1, true);
    for (int i=0; i<operationsCount; i++)
        overlappeds[i].Offset += blockSize*operationsCount;
    callback = 0;
}