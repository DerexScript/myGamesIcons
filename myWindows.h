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
    SendMessage(textLogo, STM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(LOGO_BMP)));
    char myDirectory[GetCurrentDirectory(0, NULL)+1];
    GetCurrentDirectory(sizeof(myDirectory),myDirectory);
    strcat(myDirectory,"\\gamesLocation.ini");
    char myProfileString[MAX_PATH];
    char *intChar;
    intChar = (char *)malloc(sizeof(char)+1);
    std::string lpAppName;
    char index[10];
    char gameDir[MAX_PATH];
    char bmpDir[MAX_PATH];
    char gameTitle[50];

    for (int i = 25; i < 475; i+=75){
        for (int i1 = 104; i1 < 520; i1+=96){
            itoa((l-100),intChar,10);
            lpAppName = "games_"+std::string(intChar);

            GetPrivateProfileString(lpAppName.c_str(), "index", NULL, myProfileString, sizeof(myProfileString), myDirectory);
            strcpy(index,myProfileString);

            GetPrivateProfileString(lpAppName.c_str(), "gameDir", NULL, myProfileString, sizeof(myProfileString), myDirectory);
            strcpy(gameDir,myProfileString);

            GetPrivateProfileString(lpAppName.c_str(), "bmpDir", NULL, myProfileString, sizeof(myProfileString), myDirectory);
            strcpy(bmpDir,myProfileString);

            GetPrivateProfileString(lpAppName.c_str(), "gameTitle", NULL, myProfileString, sizeof(myProfileString), myDirectory);
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
            if (strlen(index) > 0 && strlen(gameDir) > 0 && strlen(bmpDir) >= 0 && strlen(gameTitle) >= 0) {
                EnableWindow(btn[l], TRUE);
                EnableWindow(textBtn[l], TRUE);
                if (strlen(bmpDir) > 0){
                        setImgBtn(hInstance, btn[l], bmpDir);
                }else{
                    SendMessage(btn[l], BM_SETIMAGE, IMAGE_BITMAP,(LPARAM) LoadBitmap(hInstance, MAKEINTRESOURCE(BTN_DEFAULT_BMP)));
                }
                if (strlen(gameTitle) >= 8 && strlen(gameTitle) < 10){
                    SetWindowTextA(textBtn[l], gameTitle);
                    if (strlen(gameTitle) > 5) MoveWindow(textBtn[l], (i+16)-(strlen(gameTitle)*1.9), i1+66, strlen(gameTitle)*8.3, 18, TRUE);
                }else if (strlen(gameTitle) >= 1 && strlen(gameTitle) < 8){
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
                   25, 577, 80, 25,
                   hwnd,
                   (HMENU)BTN_CONFIG,
                   hInstance,
                   NULL
    );
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
