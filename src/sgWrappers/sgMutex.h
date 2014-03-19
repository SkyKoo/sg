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

#include "sgRoot.h"
#include "sgException.h"

namespace sg
{

class SGMutex : public SGNonCopyable
{
    public:
        SGMutex();
        ~SGMutex();

        void lock();
        bool tryLock();
        void unlock();
        pthread_mutex_t & getMutex()
        {
            return _mutex;
        }

    private:
        pthread_mutex_t _mutex;
};

class SGMutexGuard : public SGNonCopyable
{
    public:
        SGMutexGuard(SGMutex *mutex) :
            _mutex(mutex)
        {
            _mutex->lock();
        }

        ~SGMutexGuard()
        {
            _mutex->unlock();
        }

    private:
        SGMutex *_mutex;
};

class SGRecursiveMutex : public SGNonCopyable
{
    public:
        SGRecursiveMutex();
        ~SGRecursiveMutex();

        void lock();
        bool tryLock();
        void unlock();
        pthread_mutex_t & getMutex()
        {
            return _mutex;
        }

    private:
        pthread_mutex_t _mutex;
};

class SGRecursiveMutexGuard : public SGNonCopyable
{
    public:
        SGRecursiveMutexGuard(SGRecursiveMutex *mutex) :
            _mutex(mutex)
        {
            _mutex->lock();
        }

        ~SGRecursiveMutexGuard()
        {
            _mutex->unlock();
        }

    private:
        SGRecursiveMutex *_mutex;
};

class SGRWMutex : public SGNonCopyable
{
    public:
        SGRWMutex();
        ~SGRWMutex();

        void readLock();
        bool tryReadLock();

        void writeLock();
        bool tryWriteLock();

        void unlock();
        pthread_rwlock_t & getMutex()
        {
            return _mutex;
        }

    private:
        pthread_rwlock_t _mutex;
};

class SGReadGuard : public SGNonCopyable
{
    public:
        SGReadGuard(SGRWMutex *mutex) :
            _mutex(mutex)
        {
            _mutex->readLock();
        }
        
        ~SGReadGuard()
        {
            _mutex->unlock();
        }

    private:
        SGRWMutex *_mutex;
};

class SGWriteGuard : public SGNonCopyable
{
    public:
        SGWriteGuard(SGRWMutex *mutex) :
            _mutex(mutex)
        {
            _mutex->writeLock();
        }
        
        ~SGWriteGuard()
        {
            _mutex->unlock();
        }

    private:
        SGRWMutex *_mutex;
};

} // namespace sg
