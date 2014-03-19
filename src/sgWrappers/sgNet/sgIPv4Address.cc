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


#include "sgIPv4Address.h"
#include "sgException.h"

namespace sg
{

SGIPv4Address::SGIPv4Address(const std::string &host)
{
    SGIPv4Address(host.c_str());
}

SGIPv4Address::SGIPv4Address(const char *host)
{
    if (ISNULL(host))
    {
        _SGTHROW(NullPointerError, "SGIPv4Address host");
        _ipAddr = INADDR_NONE;
    }

    if (-1 == inet_pton(AF_INET, host, &_ipAddr))
    {
        _SGTHROW(SyscallExcuteError, "inet_pton call error");
        _ipAddr = INADDR_NONE;
    }
}

SGIPv4Address::SGIPv4Address(const uint8 &byte1, const uint8 &byte2, const uint8 &byte3, const uint8 &byte4)
{
    _ipAddr = htonl((byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4);
}

SGIPv4Address::SGIPv4Address(uint32 addr)
{
    _ipAddr = htonl(addr);
}

SGIPv4Address::SGIPv4Address(Ip addr)
{
    switch (addr)
    {
        case Any:
            _ipAddr = INADDR_ANY;
            break;
        case None:
            _ipAddr = INADDR_NONE;
            break;
    }
}

SGIPv4Address::~SGIPv4Address()
{
}

void SGIPv4Address::setIp(uint32 addr)
{
    _ipAddr = htonl(addr);
}

std::string SGIPv4Address::toString()
{
    char buf[INET_ADDRSTRLEN];
    bzero(buf, INET_ADDRSTRLEN);

    if (NULL == inet_ntop(AF_INET, &_ipAddr, buf, INET_ADDRSTRLEN))
    {
        _SGTHROW(SyscallExcuteError, "inet_ntop call error");
        return "";
    }
    return buf;
}

uint32 SGIPv4Address::toInt()
{
    return ntohl(_ipAddr);
}

} // namespace sg
