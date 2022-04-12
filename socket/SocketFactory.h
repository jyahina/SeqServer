#pragma once

#include <memory>
#include <sys/types.h>
#include <netdb.h>

namespace net_socket
{
    class Socket;
}

namespace net_socket
{
    std::unique_ptr<Socket> CreateSocket(int handle, sockaddr *addr = nullptr, int *addrlen = nullptr);
    std::unique_ptr<Socket> CreateSocket(const addrinfo &info);
}