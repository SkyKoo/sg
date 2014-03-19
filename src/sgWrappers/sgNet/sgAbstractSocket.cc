/*
 * Copyright 2013, Sky Gu. All rights reserved.
 * *
 * * * Licensed under the GNU LESSER GENERAL PUBLIC LICENSE(the "License");
 * * * you may not use this file except in compliance with the License.
 * * * You may obtain a copy of the License at
 * * *
 * * * http://www.gnu.org/licenses/lgpl.html
 * * *
 * * * Unless required by applicable law or agreed to in writing, software
 * * * distributed under the License is distributed on an "AS IS" BASIS,
 * * * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * * * See the License for the specific language governing permissions and
 * * * limitations under the License.
 * * */

//// Author: Sky Gu (skylove_gcm@hotmail.com)
////////
//

#include "sgAbstractSocket.h"
#include "sgException.h"

namespace sg
{

SGAbstractSocket::SGAbstractSocket() :
    _socketfd(-1),
    _isBlocking(true)
{
}

SGAbstractSocket::SGAbstractSocket(int socketfd) :
    _socketfd(socketfd),
    _isBlocking(true)
{
}

SGAbstractSocket::~SGAbstractSocket()
{
}

uint16 SGAbstractSocket::getLocalPort() const
{
    if (-1 != _socketfd)
    {
        sockaddr_in address;
        socklen_t size = sizeof(address);

        if (getsockname(_socketfd, reinterpret_cast<sockaddr *>(&address), &size) == 0)
        {
            return ntohs(address.sin_port);
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "getsockname call error");
            return 0;
        }
    }
    return 0;
}

SGIPv4Address SGAbstractSocket::getLocalAddress() const
{
    if (-1 != _socketfd)
    {
        sockaddr_in address;
        socklen_t size = sizeof(address);

        if (getsockname(_socketfd, reinterpret_cast<sockaddr *>(&address), &size) == 0)
        {
            return SGIPv4Address(ntohl(address.sin_addr.s_addr));
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "getpeernam call error");
            return SGIPv4Address::None;
        }
    }
    return SGIPv4Address::None;
}

uint16 SGAbstractSocket::getRemotePort() const
{
    if (-1 != _socketfd)
    {
        sockaddr_in address;
        socklen_t size = sizeof(address);

        if (getpeername(_socketfd, reinterpret_cast<sockaddr *>(&address), &size) == 0)
        {
            return ntohs(address.sin_port);
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "getpeername call error");
            return 0;
        }
    }
    return 0;
}

SGIPv4Address SGAbstractSocket::getRemoteAddress() const
{
    if (-1 != _socketfd)
    {
        sockaddr_in address;
        socklen_t size = sizeof(address);

        if (getpeername(_socketfd, reinterpret_cast<sockaddr *>(&address), &size) == 0)
        {
            return SGIPv4Address(ntohl(address.sin_addr.s_addr));
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "getpeernam call error");
            return SGIPv4Address::None;
        }
    }
    return SGIPv4Address::None;
}

void SGAbstractSocket::setBlocking(bool b)
{
    int status = fcntl(_socketfd, F_GETFL);

    if (b)
    {
        if (-1 == fcntl(_socketfd, F_SETFL, status & ~O_NONBLOCK))
        {
            _SGTHROW(SyscallExcuteError, "fcntl call error");
        }
    }
    else
    {
        if (-1 == fcntl(_socketfd, F_SETFL, status | O_NONBLOCK))
        {
            _SGTHROW(SyscallExcuteError, "fcntl call error");
        }
    }

    _isBlocking = b;
}

bool SGAbstractSocket::isBlocking()
{
    return _isBlocking;
}

SGAbstractSocket::Status SGAbstractSocket::getStatus()
{
    if ((EAGAIN == errno) || (EINPROGRESS == errno))
    {
        return SGAbstractSocket::NotReady;
    }

    switch (errno)
    {
        case EWOULDBLOCK:
            return SGAbstractSocket::NotReady;
        case ECONNABORTED:
            return SGAbstractSocket::Disconnected;
        case ECONNRESET:
            return SGAbstractSocket::Disconnected;
        case ETIMEDOUT:
            return SGAbstractSocket::Disconnected;
        case ENETRESET:
            return SGAbstractSocket::Disconnected;
        case ENOTCONN:
            return SGAbstractSocket::Disconnected;

        default:
            return SGAbstractSocket::Error;
    };
}

void SGAbstractSocket::close()
{
    if (-1 == ::close(_socketfd))
    {
        _SGTHROW(SyscallExcuteError, "close call error");
    }
}

} // namespace sg
