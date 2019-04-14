#ifndef MYWINDOWS_H
#define MYWINDOWS_H

void setImgBtn(HINSTANCE hInstance, HWND btn, char bmpName[] ){
    HANDLE bmp_btn = LoadImageA(
        hInstance,
        bmpName,
        IMAGE_BITMAP,
        LR_DEFAULTSIZE,
        LR_DEFAULTSIZE,
        LR_DEFAULTCOLOR|LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE
    );
    SendMessage(btn, BM_SETIMAGE, IMAGE_BITMAP,(LPARAM) bmp_btn);
}

HWND btn[35], textLogo, configBtn;
HWND textBtn[35];
int l = 100;
void myWindows(HINSTANCE hInstance, HWND hwnd){
    HICON hIcon = LoadIconA(hInstance,MAKEINTRESOURCE(MYGAMES_ICON));
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON|NIF_TIP|NIF_MESSAGE;
    nid.uCallbackMessage = APPWM_ICONNOTIFY;
    nid.hIcon = hIcon;
    strcpy(nid.szTip, "Games");
    Shell_NotifyIconA(NIM_ADD, &nid);
    textLogo = CreateWindowExA (
        WS_EX_COMPOSITED|WS_EX_NOACTIVATE|WS_EX_NOPARENTNOTIFY,
        "STATIC",
        "",
        WS_CHILD|WS_VISIBLE|SS_BITMAP,
        100, -5, 335, 93,
        hwnd,
        NULL,
        hInstance,
        NULL
    );
    SendMessage(textLogo, STM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(LOGO_BMP)));

    HFONT hFont = CreateFontA(0, 5.8, 0, 0,
                              0,
                              0, 0, 0,
                              DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS,
                              CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY,
                              DEFAULT_PITCH,
                              "Modern No. 20"
    );

    char myProfileString[MAX_PATH];
    char *intChar;
    intChar = (char *)malloc(sizeof(char)+1);
    std::string lpAppName;
    char index[10];
    char gameDir[MAX_PATH];
    char bmpNameBuff[MAX_PATH];
    char gameTitle[50];

    for (int i = 12; i < 463; i+=75){
        for (int i1 = 115; i1 < 500; i1+=96){
            itoa((l-100),intChar,10);
            lpAppName = "games_"+std::string(intChar);

            GetPrivateProfileString(lpAppName.c_str(), "index", NULL, myProfileString, sizeof(myProfileString), dirIniFile);
            strcpy(index,myProfileString);

            GetPrivateProfileString(lpAppName.c_str(), "gameDir", NULL, myProfileString, sizeof(myProfileString), dirIniFile);
            strcpy(gameDir,myProfileString);

            GetPrivateProfileString(lpAppName.c_str(), "bmpDir", NULL, myProfileString, sizeof(myProfileString), dirIniFile);
            strcpy(bmpNameBuff,myProfileString);

            GetPrivateProfileString(lpAppName.c_str(), "gameTitle", NULL, myProfileString, sizeof(myProfileString), dirIniFile);
            strcpy(gameTitle,myProfileString);

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
            SendMessage(textBtn[l], WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
            if (strlen(index) > 0 && strlen(gameDir) > 0 && strlen(bmpNameBuff) >= 0 && strlen(gameTitle) >= 0) {
                EnableWindow(btn[l], TRUE);
                EnableWindow(textBtn[l], TRUE);
                if (strlen(bmpNameBuff) > 0){
                        std::string bmpName = dirExePath;
                        bmpName += "img\\";
                        bmpName += bmpNameBuff;
                        setImgBtn(hInstance, btn[l], (char *)bmpName.c_str());
                }else{
                    SendMessage(btn[l], BM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(BTN_DEFAULT_BMP)));
                }
                if (strlen(gameTitle) >= 8 && strlen(gameTitle) < 10){
                    SetWindowTextA(textBtn[l], gameTitle);
                    MoveWindow(textBtn[l], (i+16)-(strlen(gameTitle)*1.9), i1+66, strlen(gameTitle)*8.3, 18, TRUE);
                }else if (strlen(gameTitle) >= 5 && strlen(gameTitle) <= 7) {
                    SetWindowTextA(textBtn[l], gameTitle);
                    MoveWindow(textBtn[l], (i+16)-(strlen(gameTitle)*1.9), i1+66, strlen(gameTitle)*8.4, 18, TRUE);
                }else if (strlen(gameTitle) >= 1 && strlen(gameTitle) < 5) {
                    SetWindowTextA(textBtn[l], gameTitle);
                }
            }else{
                SendMessage(btn[l], BM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(BTN_DEFAULT_BMP)));
                ShowWindow(btn[l], SW_HIDE);
                ShowWindow(textBtn[l], SW_HIDE);
            }
            l++;
        }
    }
    configBtn = CreateWindowExA (
                   WS_EX_COMPOSITED,
                   "BUTTON",
                   "Configure",
                   WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
                   8, 586, 80, 25,
                   hwnd,
                   (HMENU)BTN_CONFIG,
                   hInstance,
                   NULL
    );
}
#endif // MYWINDOWS_H
