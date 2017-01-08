#include "pch.h"
#include "Class1.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

using namespace UWPBridge;
using namespace Platform;

Class1::Class1()
{
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return;
    }

    struct addrinfo *result = NULL;
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("192.168.2.19", "6667", &hints, &result);

    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return;
    }

    SOCKET connectSocket = INVALID_SOCKET;

    ptr = result;

    connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (connectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    void* addr = &(((struct sockaddr_in*)ptr->ai_addr)->sin_addr);
    char s[INET_ADDRSTRLEN];

    OutputDebugStringA(inet_ntop(ptr->ai_family, addr, s, sizeof(s)));
    iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

    if (iResult == SOCKET_ERROR)
    {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }

    char recvbuf[DEFAULT_BUFLEN];

    do
    {
        iResult = recv(connectSocket, recvbuf, DEFAULT_BUFLEN, 0);

        if (iResult > 0)
        {
            printf("Bytes received: %d\n", iResult);
        }
        else if (iResult == 0)
        {
            printf("Connection closed\n");
        }
        else
        {
            printf("recv failed: %d\n", WSAGetLastError());
        }
    } while (iResult > 0);
}

int 
WindowsSocket::connect(const sockaddr * name, size_t namelen)
{
    return 0;
}
