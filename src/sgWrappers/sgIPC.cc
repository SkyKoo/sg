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

#include "sgIPC.h"
#include "sgLog4cplus.h"

namespace sg
{

SGPosixShm::SGPosixShm(const char *name, size_t size, int oflag, mode_t mode, int prot, bool autoUnlink, bool autoClose) :
    _name(name),
    _size(size),
    _shm(NULL),
    _autoUnlink(autoUnlink),
    _autoClose(autoClose)
{
    if (_size <= 0)
        _SGTHROW(ValueError, "_size <= 0");

    if (-1 == (_fd = shm_open(_name.c_str(), oflag, mode)))
        _SGTHROW(SyscallExcuteError, "shm_open call error");

    LOG_DEBUG("shm_open, name : %s, fd : %d", _name.c_str(), _fd);

    if (oflag != ipcdefs::FLAG_RD) // Read only can't call frucnate, otherwise will return 22 error
    {
        ftruncate(_size);
        _shm = mmap(NULL, _size, prot, ipcdefs::MMAPFLAG_DEFAULT, _fd, 0);
        if (MAP_FAILED == _shm)
            _SGTHROW(SyscallExcuteError, "mmap call error");
    }
    else
    {
        if (prot & PROT_WRITE)
            prot = prot ^ PROT_WRITE;

        _shm = mmap(NULL, _size, prot, ipcdefs::MMAPFLAG_DEFAULT, _fd, 0);
        if (MAP_FAILED == _shm)
            _SGTHROW(SyscallExcuteError, "mmap call error");
    }
}

SGPosixShm::~SGPosixShm()
{
    if (_autoUnlink)
    {
        if (-1 == shm_unlink(_name.c_str()))
            LOG_ERROR("shm_unlink call error, name : %s", _name.c_str());
    }
    if (_autoClose)
    {
        if (-1 == ::close(_fd))
            LOG_ERROR("close call error, fd : %d", _fd);
    }
}

void SGPosixShm::ftruncate(off_t length)
{
    if (-1 == ::ftruncate(_fd, length))
        _SGTHROW_FMT(SyscallExcuteError, "ftruncate call error, fd : %d, length : %d", _fd, length);
    _size = length;
}

void *SGPosixShm::get() const
{
    return _shm;
}

const std::string &SGPosixShm::getName() const
{
    return _name;
}

void SGPosixShm::fstat(struct stat *buf)
{
    if (-1 == ::fstat(_fd, buf))
        _SGTHROW_FMT(SyscallExcuteError, "fstat call error, fd : %d", _fd);
}

void SGPosixShm::unlink()
{
    if (-1 == shm_unlink(_name.c_str()))
        _SGTHROW_FMT(SyscallExcuteError, "shm_unlink call error, name : %s", _name.c_str());
}

void SGPosixShm::close()
{
    if (-1 == ::close(_fd))
        _SGTHROW_FMT(SyscallExcuteError, "close call error, fd : %d", _fd);
}

//////////////////////////////////////////////////////////////////////////////////////////
// SGSysVShm

SGSysVShm::SGSysVShm(key_t key, size_t size, int flag, bool autoDetach, bool autoRemove) :
    _key(key),
    _size(size),
    _autoDetach(autoDetach),
    _autoRemove(autoRemove)
{
    _shmid = shmget(_key, _size, flag);
    if (-1 ==_shmid)
    {
        _SGTHROW(SyscallExcuteError, "shmget call error");
    }

    _shmAddr = shmat(_shmid, NULL, 0);
    if ((void *)-1 == _shmAddr)
    {
        _SGTHROW(SyscallExcuteError, "shmat call error");
    }
}

SGSysVShm::~SGSysVShm()
{
    if (_autoDetach)
    {
         detach();
    }

    if (_autoRemove)
    {
        remove();
    }
}

void *SGSysVShm::getShmAddr() const
{
    if (NULL == _shmAddr)
    {
        _SGTHROW(NullPointerError, "NULL == _shmAddr");
    }
    if ((void *)-1 == _shmAddr)
    {
        _SGTHROW(ValueError, "(void *)-1 == _shmAddr");
    }
    return _shmAddr;
}

int SGSysVShm::detach()
{
    int ret = shmdt(_shmAddr);
    if (-1 == ret)
    {
        _SGTHROW(SyscallExcuteError, "shmdt call error");
    }
   _shmAddr = NULL;
   return ret;
}

int SGSysVShm::remove()
{
    int ret = shmctl(_shmid, IPC_RMID, NULL);
    if (-1 == ret)
    {
        _SGTHROW(SyscallExcuteError, "shmctl call error");
    }
    return ret;
}

} // namespace sg
