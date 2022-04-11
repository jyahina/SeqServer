#pragma once

#include "Socket.h"

#include <memory>

namespace socket
{
    static std::unique_ptr<Socket> CreateSocket(int handle, sockaddr *addr = nullptr, int *addrlen = nullptr);
    static std::unique_ptr<Socket> CreateSocket(const addrinfo &info);
}