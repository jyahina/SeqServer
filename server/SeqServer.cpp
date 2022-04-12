#include "socket/Socket.h"
#include "socket/SocketException.h"
#include "socket/SocketFactory.h"
#include "client/ClientHandler.h"

#include <iostream>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <memory>
#include <string>

//------------------

const char* IP = "127.0.0.0";
const char* PORT = "8080";
const int LISTEN_TIME_MILLISECONDS = 100;
//------------------

addrinfo GetAddrInfo()
{
    addrinfo hint;

    memset(&hint, 0, sizeof(hint));

    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_flags = AI_PASSIVE;

    return hint;
}

int main()
{
    auto hint = GetAddrInfo();
    addrinfo* server = nullptr;
    std::unique_ptr<net_socket::Socket> socket;

    try
    {
        net_socket::Socket::GetAddrInfo(IP, PORT, &hint, &server);
        socket = net_socket::CreateSocket(hint);

        socket->Create(server->ai_addr, sizeof(addrinfo));
        socket->Listen(LISTEN_TIME_MILLISECONDS);

        while (true) {
            std::unique_ptr<net_socket::Socket> client = net_socket::CreateSocket(socket->GetHandle());
            auto handler = std::make_unique<client::ClientHandler>(std::move(client));

            std::thread(&client::ClientHandler::main, handler).detach();
            std::this_thread::sleep_for(std::chrono::microseconds(LISTEN_TIME_MILLISECONDS));
        }
    }
    catch (net_socket::SocketException& e)
    {
        std::cout << e.what() << std::endl;

        if (socket->IsValid())
        {
            socket->Close();
        }

        net_socket::Socket::FreeAddrInfo(server);
        return 1;
    }

    return 0;
}