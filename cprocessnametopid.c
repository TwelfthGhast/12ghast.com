#include <Windows.h>
#include <tlhelp32.h>
#include <stdio.h>

int main(void){
    int pid = 0;
    char target[] = "main.exe";

    //Create a snapshot of currently running processes
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //Some error handling in case we failed to get a snapshot of running processes
    if(snap==INVALID_HANDLE_VALUE){
        printf("%s",GetLastError());
    }

    //Declare a PROCESSENTRY32 variable
    PROCESSENTRY32 pe32;
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process and exit if unsuccessful
    if(!Process32First(snap, &pe32) )
    {
        printf("%s",GetLastError());
        CloseHandle(snap);          // clean the snapshot object
    }

    //Cycle through Process List
    do {
        //Uncomment line below if you want your program to spit out every single list
        //printf("%s\t\t\t%d\n",pe32.szExeFile,pe32.th32ProcessID);
        //Comparing two strings containing process names for 'equality'
        if(strcmp(pe32.szExeFile, target)==0) {
            pid = pe32.th32ProcessID;
        }
    } while (Process32Next(snap, &pe32));
    //Clean the snapshot object to prevent resource leakage
    CloseHandle(snap);

    if(pid != 0){
        printf("The process ID of process %s is %d", target, pid);
    } else {
        printf("Process '%s' not found. Exiting¡­", target);
    }
}
