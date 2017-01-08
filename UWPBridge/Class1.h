#pragma once

#include "UnifiedSocket.h"

namespace UWPBridge
{
    public ref class Class1 sealed
    {
    public:
        Class1();
    };

    class WindowsSocket : virtual public UnifiedSocket
    {
        // Inherited via UnifiedSocket
        virtual int connect(const sockaddr * name, size_t namelen) override;
    };
}
