#ifndef MYWINMAIN_H
#define MYWINMAIN_H
#include <iostream>
using namespace std;
void processButton(HWND hwnd, int myStr){
    char buf[10];
    itoa(myStr,buf,10);
    MessageBox(NULL, buf, "Button", MB_ICONEXCLAMATION | MB_OK);
    cout << "myStr: " << buf << endl;
    SetFocus(hwnd);
    //ShowWindow(hwnd, SW_MINIMIZE);
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
                processButton(hwnd, (int)wParam);
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
