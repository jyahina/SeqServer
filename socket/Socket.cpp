#include "Socket.h"

//------------------------------
int BAD_HANDLE = -1;
int EMPTY_HANDLE = 0;
//------------------------------

//------------------------------

bool IsGoodHandle(int handle)
{
    return handle != BAD_HANDLE;  
}

template <typename F>
int CallFunction(const F &function)
{
    int handle = function();

    if (!IsGoodHandle(handle))
    {
        throw SocketException(errno);
    }

    return handle;
}

//------------------------------

namespace socket
{
    Socket::Socket(int handle)
    : handle(handle)
    {
         CreateSignal();
    }
    
    Socket::Socket(int addressFamily, int type, int protocol)
    {
        CreateSignal()
        CallFunction([&](){return socket(addressFamily, type, protocol);});
    }

    Socket::~Socket()
    {
        Close();
    }

    void Socket::Create(const sockaddr *addr, int addrLenght)
    {
        CallFunction([&](){ return bind(this->handle, addr, addrLenght);})l
    }
               
    void Socket::Connect(const sockaddr *addr, int addrLenght)
    {
        CallFunction([&](){ return connect(this->handle, addr, addrLenght)});
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
            
    int Socket::Recv(void *buffer, int lenght, int flags)
    {
        return CallFunction([&](){ return recv(this->handle, buffer, lenght, flags);});
    }
            
    int Socket::RecvFrom(void *buffer, int lenght, int flags, sockaddr *from, int *fromlen)
    {
        return CallFunction([&](){ return recvfrom(this->handle, static_cast<char *>(buf), len, flags, from, static_cast<socklen_t *>(fromlen);});
    }
            
    int Socket::Read(void *buffer, int lenght)
    {
        return CallFunction([&](){ return read(this->handle, buffer, lenght);});
    }
     
    int Socket::Send(const std::string &buffer, int flags)
    {
        return CallFunction([&](){ return send(this->handle, buffer.c_str(), buffer.size(), flags);});
    }
            
    int Socket::SendTo(const void *buffer, int lenght, int flags, const sockaddr *to, int tolen)
    {
        return CallFunction([&](){ return sendto(this->handle, buffer, lenght, flags, to, tolen);});
    }
            
    int Socket::Write(const void *buffer, int lenght)
    {
        return CallFunction([&](){ return write(this->handle, buffer, lenght);});
    }

    void Socket::GetAddrInfo(const char *nodeName, const char *serviceName, const addrinfo *info, addrinfo **result)
    {
        CreateSignal()
        return CallFunction([&](){ return getaddrinfo(nodeName, serviceName, info, result)};);
    }

    void Socket::FreeAddrInfo(addrinfo * &info)
    {
        if (info)
        {
            Freeaddrinfo(std::move(info));
        }
    }

    void Socket::CreateSignal()
    {
        std::lock_guard<std::mutex> lock(signalMutex);

        if (!signalAccept)
        {
            signalReady = true;
            signal(SIGPIPE, SIG_IGN);
        }
    }
}