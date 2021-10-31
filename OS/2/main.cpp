#include <iostream>
#include <windows.h>
#include <bitset>
#include <cstring>
#define CLS system("cls")
using std::cout;
using std::cin;
using std::endl;
void computingSystemInfo(SYSTEM_INFO&);
void statusOfVirtualMemory();
void defineTheStateOfMemoryArea();
void reservationOfTheRegion(SYSTEM_INFO&);
void reservationOfTheRegion_rc(SYSTEM_INFO&);
void writeData();
void setProtection();
void freeMem();

void menu(int& option);
int safe_cin();
void choose_protection(DWORD&);
void protect_info(const DWORD&);

int main(){
    int option = -1;
    SYSTEM_INFO SYSTEM_INFO;
    GetSystemInfo(&SYSTEM_INFO);
    do{
        menu(option);
        switch(option){
            case 0:
                break;
            case 1:
                computingSystemInfo(SYSTEM_INFO);
                break;
            case 2:
                statusOfVirtualMemory();
                break;
            case 3:
                defineTheStateOfMemoryArea();
                break;
            case 4:
                reservationOfTheRegion(SYSTEM_INFO);
                break;
            case 5:
                reservationOfTheRegion_rc(SYSTEM_INFO);
                break;
            case 6:
                writeData();
                break;
            case 7:
                setProtection();
                break;
            case 8:
                freeMem();
                break;
        }
    }while(option);
    cout << "Goodbye" << endl;

    return 0;
}

