#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <string>
#include <stdexcept>

namespace socket
{
    class Socket
    {
        public:
            Socket(int handle = 0);
            Socket(int addressFamily, int type, int protocol)

            ~Socket();

            void Create(const sockaddr *addr, int addrLenght);
            void Connect(const sockaddr *addr, int addrLenght);
            void Listen(int log);
            void Close();
            
            int Recv(void *buffer, int lenght, int flags = 0);
            int RecvFrom(void *buffer, int lenght, int flags, sockaddr *from, int *fromlen);
            int Read(void *buffer, int lenght);
            int Send(const std::string &buffer, int flags = 0);
            int SendTo(const void *buffer, int lenght, int flags, const sockaddr *to, int tolen);
            int Write(const void *buffer, int lenght);

            static void GetAddrInfo(const char *nodeName, const char *serviceName, const addrinfo *info, addrinfo **result);
            static void FreeAddrInfo(addrinfo * &info);

        private:
            const int handle;
            bool signalAccept;
            std::mutex signalMutex;

            void CreateSignal();
    };
}
