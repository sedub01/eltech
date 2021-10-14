#include <iostream>
#include <windows.h>
#include <bitset>
#define CLS system("cls")
using std::cout;
using std::cin;
using std::endl;
void menu(int& option);
int safe_cin();
void computingSystemInfo();
void statusOfVirtualMemory();
void defineTheStateOfMemoryArea();
void reservationOfTheRegion();

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
                computingSystemInfo();
                break;
            case 2:
                statusOfVirtualMemory();
                break;
            case 3:
                defineTheStateOfMemoryArea();
                break;
            case 4:
                reservationOfTheRegion();
                break;
        }
    }while (LOOP);


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
void computingSystemInfo(){
    SYSTEM_INFO SYSTEM_INFO;
    WORD archType;
    GetSystemInfo(&SYSTEM_INFO);
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

    if (VirtualQuery(address, &info, 64) == 0){
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

void reservationOfTheRegion(){
    int option = -1, allocType = -1, memProtect = -1;
    LPVOID *address;
    while (option < 0 || option > 2){
        cout << "What do you wanna choose?\n";
        cout << "1 - reserve the region in automatic mode\n";
        cout << "2 - reserve the region in the mode enter the address of the beginning of the region\n";
        cout << "Enter your choice: ";
        option = safe_cin();
        CLS;
        if (option < 0 || option > 2) cout << "Wrong option\n";
    }
    if (option == 1) address = nullptr;
    else {
        address = new LPVOID();
        cout << "Enter the required valid address: 0x";
        cin >> std::hex >> *address;
    }
    while (allocType < 0 || allocType > 3){
        cout << "Enter the type of memory allocation: ";
        cout << "1 - MEM_COMMIT\n";
        cout << "2 - MEM_RESERVE\n";
        cout << "3 - MEM_RESET\n";
        cout << "Enter your choice: ";
        allocType = safe_cin();
        CLS;
        if (allocType < 0 || allocType > 3) cout << "Wrong option\n";
    }
    while (memProtect < 0 || memProtect > 10){
        cout << "Enter the memory protection: ";
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
        memProtect = safe_cin();
        CLS;
        if (memProtect < 0 || memProtect > 10) cout << "Wrong option\n";
    }
    if (allocType == 1) allocType = MEM_COMMIT;
    else if (allocType == 2) allocType = MEM_RESERVE;
    else allocType = MEM_RESET;

    if (memProtect == 1) memProtect = PAGE_EXECUTE;
    else if (memProtect == 2) memProtect = PAGE_EXECUTE_READ;
    else if (memProtect == 3) memProtect = PAGE_EXECUTE_READWRITE;
    else if (memProtect == 4) memProtect = PAGE_EXECUTE_WRITECOPY;
    else if (memProtect == 5) memProtect = PAGE_NOACCESS;
    else if (memProtect == 6) memProtect = PAGE_READONLY;
    else if (memProtect == 7) memProtect = PAGE_READWRITE;
    else if (memProtect == 8) memProtect = PAGE_WRITECOPY;
    else if (memProtect == 9) memProtect = PAGE_TARGETS_INVALID;
    else memProtect = PAGE_TARGETS_NO_UPDATE;



    if (address == nullptr) delete address;
}