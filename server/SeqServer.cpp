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

const char* IP = "127.0.0.1";
const char* PORT = "1234";
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
    addrinfo hint = GetAddrInfo();
    addrinfo* server = nullptr;
    std::unique_ptr<net_socket::Socket> socket;

    try
    {
        net_socket::Socket::GetAddrInfo(IP, PORT, &hint, &server);

        socket = net_socket::CreateSocket(hint);
        socket->Bind(server->ai_addr, sizeof(addrinfo));
        socket->Listen(LISTEN_TIME_MILLISECONDS);

        while (true) {
            auto clientHandler = new client::ClientHandler(net_socket::CreateSocket(socket->GetHandle()));

            std::thread(&client::ClientHandler::main, clientHandler).detach();
            std::this_thread::sleep_for(std::chrono::microseconds(LISTEN_TIME_MILLISECONDS));
        }
    }
    catch (net_socket::SocketException& e)
    {
        std::cout << "Error from server: " << e.what() << std::endl;

        socket->Close();        

        net_socket::Socket::FreeAddrInfo(server);
        return 1;
    }

    return 0;
}