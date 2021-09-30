#include <iostream>
#include <stdio.h>
#include <windows.h>

#define CLS system("cls")
using std::cout;
using std::endl;
using std::cin;
void menu(int& option);
int safe_cin();
void getDir(char* dir);
bool isDirectory(LPCSTR folderpath);
bool isFile(LPCSTR strFileName);
void displayListOfDisks();
void displayInfoAboutDisk();
void create_deleteDir();
void createFile();
void copyAndReplaceFiles();
void changeAttributesOfFile();

int main(){
    int option = -1, LOOP = 1;
    do{
        menu(option);
        switch(option){
            case 0:
                cout << "Goodbye" << endl;
                LOOP = 0;
                break;
            case 1:
                displayListOfDisks();
                break;
            case 2:
                displayInfoAboutDisk();
                break;
            case 3:
                create_deleteDir();
                break;
            case 4:
                createFile();
                break;
            case 5:
                copyAndReplaceFiles();
                break;
            case 6:
                changeAttributesOfFile();
                break;
        }
    }while (LOOP);

    return 0;
}

void menu(int& option){
    option = -1;
    while (option < 0 || option > 6){
        cout << "What do you wanna choose?\n";
        cout << "1 - display a list of disks\n";
        cout << "2 - display info about disk\n";
        cout << "3 - create or delete directory\n";
        cout << "4 - create files in new directories\n";
        cout << "5 - copy and move files between directories\n";
        cout << "6 - analize and change atributes of files\n";
        cout << "0 - exit\n";
        cout << "Enter your choice: ";
        option = safe_cin();
        cout << endl;
        CLS;
        if (option < 0 || option > 6) cout << "Wrong option\n";
    }

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

void displayListOfDisks(){
    //A, C, D --> 1101 (справа налево)
    int mask = GetLogicalDrives();
    char disk = 'A';
    cout << "List of disks: ";
    while (mask != 0){
        int bit = mask % 2;
        if (bit) cout << disk << ' ';
        disk++; mask /= 2;
    }
    cout << endl;

    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};
    DWORD dwResult = GetLogicalDriveStrings(dwSize,szLogicalDrives);

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        char* szSingleDrive = szLogicalDrives;
        while(*szSingleDrive)
        {
            printf("Drive: %s\n", szSingleDrive);

            // get the next drive
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
    }
}
void displayInfoAboutDisk(){
    char str[50];
    int choice;
    cout << "Enter needed disk(e.g. Z:\\): ";
    cin >> str;
    choice = GetDriveType(str);
    switch (choice)
    {
    case DRIVE_REMOVABLE:
        cout << "It's floppy disk\n";
        break;
    case DRIVE_FIXED:
        cout << "It's hard drive\n";
        break;
    case DRIVE_REMOTE:
        cout << "It's network drive\n";
        break;
    case DRIVE_CDROM:
        cout << "It's compact disc\n";
        break;
    case DRIVE_RAMDISK:
        cout << "It's RAM disc\n";
        break;
    default:
        cout << "Impossible to find disk\n";
        break;
    }
    char *volName = new char[4];
    strcpy(volName, str);
    DWORD sn, *volSize, maxlen, flags;
    if (choice > 1){
        GetVolumeInformation(str, volName, *volSize, &sn, &maxlen, &flags, NULL, 0);
        cout << "Root Path Name: " << str << endl;
        cout << "Volume Name Buffer: " << volName << endl;
        cout << "Volume Size: " << *volSize << endl;
        cout << "Volume serial number: " << sn << endl;
        cout << "Maximum component length: " << maxlen << endl;
        cout << "File system flag: " << flags << "\n\n";
        
        cout << "System flags: \n";
        if (flags & FILE_CASE_PRESERVED_NAMES) cout << "The specified volume supports preserved case of file names when it places a name on disk.\n";
        if (flags & FILE_CASE_SENSITIVE_SEARCH) cout << "The specified volume supports case-sensitive file names.\n";
        //if (flags & FILE_DAX_VOLUME) cout << "The specified volume is a direct access (DAX) volume.\n";
        if (flags & FILE_FILE_COMPRESSION) cout << "The specified volume supports file-based compression.\n";
        if (flags & FILE_NAMED_STREAMS) cout << "The specified volume supports named streams.\n";
        if (flags & FILE_PERSISTENT_ACLS) cout << "The specified volume preserves and enforces access control lists (ACL).\n";
        if (flags & FILE_READ_ONLY_VOLUME) cout << "The specified volume is read-only.\n";
        if (flags & FILE_SEQUENTIAL_WRITE_ONCE) cout << "The specified volume supports a single sequential write.\n";
        if (flags & FILE_SUPPORTS_ENCRYPTION) cout << "The specified volume supports the Encrypted File System (EFS)\n";
        if (flags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES) cout << "The specified volume supports extended attributes.\n";
        if (flags & FILE_SUPPORTS_HARD_LINKS) cout << "The specified volume supports hard links.\n";
        if (flags & FILE_SUPPORTS_OBJECT_IDS) cout << " The specified volume supports object identifiers.\n";
        if (flags & FILE_SUPPORTS_OPEN_BY_FILE_ID) cout << "The file system supports open by FileID\n";
        if (flags & FILE_SUPPORTS_REPARSE_POINTS) cout << "The specified volume supports reparse points.\n";
        if (flags & FILE_SUPPORTS_SPARSE_FILES) cout << "The specified volume supports sparse files.\n";
        if (flags & FILE_SUPPORTS_TRANSACTIONS) cout << "The specified volume supports transactions.\n";
        if (flags & FILE_SUPPORTS_USN_JOURNAL) cout << "The specified volume supports update sequence number (USN) journals.\n";
        if (flags & FILE_UNICODE_ON_DISK) cout << "The specified volume supports Unicode in file names as they appear on disk.\n";
        if (flags & FILE_VOLUME_IS_COMPRESSED) cout << "The specified volume is a compressed volume, for example, a DoubleSpace volume\n";
        if (flags & FILE_VOLUME_QUOTAS) cout << "The specified volume supports disk quotas.\n";
        //if (flags & FILE_SUPPORTS_BLOCK_REFCOUNTING) cout << "The specified volume supports sharing logical clusters between files on the same volume.\n";
        cout << endl;

        DWORD sectorsPerCluster, bytesPerSector, numberfOfFreeClusters,totalNumberOfClusters;
        GetDiskFreeSpaceA(str, &sectorsPerCluster, &bytesPerSector, &numberfOfFreeClusters, &totalNumberOfClusters);
        //cout << "Root Path Name: " << str << endl;
        cout << "Sectors per cluster: " << sectorsPerCluster << endl;
        cout << "Bytes per sector: " << bytesPerSector << endl;
        cout << "Number of free sectors: " << numberfOfFreeClusters << endl;
        cout << "Total number of clusters: " << totalNumberOfClusters << endl;
    }
    delete[] volName;
}
void create_deleteDir(){
    int choice = -1;
    char str[50];
    while (choice != 1 && choice != 2){
        cout << "What do you want?\n";
        cout << "1 - Create new directory\n";
        cout << "2 - Delete repository\n";
        cout << "Enter your choice: ";
        choice = safe_cin();
        if (choice != 1 && choice != 2)
            cout << "Wrong option!\n";
    }
    if (choice == 1){
        cout << "Enter name of new directory: ";
        cin >> str;
        CreateDirectory(str, NULL);
        cout << "Directory " << str << " created\n";
    }
    else{
        cout << "Enter name of this directory: ";
        cin >> str;
        if (RemoveDirectory(str))
            cout << "Directory " << str << " removed\n";
        else cout << "Directory " << str << " not removed\n";
    }
}
void createFile(){
    char fileName[256], temp[50];
    HANDLE handle;
    
    //надо предупреждать пользователя, что нужно проверить директорию на существование
    cout << "Enter the name of new file(e.g. test.txt or \\\\dir\\\\test.txt(make sure this directory exists)): \n";
    cin >> fileName;
    strcpy(temp, fileName);
    if (fileName[0] == '\\'){
        char* buffer = new char[256];
        GetCurrentDirectory(256, buffer);
        strcat(buffer, fileName);
        strcpy(fileName, buffer);
        delete[] buffer;
    }
    handle = CreateFile(TEXT(fileName), GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
    if (handle == INVALID_HANDLE_VALUE) printf("ERROR 0x%x \nFile not created\n",GetLastError());
    else cout << "File " << temp << " created\n";
    CloseHandle(handle);
}

void copyAndReplaceFiles(){
    char dir1[256], dir2[256], fileName[256], buffer[256], buffer2[256];
    int choice = -1;
    while (choice != 1 && choice != 2){
        cout << "What do you want?\n";
        cout << "1 - copy file\n";
        cout << "2 - move file\n";
        cout << "Enter your choice: ";
        choice = safe_cin();
        if (choice != 1 && choice != 2)
            cout << "Wrong option!\n";
    }
    cout << "Enter first directory: ";
    getDir(dir1); //локальная функция, чтобы не писать дважды
    cout << "Enter file name in this directory: ";
    do{
        cin >> fileName;
        strcpy(buffer, dir1);
        strcat(buffer, "\\");
        strcat(buffer, fileName);
        if (!isFile(buffer))
            cout << "This file doesn't exist\nTry again\n";
    } while (!isFile(buffer));
    cout << "Enter directory to move file in: ";
    getDir(dir2);

    strcpy(buffer2, dir2);
    strcat(buffer2, "\\");
    strcat(buffer2, fileName);
    if (choice == 1) {
        if (!CopyFile(buffer, buffer2, true)) 
            cout << "This file already exists!\nFile haven't been copied\n";
    }
    else {
        if (!MoveFile(buffer, buffer2)) 
            cout << "This file already exists!\nFile haven't been moved\n";;
    }

}
bool isDirectory(LPCSTR folderpath)//char*
{
    DWORD dwFileAttributes = GetFileAttributesA(folderpath);
    if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22)
        return true;
    return false;
}
bool isFile(LPCSTR strFileName){
    DWORD ret = GetFileAttributesA(strFileName);
    return ((ret != INVALID_FILE_ATTRIBUTES) && !(ret & FILE_ATTRIBUTE_DIRECTORY));
}
void getDir(char* dir){
    //char tempdir[256];
    do{
        cin >> dir;
        // GetCurrentDirectory(256, tempdir);
        // strcpy(tempdir, "\\");
        // strcpy(tempdir, dir);
        // вот здесь не знаю, указывать абсолютный или относительный путь
        // поэтому укажу относительный
        if (!isDirectory(dir))
            cout << "This directory doesn't exist\nTry again\n";
    } while (!isDirectory(dir));
}

