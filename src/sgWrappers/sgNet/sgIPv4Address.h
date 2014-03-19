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


#ifndef _SG_IPV4_ADDRESS_H_
#define _SG_IPV4_ADDRESS_H_

#include "sgRoot.h"

namespace sg
{

class SGIPv4Address : public SGObject
{
    public:
        enum Ip
        {
            Any,
            None
        };

        SGIPv4Address(const std::string &host);
        SGIPv4Address(const char *host);
        SGIPv4Address(const uint8 &byte1, const uint8 &byte2, const uint8 &byte3, const uint8 &byte4);
        SGIPv4Address(uint32 addr);
        SGIPv4Address(Ip addr);

        ~SGIPv4Address();

        void setIp(uint32 addr);

        std::string toString();

        uint32 toInt();

    private:
        in_addr_t _ipAddr;
};

} // namespace sg

#endif // _SG_IPV4_ADDRESS_H_
