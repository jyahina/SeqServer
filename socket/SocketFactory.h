#pragma once

#include "Socket.h"

#include <memory>

namespace socket
{
    static std::unique_ptr<Socket> CreateSocket(sockaddr *addr = nullptr, int *addrlen = nullptr);
}