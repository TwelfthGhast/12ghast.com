// Overwriting the memory of a dummy program
// Coded by Dennis Ying
// Last updated: 08/05/2019
// Contact: z5163983@unsw.edu.au

#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>

// Prototype functions
int get_pid(char *string);

int main(void) {

    // Change the following values as necessary
    // Process name and memory addresses
    // Integers can directly store hex and decimal
    // To the computer everything is in binary
    char *pid_name = "dummy.exe";
    int adr_number = 0x60ff08;
    int adr_ptr_to_int = 0x60ff04;
    int adr_ptr_to_ptr = 0x60ff00;
    int adr_fixed_string = 0x60fe80;
    int adr_initial_string = 0x60fe6d;
    int adr_string_literal = 0x60fe68;

    // Declaring our buffers
    int buffer_number = 987654321;
    char buffer_fixed[] = "12GHAST.COM IS AWESOME AND THIS STRING IS LONGER THAN OUR PREVIOUS BUT LESS THAN 128";
    char buffer_initial[] = "ShortString";
    char buffer_literal[] = "StRiNgLiTeRaL";

    int pid_dummy = get_pid(pid_name);
    // Exit program if process name not found
    if (!pid_dummy) {
        printf("Process not found...");
        exit(1);
    }

    // Only one HANDLE needed as we are only accessing one program
    HANDLE hProcess = OpenProcess(
        // If you are getting C0000005 errors
        // Try changing line below to PROCESS_ALL_ACCESS
        PROCESS_VM_OPERATION,    // Permission level you are seeking
        FALSE,                   // Do child processes inherit permissions?
        pid_dummy                // ProcessID you are hooking into
    );

    if(hProcess == NULL){
        printf("%s", GetLastError());
    } else {
        printf("Process ID: %d\n\n", pid_dummy);
    }

    // Start writing memory


    BOOL successful = 0;

    // Overwrite integer
    successful = WriteProcessMemory(
        hProcess,
        (LPVOID)adr_number,           // Address we are trying to write to.
        &buffer_number,               // Buffer containing what we are writing
        sizeof(int),                  // Size of things we are writing
        NULL
    );
    if (!successful) {
        printf("An error occurred\n");
        printf("%s", GetLastError());
    }

    // Swapping the values of the pointers
    successful = WriteProcessMemory(
        hProcess,
        (LPVOID)adr_ptr_to_int,       // Address we are trying to write to.
        &adr_ptr_to_ptr,              // Buffer containing what we are writing
        sizeof(int),                  // Size of things we are writing
        NULL
    );
    if (!successful) {
        printf("An error occurred\n");
        printf("%s", GetLastError());
    }

    successful = WriteProcessMemory(
        hProcess,
        (LPVOID)adr_ptr_to_ptr,       // Address we are trying to write to.
        &adr_number,                  // Buffer containing what we are writing
        sizeof(int),                  // Size of things we are writing
        NULL
    );
    if (!successful) {
        printf("An error occurred\n");
        printf("%s", GetLastError());
    }

    // Fixed length char array
    successful = WriteProcessMemory(
        hProcess,
        (LPVOID)adr_fixed_string,     // Address we are trying to write to.
        &buffer_fixed,                // Buffer containing what we are writing
        sizeof(buffer_fixed),         // Size of things we are writing
        NULL
    );
    if (!successful) {
        printf("An error occurred\n");
        printf("%s", GetLastError());
    }

    // Char array defined initially
    successful = WriteProcessMemory(
        hProcess,
        (LPVOID)adr_initial_string,   // Address we are trying to write to.
        &buffer_initial,              // Buffer containing what we are writing
        sizeof(buffer_initial),       // Size of things we are writing
        NULL
    );
    if (!successful) {
        printf("An error occurred\n");
        printf("%s", GetLastError());
    }

    // Modifying string literal will cause dummy program to crash
    /*
    //String Literal
    successful = WriteProcessMemory(
        hProcess,
        (LPVOID)adr_string_literal,   // Address we are trying to write to.
        &buffer_literal,              // Buffer containing what we are writing
        sizeof(buffer_literal),       // Size of things we are writing
        NULL
    );
    if (!successful) {
        printf("An error occurred\n");
        printf("%s", GetLastError());
    }
    */

    return 0;
}

// Input is name of process
// Returns 0 if ProcessID is not found
// Otherwise returns ProcessID
// Modified from:
// https://www.12ghast.com/technology/c-process-name-to-pid/

int get_pid(char *string) {
    int pid = 0;

    // Create a snapshot of currently running processes
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // Some error handling in case we failed to get a snapshot of running processes
    if (snap == INVALID_HANDLE_VALUE) {
        printf("%s", GetLastError());
    }

    // Declare a PROCESSENTRY32 variable
    PROCESSENTRY32 pe32;
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process and exit if unsuccessful
    if (!Process32First(snap, &pe32)) {
        printf("%s", GetLastError());
        CloseHandle(snap);          // clean the snapshot object
    }

    // Cycle through Process List
    do {

        // Uncomment line below if you want your program to spit out every single list
        // printf("%20s\t\t%d\n",pe32.szExeFile, pe32.th32ProcessID);
        // Comparing two strings containing process names for 'equality'
        if (strcmp(pe32.szExeFile, string) == 0) {
            pid = pe32.th32ProcessID;
        }

    } while (Process32Next(snap, &pe32));

    // Clean the snapshot object to prevent resource leakage
    CloseHandle(snap);

    return pid;
}
