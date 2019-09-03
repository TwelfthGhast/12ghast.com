#include "main.h"

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            MessageBoxA(0, "DLL has been attached to process.", "DLL Message", MB_OK);
            break;
        case DLL_PROCESS_DETACH:
            // detach from process
            MessageBoxA(0, "DLL has been detached from process.", "DLL Message", MB_OK);
            break;
        case DLL_THREAD_ATTACH:
            // attach to thread
            MessageBoxA(0, "DLL has been attached to thread.", "DLL Message", MB_OK);
            break;
        case DLL_THREAD_DETACH:
            // detach from thread
            MessageBoxA(0, "DLL has been detached from thread.", "DLL Message", MB_OK);
            break;
    }
    return TRUE; // succesful
}
