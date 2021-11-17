#define UNICODE
#include <iostream>
#include <windows.h>

using std::cout;
using std::wstring;
int main(){
    STARTUPINFO sti = {0};
    PROCESS_INFORMATION pi = {0};
    DWORD excode;

    wstring applicationName(L"child.exe");
    LPWSTR lpwAppName = &applicationName[0];

    wstring commandLine(L"child.exe");
    LPWSTR lpwCommandLine = &commandLine[0];

    cout << "PARENT PROCESS STARTS\n";
    if (!CreateProcess( NULL, //Имя исполняемого файла
                        lpwCommandLine, // Командая строка
                        NULL, // Указатель на структуру SECURITY_ATTRIBUTES
                        NULL, // Указатель на структуру SECURITY_ATTRIBUTES
                        TRUE, // Флаг наследования дескриптора тек. процесса
                        NULL, // Флаги способов создания процесса
                        NULL, // указатель на блок среды
                        NULL, // Текущий диск или каталог
                        &sti, // Указатель на структуру STARTUPINFO
                        &pi // Указатель на структуру PROCESS_INFORMATION
    )){
        cout << "Unable to generate process\n";
        return -1;
    }

    system("pause");

    GetExitCodeProcess(pi.hProcess, &excode);
    cout << excode << "\n";

    cout << ((excode != STILL_ACTIVE)? "Done\n" : "Process still running\n");

    cout << "PARENT PROCESS ENDS\n";
    system("pause");
}