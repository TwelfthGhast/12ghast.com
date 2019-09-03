#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>

static PROCESSENTRY32 *FindProcess(char* ProcessName);

int InjectDLL(char *LocationDLL, char *VictimProcess) {
    PROCESSENTRY32 *pe32 = FindProcess(VictimProcess);
    if (pe32 == NULL) {
        fprintf(stderr, "Could not find process.\n");
        return 1;
    }
    // Get a handle to process we wish to inject into
    HANDLE inject = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pe32->th32ProcessID);
    if(inject) {
        LPVOID baseAddr = VirtualAllocEx(inject, NULL, strlen(LocationDLL) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (baseAddr) {
            if(! WriteProcessMemory(inject, baseAddr, LocationDLL, strlen(LocationDLL) + 1, NULL)) {
                fprintf(stderr, "Could not write path of DLL into process memory.\n");
                return 1;
            } else {
                // Returns a pointer to the LoadLibrary address.
                // This will be the same on the remote process as in our current process.
                LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
                if(loadLibraryAddress == NULL) {
                    fprintf(stderr, "Could not load library.\n");
                    return 1;
                }
                HANDLE remoteThread = CreateRemoteThread(inject, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddress, baseAddr, 0, NULL);
                if (remoteThread == NULL) {
                    fprintf(stderr, "Could not start remote thread.\n");
                    return 1;
                }
                printf("Injected successfully\n");
                return 0;
            }
        } else {
            fprintf(stderr, "Could not allocate memory in injected process\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Could not inject into running process\n");
        return 1;
    }
}

// Find process by name and return handle
static PROCESSENTRY32 *FindProcess(char* ProcessName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    if(hSnapshot) {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if(Process32First(hSnapshot, &pe32)) {
            do {
                if (! strcmp(pe32.szExeFile, ProcessName)) {
                    break;
                }
            } while(Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }
    if (! strcmp(pe32.szExeFile, ProcessName)) {
        PROCESSENTRY32 *cpy = malloc(sizeof(PROCESSENTRY32));
        *cpy = pe32;
        return cpy;
    } else {
        return NULL;
    }
}

