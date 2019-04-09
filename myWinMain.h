#ifndef MYWINMAIN_H
#define MYWINMAIN_H

using namespace std;
void processButton(HWND hwnd, int myBtnCode){
    char buf[10];
    itoa((myBtnCode-100),buf,10);
    //MessageBox(NULL, buf, "Button", MB_ICONEXCLAMATION | MB_OK);
    char myDirectory[GetCurrentDirectory(0, NULL)+1];
    GetCurrentDirectory(sizeof(myDirectory),myDirectory);
    char myPath[sizeof(myDirectory)+1];
    strcpy(myPath,myDirectory);
    strcat(myPath, "\\");
    strcat(myDirectory,"\\gamesLocation.ini");
    char myProfileString[MAX_PATH];
    string lpAppName = "games_"+string(buf);
    GetPrivateProfileString(lpAppName.c_str(), "gameDir", NULL, myProfileString, sizeof(myProfileString), myDirectory);
    if (strlen(myProfileString) > 0){
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        //char fileOpen[] = "notepad.exe D:\\Users\\Derex\\Documents\\CodeBlocks\\myGamesIcons\\bin\\Debug\\gamesLocation.ini";
        if (!CreateProcessA(myProfileString, NULL, NULL, NULL, 0, 0, NULL, myPath, &si, &pi)){
            DWORD lastErrorCode = GetLastError();
            ostringstream oss;
            oss << "0x" << hex << setw(8) << right << setfill('0') << lastErrorCode;
            switch (lastErrorCode){
                case 0x02:{
                    string erroCode = "Error Code: "+oss.str()+"\nArquivo nao foi encontrado!";
                    LPCSTR codeConvert = erroCode.c_str();
                    MessageBoxA(NULL, codeConvert, "Create Process failed", MB_ICONEXCLAMATION | MB_OK);
                }
                break;
                case 0xc1:{
                    string erroCode = "Error Code: "+oss.str()+"\nArquivo deve ser um executavel!";
                    LPCSTR codeConvert = erroCode.c_str();
                    MessageBoxA(NULL, codeConvert, "Create Process failed", MB_ICONEXCLAMATION | MB_OK);
                }
                break;
                default:
                    string erroCode = "Error Code: "+oss.str();
                    LPCSTR codeConvert = erroCode.c_str();
                    MessageBoxA(NULL, codeConvert, "Create Process failed", MB_ICONEXCLAMATION | MB_OK);
                break;
            }
        }
    }else{
        MessageBoxA(NULL, "Botao Desativado!", "Status Botao", MB_ICONEXCLAMATION | MB_OK);
    }
    SetFocus(hwnd);
    ShowWindow(hwnd, SW_MINIMIZE);
}

void processButtonConfig (){
    char myDirectory[GetCurrentDirectory(0, NULL)];
    GetCurrentDirectory(sizeof(myDirectory),myDirectory);
    char myPath[sizeof(myDirectory)+1];
    strcpy(myPath,myDirectory);
    strcat(myPath, "\\");
    strcat(myDirectory,"\\gamesLocation.ini");
    myDirectory[strlen(myDirectory)] = '\0';
    char myProfileString[MAX_PATH];
    GetPrivateProfileString("Games_0", "index", NULL, myProfileString, sizeof(myProfileString), myDirectory);
    switch(GetLastError()){
        case 0x2:
        {
            char *intChar;
            intChar = (char *)malloc(sizeof(char)+1);
            string lpAppName;
            for(int i = 0; i < 30; i++) {
                itoa(i,intChar,10);
                lpAppName = "games_"+string(intChar);
                WritePrivateProfileString(lpAppName.c_str(), "index", intChar, myDirectory);
                WritePrivateProfileString(lpAppName.c_str(), "gameDir","",myDirectory);
                WritePrivateProfileString(lpAppName.c_str(), "bmpDir","",myDirectory);
                WritePrivateProfileString(lpAppName.c_str(), "gameTitle","\n",myDirectory);
            }
            free(intChar);
            Sleep(1000);
        }
        break;
    }
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    char fileOpen[MAX_PATH] = "notepad.exe ";
    strcat(fileOpen, myDirectory);
    fileOpen[strlen(fileOpen)] = '\0';
    if (!CreateProcessA("C:\\Windows\\System32\\notepad.exe", fileOpen, NULL, NULL, 0, 0, NULL, myPath, &si, &pi))
    {
        DWORD lastErrorCode = GetLastError();
        ostringstream oss;
        oss << "0x" << hex << setw(8) << right << setfill('0') << lastErrorCode;
        LPCSTR codeConvert = oss.str().c_str();
        MessageBoxA(NULL, codeConvert, "Create Process failed", MB_ICONEXCLAMATION | MB_OK);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CTLCOLORSTATIC:
            {
                if(GetWindowLong((HWND)lParam, GWL_ID) >= 100 && GetWindowLong((HWND)lParam, GWL_ID) <= 129) {
                    SetBkMode( (HDC)wParam, TRANSPARENT );
                    SetTextColor((HDC)wParam, RGB(217, 244, 66));
                }
                return (INT_PTR)GetStockObject(NULL_BRUSH);
            }
            break;
        case WM_COMMAND:
            if (wParam >= 100 && wParam <= 129){
                processButton(hwnd, (int)wParam);
            }else if (wParam == BTN_CONFIG){
                processButtonConfig();
            }
           /*switch(wParam){
               case ID_BUTTON1:
                    processButton(hwnd);
                    break;
           }*/
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int myWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow){
    const char g_szClassName[] = "myGames";
    InitCommonControls();
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(MYGAMES_ICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(BACKGROUND_BMP)))/*(HBRUSH)(COLOR_WINDOW+1)*/;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(MYGAMES_ICON));

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW|WS_EX_CLIENTEDGE|WS_EX_COMPOSITED|WS_EX_DLGMODALFRAME|WS_EX_NOINHERITLAYOUT|WS_EX_WINDOWEDGE,
        g_szClassName,
        "myGames",
        WS_CAPTION|WS_BORDER|WS_SYSMENU|WS_MINIMIZEBOX|WS_TILED|WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 650,
        NULL, NULL, hInstance, NULL
    );

    myWindows(hInstance, hwnd);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
#endif // MYWINMAIN_H
