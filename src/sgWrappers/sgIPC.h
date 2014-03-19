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

#ifndef _SG_IPC_H_
#define _SG_IPC_H_

#include "sgRoot.h"
#include "sgException.h"

namespace sg
{

namespace ipcdefs
{

enum
{
    MODE_DEFAULT = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)
}; // enum

enum
{
    FLAG_CREATE_EXCL = (O_RDWR | O_CREAT | O_EXCL),
    FLAG_CREATE = (O_RDWR | O_CREAT),
    FLAG_RDWR = O_RDWR,
    FLAG_RD = O_RDONLY,
    FLAG_WR = O_WRONLY
};

enum
{
    PROT_DEFAULT = PROT_READ | PROT_WRITE
};

enum
{
    MMAPFLAG_DEFAULT = MAP_SHARED
};

} // namespace ipcdefs

class SGPosixShm : public SGNonCopyable
{
    public:
        SGPosixShm(const char *name, size_t size, int oflag = ipcdefs::FLAG_CREATE, mode_t mode = ipcdefs::MODE_DEFAULT, int prot = ipcdefs::PROT_DEFAULT, bool autoUnlink = false, bool autoClose = true);
        ~SGPosixShm();

        void ftruncate(off_t length);
        void *get() const;
        const std::string &getName() const;
        void fstat(struct stat *buf);
        void unlink();
        void close();
        
    private:
        std::string _name;
        size_t _size;
        int _fd;
        void *_shm;
        bool _autoUnlink;
        bool _autoClose;
};


class SGSysVShm : public SGNonCopyable
{
    public:
        SGSysVShm(key_t key, size_t size, int flag = IPC_CREAT | ipcdefs::MODE_DEFAULT, bool autoDetach = true, bool autoRemove = false);
        ~SGSysVShm();

        void *getShmAddr() const;

        int detach();

        int remove();

    private:
        key_t _key;
        size_t _size;
        void *_shmAddr;
        int _shmid;
        bool _autoDetach;
        bool _autoRemove;
};

} // namespace sg


#endif // _SG_IPC_H_
