#include "SocketException.h"

namespace socket
{
    SocketException::SocketException(const char *what)
    : std::runtime_error(what)
    , code(0)
    {}

    SocketException::SocketException(int code)
    : std::runtime_error("Error code:" + std::to_string(code))
    , code(code)
    {} 
}