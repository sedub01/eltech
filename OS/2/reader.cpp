#include <iostream>
#include <windows.h>
using std::cout;
using std::cin;
using std::endl;

int main(){
    char* fileMap = new char[50];
    HANDLE map = NULL;
    LPVOID lpFileMap = NULL;

    cout << "Enter the name of file map: ";
    cin >> fileMap;

    map = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE, FALSE, (LPCTSTR)fileMap);
    if (map == INVALID_HANDLE_VALUE) cout << "Projection creation error\n";
    else{
        lpFileMap = MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if(!lpFileMap){
            cout << "There's nothing in file projection\n";
            system("pause");
            return 2;
        }
        cout << "There is address: " << lpFileMap << "\nThere is projection's data:\n";
        cout << (char*)lpFileMap << endl;
        cout << "This is the end of reader.exe\nClose two programs\n";
        system("pause");
    }
    if (!UnmapViewOfFile(lpFileMap)) cout << "Unable to ummap view of file\n";
    if (!CloseHandle(map)) cout << "Unable to close map file\n";
    delete[] fileMap;
}