void menu(int& option){
    option = -1;
    while (option < 0 || option > 8){
        cout << "What do you wanna choose?\n";
        cout << "1 - get info about computing system\n";
        cout << "2 - define status of virtual memory\n";
        cout << "3 - define the state of memory area by the address adress set from keyboard\n";
        cout << "4 - reservation of the region in automatic mode and in the mode\n"
                "    enter the address of the beginning of the region\n";
        cout << "5 - reservation of the region and transfer of physical memory to it in automatic\n"
                "    mode and in the mode of entering the address of the beginning of the region\n";
        cout << "6 - writing data to memory cells at addresses specified from the keyboard\n";
        cout << "7 - setting access protection for a specified (from the keyboard) memory\n"
        "    region and checking it\n";
        cout << "8 - returning physical memory and freeing the region of the address\n"
        "    space of the specified (from the keyboard) region of memory\n";
        cout << "0 - exit\n";
        cout << "Enter your choice: ";
        option = safe_cin();
        CLS;
        if (option < 0 || option > 8) cout << "Wrong option\n";
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
void computingSystemInfo(SYSTEM_INFO& SYSTEM_INFO){
    WORD archType;

    archType = SYSTEM_INFO.wProcessorArchitecture;
    if (archType == PROCESSOR_ARCHITECTURE_AMD64)
        cout << "x64 (AMD or Intel)";
    else if (archType == PROCESSOR_ARCHITECTURE_ARM)
        cout << "ARM";
    else if (archType == PROCESSOR_ARCHITECTURE_IA64)
        cout << "Intel Itanium-based";
    else if (archType == PROCESSOR_ARCHITECTURE_INTEL)
        cout << "x86";
    else if (archType == PROCESSOR_ARCHITECTURE_UNKNOWN)
        cout << "Unknown";
    cout << " architechture\n";

    cout << "The page size: " << SYSTEM_INFO.dwPageSize << endl;
    cout << "The lowest memory address accessible: " << SYSTEM_INFO.lpMinimumApplicationAddress << endl;
    cout << "The highest memory address accessible: " << SYSTEM_INFO.lpMaximumApplicationAddress << endl;
    cout << "A mask representing the set of processors\n"
    "configured into the system: " << endl << std::bitset<32>(SYSTEM_INFO.dwActiveProcessorMask) << endl;
    cout << "The number of logical processors in the current group: " << SYSTEM_INFO.dwNumberOfProcessors << endl;
    cout << "The granularity for the starting address \nat which virtual memory can be allocated: " 
        << SYSTEM_INFO.dwAllocationGranularity << endl;
    cout << "The architecture-dependent processor level: " << SYSTEM_INFO.wProcessorLevel << endl;
    cout << "The architecture-dependent processor revision: " << SYSTEM_INFO.wProcessorRevision << "\n\n";
    system("pause");
    CLS;
}
void statusOfVirtualMemory(){
    MEMORYSTATUS MEMORYSTATUS;
    GlobalMemoryStatus(&MEMORYSTATUS);
    cout << "The size of the MEMORYSTATUS data structure, in bytes: " << MEMORYSTATUS.dwLength << endl;
    cout << "The approximate percentage of physical memory that is in use: " << MEMORYSTATUS.dwMemoryLoad << endl;
    cout << "The amount of actual physical memory, in bytes: " << MEMORYSTATUS.dwTotalPhys << endl;
    cout << "The amount of physical memory currently available, in bytes: " << MEMORYSTATUS.dwAvailPhys << endl;
    cout << "The current size of the committed memory limit, in bytes: " << MEMORYSTATUS.dwTotalPageFile << endl;
    cout << "The maximum amount of memory the current process can commit, in bytes: " << MEMORYSTATUS.dwAvailPageFile << endl;
    cout << "The size of the user-mode portion of the virtual address space \nof the calling process, in bytes: " << MEMORYSTATUS.dwTotalVirtual << endl;
    cout << "The amount of unreserved and uncommitted memory currently in \n"
    "the user-mode portion of the virtual address \n"
    "space of the calling process, in bytes: " << MEMORYSTATUS.dwAvailVirtual << endl;
    system("pause");
    CLS;
}
void defineTheStateOfMemoryArea(){
    LPVOID address;
    MEMORY_BASIC_INFORMATION info;
    DWORD state, type;

    cout << "Enter the required valid address: 0x";
    cin >> std::hex >> address;

    if (VirtualQuery(address, &info, sizeof(info)) == 0){
        cout << "Error 0x" <<GetLastError() << "\n";
        system("pause");
        CLS;
        return;
    }

    cout << "A pointer to the base address of the region of pages to be queried: " << address << endl;
    cout << "A pointer to the base address of the region of pages: " << info.BaseAddress << endl;
    cout << "A pointer to the base address of a range of pages allocated by the VirtualAlloc function: " << info.AllocationBase << endl;
    cout << "The memory protection option when the region was initially allocated: " <<
        info.AllocationProtect << ((info.AllocationProtect != 0)? "": " (caller does not have access)") << endl;
    cout << "The size of the region beginning at the base address \n"
    "in which all pages have identical attributes, in bytes: " << info.RegionSize << endl;
    state = info.State;
    if (state == MEM_COMMIT)
        cout << "Indicates committed pages for which physical \n"
        "storage has been allocated, either in memory \n"
        "or in the paging file on disk\n";
    else if (state == MEM_FREE)
        cout << "Indicates free pages not accessible to \n"
        "the calling process and available to be allocated\n";
    else if (state == MEM_RESERVE)
        cout << "Indicates reserved pages where a range of the process's \n"
        "virtual address space is reserved without any physical \n"
        "storage being allocated\n";
    else cout << "Unknown state\n";

    cout << "The access protection of the pages in the region: " << info.Protect << endl;
    //именно здесь нужна info_protect(так должна быть какая-нибудь константа)
    protect_info(info.Protect);
    cout << endl;
    cout << "The type of pages in the region\n";
    type = info.Type;
    if (type == MEM_IMAGE)
        cout << "Indicates that the memory pages within the \n"
        "region are mapped into the view of an image section\n";
    else if (type == MEM_MAPPED)
        cout << "Indicates that the memory pages within \n"
        "the region are mapped into the view of a section\n";
    else if (type == MEM_PRIVATE)
        cout << "Indicates that the memory pages within the \n"
        "region are private (that is, not shared by other processes)\n";
    else cout << "Unknown type\n";

    system("pause");
    CLS;
}

//this will with commit
void reservationOfTheRegion(SYSTEM_INFO& SYSTEM_INFO){
    int option = -1;
    void* address = nullptr;
    while (option < 1 || option > 2){
        cout << "What do you wanna choose?\n";
        cout << "1 - reserve the region in automatic mode\n";
        cout << "2 - reserve the region in the mode enter the address of the beginning of the region\n";
        cout << "Enter your choice: ";
        option = safe_cin();
        CLS;
        if (option < 1 || option > 2) cout << "Wrong option\n";
    }
    if (option == 2){
        cout << "Enter the required valid address: 0x";
        cin >> address;
    }

    // разблокировать на случай хз
    // while (memProtect < 0 || memProtect > 10){
    //     cout << "Enter the memory protection:\n";
    //     cout << "1 - PAGE_EXECUTE\n";
    //     cout << "2 - PAGE_EXECUTE_READ\n";
    //     cout << "3 - PAGE_EXECUTE_READWRITE\n";
    //     cout << "4 - PAGE_EXECUTE_WRITECOPY\n";
    //     cout << "5 - PAGE_NOACCESS\n";
    //     cout << "6 - PAGE_READONLY\n";
    //     cout << "7 - PAGE_READWRITE\n";
    //     cout << "8 - PAGE_WRITECOPY\n";
    //     cout << "9 - PAGE_TARGETS_INVALID\n";
    //     cout << "10- PAGE_TARGETS_NO_UPDATE\n";
    //     cout << "Enter your choice: ";
    //     memProtect = safe_cin();
    //     CLS;
    //     if (memProtect < 0 || memProtect > 10) cout << "Wrong option\n";
    // }
    // if (memProtect == 1) memProtect = PAGE_EXECUTE;
    // else if (memProtect == 2) memProtect = PAGE_EXECUTE_READ;
    // else if (memProtect == 3) memProtect = PAGE_EXECUTE_READWRITE;
    // else if (memProtect == 4) memProtect = PAGE_EXECUTE_WRITECOPY;
    // else if (memProtect == 5) memProtect = PAGE_NOACCESS;
    // else if (memProtect == 6) memProtect = PAGE_READONLY;
    // else if (memProtect == 7) memProtect = PAGE_READWRITE;
    // else if (memProtect == 8) memProtect = PAGE_WRITECOPY;
    // else if (memProtect == 9) memProtect = PAGE_TARGETS_INVALID;
    // else memProtect = PAGE_TARGETS_NO_UPDATE;

    address = VirtualAlloc(address, SYSTEM_INFO.dwPageSize, MEM_RESERVE, PAGE_READWRITE);
    if (address){
        if (address = VirtualAlloc(address, SYSTEM_INFO.dwPageSize, MEM_COMMIT, PAGE_READWRITE))
            cout << "Memory area allocated\nAddress: " << address << endl;
        else cout << "Error 0x" << GetLastError() << endl << "Memory hasn't commited";
    }
    else cout << "Error 0x" << GetLastError() << endl << "Memory hasn't reserved\n";
}
//and the next function will be with reserve and commit
void reservationOfTheRegion_rc(SYSTEM_INFO& SYSTEM_INFO){
    int option = -1;
    void* address = nullptr;
    while (option < 1 || option > 2){
        cout << "What do you wanna choose?\n";
        cout << "1 - reserve the region in automatic mode\n";
        cout << "2 - reserve the region in the mode enter the address of the beginning of the region\n";
        cout << "Enter your choice: ";
        option = safe_cin();
        CLS;
        if (option < 1 || option > 2) cout << "Wrong option\n";
    }
    if (option == 2){
        cout << "Enter the required valid address: 0x";
        cin >> address;
    }
    if (address = VirtualAlloc(address, SYSTEM_INFO.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE))
        cout << "Memory area allocated\nAddress: " << address << endl;
    else cout << "Error 0x" << GetLastError() << endl << "Memory hasn't allocated";
}
//use CopyMemory
void writeData(){
    std::string source;
    LPVOID address; //not const
    MEMORY_BASIC_INFORMATION info;
    char* destination;

    cout << "Enter data for input: ";
    getchar();
    std::getline(cin, source);

    cout << "Enter the address of input: 0x";
    cin >> address;

    if(!VirtualQuery(address, &info, 256)){
        cout << "Error 0x" << GetLastError() << "\n";
        system("pause");
        CLS;
        return;
    }
    
    if (info.AllocationProtect && (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READWRITE | PAGE_WRITECOPY)){
        destination = (char*)address;
        CopyMemory(destination, source.c_str(), source.length() * sizeof(char));
        //if not copied --> invalid address
        cout << "Memory area " << address << " filled. Entered data: ";
        for (size_t i = 0; i < source.length(); i++)
            cout << destination[i];
        cout << endl;
    }
    else cout << "Access is denied\n";
}

void setProtection(){
    LPVOID address;
    DWORD newLevel, oldLevel;

    cout << "Enter the address: 0x";
    cin >> address;
    cout << "Choose new protection level:\n";
    choose_protection(newLevel);

    if (VirtualProtect(address, sizeof(DWORD), newLevel, &oldLevel)){
        cout << "Old protection level:\n";
        protect_info(oldLevel);
    }
    else cout << "Error 0x" << GetLastError() << "Access denied\n";
    system("pause");
}

void choose_protection(DWORD& newLevel){
    newLevel = -1;
    while (newLevel < 1 || newLevel > 10){
        //cout << "Enter the memory protection:\n";
        cout << "1 - PAGE_EXECUTE\n";
        cout << "2 - PAGE_EXECUTE_READ\n";
        cout << "3 - PAGE_EXECUTE_READWRITE\n";
        cout << "4 - PAGE_EXECUTE_WRITECOPY\n";
        cout << "5 - PAGE_NOACCESS\n";
        cout << "6 - PAGE_READONLY\n";
        cout << "7 - PAGE_READWRITE\n";
        cout << "8 - PAGE_WRITECOPY\n";
        cout << "9 - PAGE_TARGETS_INVALID\n";
        cout << "10- PAGE_TARGETS_NO_UPDATE\n";
        cout << "Enter your choice: ";
        newLevel = safe_cin();
        CLS;
        if (newLevel < 1 || newLevel > 10) cout << "Wrong option\n";
    }

    if (newLevel == 1) newLevel = PAGE_EXECUTE;
    else if (newLevel == 2) newLevel = PAGE_EXECUTE_READ;
    else if (newLevel == 3) newLevel = PAGE_EXECUTE_READWRITE;
    else if (newLevel == 4) newLevel = PAGE_EXECUTE_WRITECOPY;
    else if (newLevel == 5) newLevel = PAGE_NOACCESS;
    else if (newLevel == 6) newLevel = PAGE_READONLY;
    else if (newLevel == 7) newLevel = PAGE_READWRITE;
    else if (newLevel == 8) newLevel = PAGE_WRITECOPY;
    else if (newLevel == 9) newLevel = PAGE_TARGETS_INVALID;
    else newLevel = PAGE_TARGETS_NO_UPDATE;
}

void protect_info(const DWORD& pro){
    if (pro & PAGE_EXECUTE) cout << "PAGE_EXECUTE\n";
    if (pro & PAGE_EXECUTE_READ) cout << "PAGE_EXECUTE_READ\n";
    if (pro & PAGE_EXECUTE_READWRITE) cout << "PAGE_EXECUTE_READWRITE\n";
    if (pro & PAGE_EXECUTE_WRITECOPY) cout << "PAGE_EXECUTE_WRITECOPY\n";
    if (pro & PAGE_NOACCESS) cout << "PAGE_NOACCESS\n";
    if (pro & PAGE_READONLY) cout << "PAGE_READONLY\n";
    if (pro & PAGE_READWRITE) cout << "PAGE_READWRITE\n";
    if (pro & PAGE_WRITECOPY) cout << "PAGE_WRITECOPY\n";
    if (pro & PAGE_TARGETS_INVALID) cout << "PAGE_TARGETS_INVALID\n";
    if (pro & PAGE_TARGETS_NO_UPDATE) cout << "PAGE_TARGETS_NO_UPDATE\n";
}

void freeMem(){
    LPVOID address;

    cout << "Enter the address: 0x";
    cin >> address;
    if (VirtualFree(address, 0, MEM_RELEASE))
        cout << "Memory area deleted\n";
    else std::cerr << "Error 0x" << GetLastError() << endl;
    system("pause");
}