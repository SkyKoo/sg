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

#include "sgMutex.h"

namespace sg
{

SGMutex::SGMutex()
{
    if (0 != pthread_mutex_init(&_mutex, NULL))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutex_init call error");
    }
}

SGMutex::~SGMutex()
{
    if (0 != pthread_mutex_destroy(&_mutex))
    {
        // Should not throw exception in destructor, maybe could write log
    }
}

void SGMutex::lock()
{
    if (0 != pthread_mutex_lock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutex_lock call error");
    }
}

bool SGMutex::tryLock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if (0 != ret)
    {
        if (0 == EBUSY)
        {
            return false;
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "pthread_mutex_trylock call error");
        }
    }
    return true;
}

void SGMutex::unlock()
{
    if (0 != pthread_mutex_unlock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutex_unlock call error");
    }
}

SGRecursiveMutex::SGRecursiveMutex()
{
    pthread_mutexattr_t attr;
    if (0 != pthread_mutexattr_init(&attr))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutexattr_init call error");
    }

    if (0 != pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutexattr_settype call error");
    }

    if (0 != pthread_mutex_init(&_mutex, &attr))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutex_init call error");
    }
}

SGRecursiveMutex::~SGRecursiveMutex()
{
    if (0 != pthread_mutex_destroy(&_mutex))
    {
        // Should not throw exception in destructor, maybe could write log
    }
}

void SGRecursiveMutex::lock()
{
    if (0 != pthread_mutex_lock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutex_lock call error");
    }
}

bool SGRecursiveMutex::tryLock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if (0 != ret)
    {
        if (0 == EBUSY)
        {
            return false;
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "pthread_mutex_trylock call error");
        }
    }
    return true;
}

void SGRecursiveMutex::unlock()
{
    if (0 != pthread_mutex_unlock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_mutex_unlock call error");
    }
}

SGRWMutex::SGRWMutex()
{
    if (0 != pthread_rwlock_init(&_mutex, NULL))
    {
        _SGTHROW(SyscallExcuteError, "pthread_rwlock_init call error");
    }
}

SGRWMutex::~SGRWMutex()
{
    if (0 != pthread_rwlock_destroy(&_mutex))
    {
        // Should not throw exception in destructor, maybe could write log
    }
}

void SGRWMutex::readLock()
{
    if (0 != pthread_rwlock_rdlock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_rwlock_rdlock call error");
    }
}

bool SGRWMutex::tryReadLock()
{
    int ret = pthread_rwlock_tryrdlock(&_mutex);
    if (0 != ret)
    {
        if (EBUSY == ret)
        {
            return false;
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "pthread_rwlock_tryrdlock call error");
        }
    }
    return true;
}

void SGRWMutex::writeLock()
{
    if (0 != pthread_rwlock_wrlock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_rwlock_wrlock call error");
    }
}

bool SGRWMutex::tryWriteLock()
{
    int ret = pthread_rwlock_trywrlock(&_mutex);
    if (0 != ret)
    {
        if (EBUSY == ret)
        {
            return false;
        }
        else
        {
            _SGTHROW(SyscallExcuteError, "pthread_rwlock_trywrlock call error");
        }
    }
    return true;
}

void SGRWMutex::unlock()
{
    if (0 != pthread_rwlock_unlock(&_mutex))
    {
        _SGTHROW(SyscallExcuteError, "pthread_rwlock_unlock call error");
    }
}

} // namespace sg
