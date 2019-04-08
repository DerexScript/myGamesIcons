#ifndef MYWINDOWS_H
#define MYWINDOWS_H
HWND btn[29], textLogo, configBtn;
HWND textBtn[29];
int l = 100;
void myWindows(HINSTANCE hInstance, HWND hwnd){
    textLogo = CreateWindowExA (
        WS_EX_COMPOSITED|WS_EX_NOACTIVATE|WS_EX_NOPARENTNOTIFY,
        "STATIC",
        "",
        WS_CHILD|WS_VISIBLE|SS_BITMAP,
        80, -5, 335, 93,
        hwnd,
        NULL,
        hInstance,
        NULL
    );

    for (int i = 25; i < 475; i+=75){
        for (int i1 = 104; i1 < 520; i1+=96){
            btn[l] = CreateWindowExA (
                   WS_EX_CLIENTEDGE|WS_EX_COMPOSITED,
                   "BUTTON",
                   "ICO",
                   WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON|BS_BITMAP|WS_DISABLED,
                   i, i1, 64, 64,
                   hwnd,
                   (HMENU)l,
                   hInstance,
                   NULL
            );
            SendMessage(btn[l], BM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(BTN_DEFAULT_BMP)));
            ShowWindow(btn[l], SW_HIDE);
            textBtn[l] = CreateWindowExA (
                       WS_EX_COMPOSITED|WS_EX_NOACTIVATE|WS_EX_NOPARENTNOTIFY,
                       "STATIC",
                       "Title",
                       SS_CENTER|WS_CHILD|WS_VISIBLE|WS_DISABLED,
                       (i+16)-(strlen("Title")*1.9), i1+66, strlen("Title")*7.7, 18,
                       hwnd,
                       (HMENU)l,
                       hInstance,
                       NULL
            );
            ShowWindow(textBtn[l], SW_HIDE);
            l++;
        }
    }
    configBtn = CreateWindowExA (
                   WS_EX_CLIENTEDGE|WS_EX_COMPOSITED,
                   "BUTTON",
                   "Configure",
                   WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
                   25, 577, 90, 35,
                   hwnd,
                   (HMENU)BTN_CONFIG,
                   hInstance,
                   NULL
                );
    /*HANDLE bmp_btn1 = LoadImageA(
                          hInstance,
                          "btn1.bmp",
                          IMAGE_BITMAP,
                          LR_DEFAULTSIZE,
                          LR_DEFAULTSIZE,
                          LR_DEFAULTCOLOR|LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE
                      );*/
    //SendMessage(btn[100], BM_SETIMAGE, IMAGE_BITMAP,(LPARAM) bmp_btn1);
    SendMessage(textLogo, STM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(LOGO_BMP)));
    HFONT hFont = CreateFontA(0, 6, 0, 0,
                              0,
                              0, 0, 0,
                              DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS,
                              CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY,
                              DEFAULT_PITCH,
                              "Modern No. 20"
                             );
    SendMessage(textBtn[0], WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
}
#endif // MYWINDOWS_H
