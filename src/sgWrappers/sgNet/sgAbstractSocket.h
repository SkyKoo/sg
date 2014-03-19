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

#ifndef _SG_ABSTRACT_SOCKET_H_
#define _SG_ABSTRACT_SOCKET_H_

#include "sgRoot.h"
#include "sgIPv4Address.h"

namespace sg
{

class SGAbstractSocket : public SGNonCopyable
{
    public:
        enum Status
        {
            /** No socket errors **/
            Done,
            /** Socket not ready **/
            NotReady,
            /** Socket disconnected **/
            Disconnected,
            /** Socket error **/
            Error,
            /** Could not open socket discripter **/
            EOPEN,
            /** Could find host **/
            EHOST,
            /** Could not allocate memory **/
            EMEM,
            /** Http request invalid **/
            InvalidRequest,
            /** Udp datagram too big **/
            UdpDatagramTooBig
        };

        SGAbstractSocket();
        SGAbstractSocket(int socketfd);
        virtual ~SGAbstractSocket();

        uint16 getLocalPort() const;

        SGIPv4Address getLocalAddress() const;

        uint16 getRemotePort() const;

        SGIPv4Address getRemoteAddress() const;

        void setBlocking(bool b);

        bool isBlocking();

        SGAbstractSocket::Status getStatus();

        void close();

    protected:
        int _socketfd;
        Status _status;

    private:
        bool _isBlocking;
};

} // namespace sg

#endif // _SG_ABSTRACT_SOCKET_H_
