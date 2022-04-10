#pragma once

#include "SocketFactory.h"
#include "SocketException.h"

namespace socket
{
    int BAD_HANDLE = -1;
}

namespace socket
{
    std::unique_ptr<Socket> SocketFactory::CreateSocket(sockaddr *addr, int *addrlen)
    {
        const auto handle = accept(handle, addr, (socklen_t *)addrlen);
        
        if (handle == BAD_HANDLE) 
        {
            throw SocketExceptionrror(errno);
        }

        return make_unique<Socket>(handle);
    }
}