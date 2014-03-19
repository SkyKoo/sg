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


#ifndef _SG_THREAD_H_
#define _SG_THREAD_H_

#include "sgRoot.h"
#include "sgException.h"

namespace sg
{

class SGThread : public SGNonCopyable
{
    public:
        SGThread();
        virtual ~SGThread();

        void start();

        void join();

        void detach();

        void cancel();

        pthread_t self();

    protected:
        virtual void run() = 0;

    private:
        static void *threadRun(void *arg);
        pthread_t _threadID;
};

} // namespace sg

#endif // _SG_THREAD_H_
