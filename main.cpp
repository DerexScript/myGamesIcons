#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <windows.h>
#include <commctrl.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "resource.h"
#include "init.h"
#include "myWindows.h"
#include "myWinMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    getPath();
    try{
        HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, "myGamesSI_IBJRKFYAHE");
        if (!hMutex)
            hMutex = CreateMutex(0, 0, "myGamesSI_IBJRKFYAHE");
        else{
            HWND existingApp = FindWindowA(0, "myGames");
            ShowWindow(existingApp, SW_RESTORE);
            SetForegroundWindow(existingApp);
            return 0;
        }
    }catch (...){
        MessageBox(NULL, "Error", "Error", MB_ICONEXCLAMATION|MB_OK);
    }
    return myWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