void changeAttributesOfFile(){
    char fileName[256];
    int choice = -1;
    cout << "Enter the name of file(e.g. test.txt or dir\\\\test.txt(make sure this directory exists)): \n";
    do{
        cin >> fileName;
        if (!isFile(fileName))
            cout << "This file doesn't exist\nTry again\n";
    } while (!isFile(fileName));
    
    while (choice != 1 && choice != 2){
        cout << "What do you want?\n";
        cout << "1 - analize attributes\n";
        cout << "2 - change them\n";
        cout << "Enter your choice: ";
        choice = safe_cin();
        if (choice != 1 && choice != 2)
            cout << "Wrong option!\n";
    }
    if (choice == 1){
        DWORD ret = GetFileAttributesA(fileName);
        printf("File's code attribute is 0x%x\n", ret);
        if (FILE_ATTRIBUTE_ARCHIVE & ret) cout <<    "- Archive file" << endl;
        if (FILE_ATTRIBUTE_COMPRESSED & ret) cout << "- Compressed file" << endl;
        if (FILE_ATTRIBUTE_DIRECTORY & ret) cout <<  "- Catalog" << endl;
        if (FILE_ATTRIBUTE_HIDDEN & ret) cout <<     "- Hidden File" << endl;
        if (FILE_ATTRIBUTE_NORMAL & ret) cout <<     "- File has no attributes" << endl;
        if (FILE_ATTRIBUTE_READONLY & ret) cout <<   "- Readonly file" << endl;
        if (ret & FILE_ATTRIBUTE_DEVICE) cout << "This value is reserved for system use.\n";
    }
    else{
        DWORD ret;
        cout << "Enter code of needed attribute(watch winnt.h)\n0x";
        cin >> std::hex >> ret;
        if (!SetFileAttributesA(fileName, ret))
            cout << "Something went wrong!!!\n";
        else cout << "Attributes updated\n";
    }
}