#include "SocketException.h"

#include <string>
#include <cerrno>
#include <cstring>
#include <stdexcept>

namespace net_socket
{
    SocketException::SocketException(const char *what)
    : std::runtime_error(what)
    , handleError(0)
    {}

    SocketException::SocketException(const std::string &what) 
    : std::runtime_error(what)
    , handleError(0) 
    {}

    SocketException::SocketException(int handle)
    : std::runtime_error(std::strerror(handle))
    , handleError(handle)
    {} 
}