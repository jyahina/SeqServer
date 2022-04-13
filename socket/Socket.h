#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <string>
#include <stdexcept>
#include <mutex>

namespace net_socket
{
    class Socket
    {
        public:
            Socket(int sHandle = 0);
            Socket(int addressFamily, int type, int protocol);

            void Bind(const sockaddr *addr, int addrLenght);
            void Connect(const sockaddr *addr, int addrLenght);
            void Listen(int log);
            void Close();
            
            int GetHandle() const;
            int Recv(void *buffer, int lenght, int flags = 0);
            int Send(const std::string &buffer, int flags = 0);
 
            static void GetAddrInfo(const char *nodeName, const char *serviceName, const addrinfo *info, addrinfo **result);
            static void FreeAddrInfo(addrinfo * &info);

            bool IsValid() const;

        private:
            int handle;
            static bool signalAccept;
            static std::mutex signalMutex;

    };
}
