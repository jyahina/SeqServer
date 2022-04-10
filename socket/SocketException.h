#pragma once

#include <stdexcept>

namespace socket
{
    class SocketException : public std::runtime_error
    {
        public:
            SocketException(const char *what);
            SocketException(int code);

        private:
            const int codeError;
    }
}