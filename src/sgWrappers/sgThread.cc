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

#include "sgThread.h"

namespace sg
{

SGThread::SGThread() :
    _threadID(0)
{
}

SGThread::~SGThread()
{
}

void *SGThread::threadRun(void *argc)
{
    reinterpret_cast<SGThread *>(argc)->run();
    return NULL;
}

void SGThread::start()
{
    if (0 != pthread_create(&_threadID, NULL, threadRun, (void *)this))
    {
        _SGTHROW(SyscallExcuteError, "pthread_create call error");
    }
}

void SGThread::join()
{
    if (0 != pthread_join(_threadID, NULL))
    {
        _SGTHROW(SyscallExcuteError, "pthread_join call error");
    }
}

void SGThread::detach()
{
    if (0 != pthread_detach(_threadID))
    {
        _SGTHROW(SyscallExcuteError, "pthread_detach call error");
    }
}

void SGThread::cancel()
{
    if (0 != pthread_cancel(_threadID))
    {
        _SGTHROW(SyscallExcuteError, "pthread_create call error");
    }
}

pthread_t SGThread::self()
{
    return pthread_self();
}

} // namespace sg
