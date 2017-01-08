#pragma once
#include "pch.h"

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <socket.h>
#endif

class UnifiedSocket
{
public:
    virtual int connect(const sockaddr* name, size_t namelen) = 0;
};