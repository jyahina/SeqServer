#pragma once

#include <stdexcept>
#include <string>

namespace net_socket
{
    class SocketException : public std::runtime_error
    {
        public:
            SocketException(const char *what);
            SocketException(const std::string &what);
            SocketException(int handle);

        private:
            const int handleError;
    };
}