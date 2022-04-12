#pragma once

#include "SocketFactory.h"
#include "SocketException.h"

namespace net_socket
{
    const int BAD_HANDLE = -1;
}

namespace net_socket
{
    std::unique_ptr<Socket> CreateSocket(int handle, sockaddr *addr, int *addrlen)
    {
        const auto result = accept(handle, addr, (socklen_t *)addrlen);
        
        if (result == BAD_HANDLE)
        {
            throw SocketException(errno);
        }

        return std::make_unique<Socket>(result);
    }

    std::unique_ptr<Socket> CreateSocket(const addrinfo& info)
    {
        return std::make_unique<Socket>(info.ai_family, info.ai_socktype, info.ai_protocol);
    }
}