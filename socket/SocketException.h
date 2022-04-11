#pragma once

#include <stdexcept>

namespace socket
{
    class SocketException : public std::runtime_error
    {
        public:
            SocketException(const char *what);
            SocketException(int handle);

        private:
            const int handleError;
    };
}