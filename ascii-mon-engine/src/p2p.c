/*
*	copyright martin hundrup
*/

/*
* p2p.c contains function implementations for p2p.h
*/

#include "../include/ascii-engine.h"
#include "../include/p2p.h"

static HMODULE p2pDll = NULL;

static void (__cdecl *HostFunc)(void) = NULL;
static void (__cdecl *ConnectFunc)(const char*) = NULL;
static void (__cdecl *SendFunc)(const char*) = NULL;
static int  (__cdecl *HasMessageFunc)(void) = NULL;
static char* (__cdecl *GetLastMessageFunc)(void) = NULL;
static char* (__cdecl *GetPublicIPFunc)(void) = NULL;

int P2P_Init(const char* dllPath) {
    p2pDll = LoadLibraryA(dllPath);
    if (!p2pDll) {
        printf("Failed to load %s\n", dllPath);
        return 0;
    }

    HostFunc = (void (__cdecl*)(void)) GetProcAddress(p2pDll, "Host");
    ConnectFunc = (void (__cdecl*)(const char*)) GetProcAddress(p2pDll, "Connect");
    SendFunc = (void (__cdecl*)(const char*)) GetProcAddress(p2pDll, "Send");
    HasMessageFunc = (int (__cdecl*)(void)) GetProcAddress(p2pDll, "HasMessage");
    GetLastMessageFunc = (char* (__cdecl*)(void)) GetProcAddress(p2pDll, "GetLastMessage");
    GetPublicIPFunc = (char* (__cdecl*)(void)) GetProcAddress(p2pDll, "GetPublicIP");

    if (!HostFunc || !ConnectFunc || !SendFunc || !HasMessageFunc || !GetLastMessageFunc || !GetPublicIPFunc) {
        printf("One or more P2P functions not found in DLL\n");
        return 0;
    }

    return 1;
}

void P2P_Host() {
    if (HostFunc) HostFunc();
}

void P2P_Connect(const char* ipAndPort) {
    if (ConnectFunc) ConnectFunc(ipAndPort);
}

void P2P_Send(const char* message) {
    if (SendFunc) SendFunc(message);
}

int P2P_HasMessage() {
    return HasMessageFunc ? HasMessageFunc() : 0;
}

char* P2P_GetLastMessage() {
    return GetLastMessageFunc ? GetLastMessageFunc() : NULL;
}

char* P2P_GetPublicIP() {
    return GetPublicIPFunc ? GetPublicIPFunc() : NULL;
}

int client_test(char* ip) {

    printf("Connecting to %s...\n", ip);
    P2P_Connect(ip);

    Sleep(100); // Give time to connect

    int i = 100;

    while (i-- > 0) {
        P2P_Send("Hello from C!");
        Sleep(100);
    }

    return 0;
}

int server_test() {
   // Host on one machine
    P2P_Host();
    printf("Server listening on %s (clients can connect to this IP)\n", P2P_GetPublicIP());

    Sleep(100); // Give time to connect

    P2P_Send("Hello from C!");

    while (1) {
        if (P2P_HasMessage()) {
            char* msg = P2P_GetLastMessage();
            printf("Got: %s\n", msg);
            free(msg);
        }
        Sleep(100);
    }

    return 0;
}