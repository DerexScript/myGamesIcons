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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
    getPath();
    HANDLE m_singleInstanceMutex = CreateMutex(NULL, TRUE, "myGamesSI_IBJRKFYAHE");
    if (m_singleInstanceMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS) {
        HWND existingApp = FindWindowA(0, "myGames");
        if (existingApp){
            ShowWindow(existingApp, SW_RESTORE);
            SetForegroundWindow(existingApp);
        }
        return 0;
    }
    return myWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
