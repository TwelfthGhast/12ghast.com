// Reading the memory of a dummy program
// Coded by Dennis Ying
// Last updated: 08/05/2019
// Contact: z5163983@unsw.edu.au

#include <stdio.h>
#include <Windows.h>

int main(void) {

    // Change the following values as necessary
    // Process IDs and memory addresses
    // Integers can directly store hex and decimal
    // To the computer everything is in binary
    int pid_dummy = 20276;
    int adr_number = 0x60ff08;
    int adr_ptr_to_int = 0x60ff04;
    int adr_ptr_to_ptr = 0x60ff00;
    int adr_fixed_string = 0x60fe80;
    int adr_initial_string = 0x60fe6d;
    int adr_string_literal = 0x60fe68;

    // Declaring our buffers
    int buffer_number = 0;
    int *buffer_ptr_to_int;
    int **buffer_ptr_to_ptr;
    char buffer_fixed[128];
    char buffer_initial[128];
    char buffer_literal[128];

    // Only one HANDLE needed as we are only accessing one program
    HANDLE hProcess = OpenProcess(
        PROCESS_VM_READ,    // Permission level you are seeking
        FALSE,              // Do child processes inherit permissions?
        pid_dummy           // ProcessID you are hooking into
    );

    // If we are failing to get a handle
    if(hProcess == NULL){
        printf("%s", GetLastError());
    }

    // Start reading in memory
    // We don't use the BOOL for anything, but theoretically
    // we should use it to check that ReadProcessMemory
    // was successful
    // Removed BOOL for following RPM() calls

    BOOL rpm_number = ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_number,           // Address we are trying to hook.
        &buffer_number,                // Buffer we are writing to
        sizeof(int),                   // Size of things we are reading
        NULL
    );

    // Need to dereference
    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_ptr_to_int,       // Address we are trying to hook.
        &adr_ptr_to_int,               // Buffer we are writing to
        sizeof(int),                   // Size of things we are reading
        NULL
    );

    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_ptr_to_int,       // Address we are trying to hook.
        &buffer_ptr_to_int,            // Buffer we are writing to
        sizeof(int),                   // Size of things we are reading
        NULL
    );

    // Need to dereference twice
    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_ptr_to_ptr,       // Address we are trying to hook.
        &adr_ptr_to_ptr,               // Buffer we are writing to
        sizeof(int),                   // Size of things we are reading
        NULL
    );

    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_ptr_to_ptr,       // Address we are trying to hook.
        &adr_ptr_to_ptr,               // Buffer we are writing to
        sizeof(int),                   // Size of things we are reading
        NULL
    );

    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_ptr_to_ptr,       // Address we are trying to hook.
        &buffer_ptr_to_ptr,            // Buffer we are writing to
        sizeof(int),                   // Size of things we are reading
        NULL
    );

    // Back to normal
    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_fixed_string,     // Address we are trying to hook.
        &buffer_fixed,                 // Buffer we are writing to
        sizeof(buffer_fixed),          // Size of things we are reading
        NULL
    );

    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_initial_string,   // Address we are trying to hook.
        &buffer_initial,               // Buffer we are writing to
        sizeof(buffer_initial),        // Size of things we are reading
        NULL
    );

    // Need to dereference
    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_string_literal,   // Address we are trying to hook.
        &adr_string_literal,           // Buffer we are writing to
        sizeof(adr_string_literal),    // Size of things we are reading
        NULL
    );

    ReadProcessMemory(
        hProcess,
        (LPCVOID)adr_string_literal,   // Address we are trying to hook.
        &buffer_literal,               // Buffer we are writing to
        sizeof(buffer_literal),        // Size of things we are reading
        NULL
    );

    // Print our results
    printf("%d\n", buffer_number);
    printf("%d\n", buffer_ptr_to_int);
    printf("%d\n", buffer_ptr_to_ptr);
    printf("%s\n", buffer_fixed);
    printf("%s\n", buffer_initial);
    printf("%s\n", buffer_literal);

    return 0;
}
