#ifndef MYWINMAIN_H
#define MYWINMAIN_H

using namespace std;
void processButton(HWND hwnd, int myBtnCode){
    char buf[10];
    itoa((myBtnCode-100),buf,10);
    //MessageBox(NULL, buf, "Button", MB_ICONEXCLAMATION | MB_OK);
    char myIniFile[GetCurrentDirectory(0, NULL)+30];
    GetCurrentDirectory(sizeof(myIniFile),myIniFile);
    char myPath[sizeof(myIniFile)+10];
    strcpy(myPath,myIniFile);
    strcat(myPath, "\\");
    strcat(myIniFile,"\\gamesLocation.ini");
    char dirProfileString[MAX_PATH];
    string lpAppName = "games_"+string(buf);
    GetPrivateProfileString(lpAppName.c_str(), "gameDir", NULL, dirProfileString, sizeof(dirProfileString), myIniFile);
    if (strlen(dirProfileString) > 0){
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));
        string::size_type pos = string( dirProfileString ).find_last_of( "\\/" );
        string dirExec = string( dirProfileString ).substr( 0, pos+1);
        if (!CreateProcessA(dirProfileString, NULL, NULL, NULL, 0, 0, NULL, dirExec.c_str(), &si, &pi)){
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
        ShowWindow(hwnd, SW_MINIMIZE);
    }else{
        MessageBoxA(NULL, "Botao Desativado!", "Status Botao", MB_ICONEXCLAMATION | MB_OK);
    }
    SetFocus(hwnd);
}

void processButtonConfig (){
    //definindo array myIniFile e adicionando +30 espaços extras! Pois irei fazer uma concatenação em seguida!
    char myIniFile[GetCurrentDirectory(0, NULL)+30];
    GetCurrentDirectory(sizeof(myIniFile),myIniFile);
    char myPath[strlen(myIniFile)+10];
    strcpy(myPath,myIniFile);
    strcat(myPath, "\\");
    strcat(myIniFile,"\\gamesLocation.ini");
    char myProfileString[10];
    GetPrivateProfileString("Games_0", "index", NULL, myProfileString, sizeof(myProfileString), myIniFile);
    switch(GetLastError()){
        case 0x2:
        {
            char *intChar;
            intChar = (char *)malloc(sizeof(char)+1);
            string lpAppName;
            for(int i = 0; i < 35; i++) {
                itoa(i,intChar,10);
                lpAppName = "games_"+string(intChar);
                WritePrivateProfileString(lpAppName.c_str(), "index", intChar, myIniFile);
                WritePrivateProfileString(lpAppName.c_str(), "gameDir","",myIniFile);
                WritePrivateProfileString(lpAppName.c_str(), "bmpDir","",myIniFile);
                WritePrivateProfileString(lpAppName.c_str(), "gameTitle","\n",myIniFile);
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
    char fileOpen[strlen(myIniFile)+30] = "notepad.exe ";
    strcat(fileOpen, myIniFile);
    //Pegando diretorio do notepad
    char mySystemDir[MAX_PATH];
    GetSystemDirectoryA(mySystemDir, sizeof(mySystemDir));
    strcat(mySystemDir, "\\notepad.exe");
    if (!CreateProcessA(mySystemDir, fileOpen, NULL, NULL, 0, 0, NULL, myPath, &si, &pi))
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
                long idMyStatics = GetWindowLong((HWND)lParam, GWL_ID);
                if(idMyStatics >= 100 && idMyStatics <= 134) {
                    SetBkMode( (HDC)wParam, TRANSPARENT );
                    SetTextColor((HDC)wParam, RGB(217, 244, 66));
                }
                return (INT_PTR)GetStockObject(NULL_BRUSH);
            }
            break;
        case WM_COMMAND:
            if (wParam >= 100 && wParam <= 134){
                processButton(hwnd, (int)wParam);
            }else if (wParam == BTN_CONFIG){
                processButtonConfig();
            }
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
    wc.hbrBackground = CreatePatternBrush((HBITMAP) LoadImageA(hInstance,".//img//background.bmp",
                                                        IMAGE_BITMAP,0,0,
                                                        LR_CREATEDIBSECTION|LR_LOADFROMFILE));
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
        CW_USEDEFAULT, CW_USEDEFAULT, 549, 650,
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
