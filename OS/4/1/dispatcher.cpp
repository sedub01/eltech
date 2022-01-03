#include "consts.hpp"
HANDLE CreateNewProcess(const string&, const string&);

int main(){
    HANDLE writeSemaphores[pageCount],
    readSemaphores[pageCount],
    IOMutex = CreateMutex(NULL, false, mutexName.c_str()),//false->поток не получает права владения мьютексом
    fileHandle = CreateFile(fileName.c_str(), GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0),
    mapFile = CreateFileMapping(fileHandle, NULL, PAGE_READWRITE, 0, pageSize * pageCount, mapName.c_str()),
    processHandles[hProcessCount * 2];
    LPVOID fileView = MapViewOfFile(mapFile, FILE_MAP_ALL_ACCESS, 0, 0, pageSize * pageCount);
    
    cout << "---Start---\n";
    for (int i = 0; i < pageCount; i++){
        string semaphoreName = "writeSemaphore #" + to_string(i);
        writeSemaphores[i] = CreateSemaphore(NULL, 1, 1, semaphoreName.c_str());
        semaphoreName = "readSemaphore #" + to_string(i);
        readSemaphores[i] = CreateSemaphore(NULL, 0, 1, semaphoreName.c_str());
    }
    VirtualLock(fileView, pageSize * pageCount);

    for (int i = 0; i < hProcessCount; i++){
        string logName = "writelogs\\writeLog #" + to_string(i) + ".txt";
        processHandles[i] = CreateNewProcess("writer.exe", logName);
    }

    for (int i = 0; i < hProcessCount; i++){
        string logName = "readlogs\\readLog #" + to_string(i) + ".txt";
        processHandles[i + hProcessCount] = CreateNewProcess("reader.exe", logName);
    }

    cout << "Now wait...\n";
    WaitForMultipleObjects(hProcessCount * 2, processHandles, true, INFINITE);
    cout << "---End---\n";
    
    VirtualUnlock(fileView, pageSize * pageCount);
    UnmapViewOfFile(fileView);
    CloseHandle(IOMutex);
    CloseHandle(mapFile);
    CloseHandle(fileHandle);
    for (int i = 0; i < pageCount; i++){
        CloseHandle(writeSemaphores[i]);
        CloseHandle(readSemaphores[i]);
    }
}

HANDLE CreateNewProcess(const string& exePath, const string& logName){
    SECURITY_ATTRIBUTES securityAttributes = {sizeof(securityAttributes), nullptr, true};

    HANDLE logFileHandle = CreateFile(logName.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE, 
        &securityAttributes, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInformation;

    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInformation, sizeof(processInformation));

    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;
    startupInfo.hStdInput = NULL;
    startupInfo.hStdError = NULL;
    startupInfo.hStdOutput = logFileHandle;

    if (CreateProcess(exePath.c_str(), NULL, NULL, NULL, true, 0, NULL, NULL, &startupInfo, &processInformation))
        return processInformation.hProcess;
    return nullptr;
}