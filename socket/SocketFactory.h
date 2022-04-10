#pragma once

#include "Socket.h"

#include <memory>

namespace socket
{
    class SocketFactory
    {
        static std::unique_ptr<Socket> CreateSocket(sockaddr *addr = nullptr, int *addrlen = nullptr);
    }
}