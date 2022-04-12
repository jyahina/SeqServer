#include "SocketException.h"

#include <string>

namespace net_socket
{
    SocketException::SocketException(const char *what)
    : std::runtime_error(what)
    , handleError(0)
    {}

    SocketException::SocketException(int handle)
    : std::runtime_error("Error code:" + std::to_string(handle))
    , handleError(handle)
    {} 
}