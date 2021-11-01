#include <iostream>
#include <windows.h>
#include <string>
using std::cout;
using std::cin;
using std::endl;

int main(){
    char fileName[50], fileMap[50];
    HANDLE file = NULL, map = NULL;
    LPVOID lpFileMap = NULL;
    std::string data;

    cout << "Enter file name (in English, plez): ";
    cin >> fileName;

    file = CreateFile((LPCTSTR)&fileName[0], GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file == INVALID_HANDLE_VALUE) cout << "Error 0x" << GetLastError() << endl;
    else{
        cout << "Enter file mapping name: ";
        cin >> fileMap;
        map = CreateFileMapping(file, NULL, PAGE_READWRITE, 0, 128, (LPCTSTR)&fileMap[0]);
        lpFileMap = MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (lpFileMap != NULL)
        {
            cout << "\n\nFile projected successfully.\n";
            cout << "Projection's address: " << lpFileMap << endl;
        }
        else cout << "File projection crushed :(\n";

        cout << "Enter data for input: \n> ";
        getchar();
        std::getline(cin, data);

        CopyMemory(lpFileMap, data.c_str(), data.length() * sizeof(char));

        cout << "Data entered.\nNow open reader.exe\nDon't close writer-file\n";
        system("pause");
    }

    if (lpFileMap != NULL && file != NULL) {
        UnmapViewOfFile(lpFileMap);
        CloseHandle(file);
    }
}
