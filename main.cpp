#include <windows.h>
#include <commctrl.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "resource.h"
#include "myWindows.h"
#include "myWinMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
   return myWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}