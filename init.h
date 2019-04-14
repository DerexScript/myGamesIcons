#ifndef INIT_H
#define INIT_H
NOTIFYICONDATA nid = {};
char dirIniFile[MAX_PATH];
char dirExePath[MAX_PATH];
void getPath(){
    char myIniFile[GetCurrentDirectory(0, NULL)+25];
    GetCurrentDirectory(sizeof(myIniFile),myIniFile);
    char myPath[strlen(myIniFile)+10];
    strcpy(myPath,myIniFile);
    strcat(myPath, "\\");
    strcat(myIniFile,"\\gamesLocation.ini");
    strcpy(dirIniFile, myIniFile);
    strcpy(dirExePath, myPath);
}
#endif //INIT_H
