#include "Socket.h"
#include "SocketException.h"

#include <csignal>
#include <cstring>
#include <cerrno>
#include <unistd.h>

//------------------------------
int BAD_HANDLE = -1;
int EMPTY_HANDLE = 0;
//------------------------------
static bool signalAccept = false;
static std::mutex signalMutex;
//------------------------------

bool IsGoodHandle(int handle)
{
    return handle != BAD_HANDLE;  
}

void CreateSignal()
{
    std::lock_guard<std::mutex> lock(signalMutex);

    if (!signalAccept)
    {
        signalAccept = true;
        signal(SIGPIPE, SIG_IGN);
    }
}

template <typename F>
int CallFunction(const F &function)
{
    int handle = function();

    if (!IsGoodHandle(handle))
    {
        throw net_socket::SocketException(errno);
    }

    return handle;
}

//------------------------------

namespace net_socket
{
    Socket::Socket(int handle)
    : handle(handle)
    {
        CreateSignal();
    }
    
    Socket::Socket(int addressFamily, int type, int protocol)
    {
        CreateSignal();
        CallFunction([&](){ return socket(addressFamily, type, protocol);});
    }

    void Socket::Create(const sockaddr *addr, int addrLenght)
    {
        CallFunction([&](){ return bind(this->handle, addr, addrLenght);});
    }
               
    void Socket::Connect(const sockaddr *addr, int addrLenght)
    {
        CallFunction([&](){ return connect(this->handle, addr, addrLenght);});
    }

    void Socket::Listen(int log)
    {
        CallFunction([&](){ return listen(this->handle, log);});
    }
           
    void Socket::Close()
    {
        CallFunction([&](){ return close(this->handle); });
        this->handle = EMPTY_HANDLE;
    }
            
    int Socket::GetHandle() const
    {
        return this->handle;
    }

    int Socket::Recv(void *buffer, int lenght, int flags)
    {
        return CallFunction([&](){ return recv(this->handle, buffer, lenght, flags);});
    }
     
    int Socket::Send(const std::string &buffer, int flags)
    {
        return CallFunction([&](){ return send(this->handle, buffer.c_str(), buffer.size(), flags);});
    }

    void Socket::GetAddrInfo(const char *nodeName, const char *serviceName, const addrinfo *info, addrinfo **result)
    {
        CreateSignal();
        CallFunction([&]() { return getaddrinfo(nodeName, serviceName, info, result); });
    }

    void Socket::FreeAddrInfo(addrinfo * &info)
    {
        if (info)
        {
            freeaddrinfo(std::move(info));
        }
    }

    bool Socket::IsValid() const
    {
        return IsGoodHandle(this->handle);
    }
}