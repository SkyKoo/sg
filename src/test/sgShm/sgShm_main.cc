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
#include "sgTypeCast.h"
#include "sgTime.h"

using namespace sg;

std::string w_content_a(1024 * 500, 'a');
std::string w_content_b(1024 * 500, 'b');
std::string w_content_c(1024 * 500, 'c');
std::string w_content_d(1024 * 500, 'd');
std::string r_content(1024 * 500, '\0');

void shm_write(const std::string &name)
{
    int i = 0;
    SGPosixShm shm(name.c_str(),1024 * 500); 
    void *mem = shm.get();
    for (i; ; i++)
    {
        long millisec = SGTime::getTimeMilliseconds();
        if (0 == i)
        {
            memcpy(&w_content_a[0], &millisec, sizeof(millisec));
            memcpy(&w_content_a[0] + (w_content_a.size() - sizeof(millisec)), &millisec, sizeof(millisec));
            memcpy(mem, w_content_a.c_str(), w_content_a.size());
            LOG_DEBUG("shm_write : %s", w_content_a.c_str());
        }
        else if (1 == i)
        {
            memcpy(&w_content_b[0], &millisec, sizeof(millisec));
            memcpy(&w_content_b[0] + (w_content_b.size() - sizeof(millisec)), &millisec, sizeof(millisec));
            memcpy(mem, w_content_b.c_str(), w_content_b.size());
            LOG_DEBUG("shm_write : %s", w_content_b.c_str());
        }
        else if (2 == i)
        {
            memcpy(&w_content_c[0], &millisec, sizeof(millisec));
            memcpy(&w_content_c[0] + (w_content_c.size() - sizeof(millisec)), &millisec, sizeof(millisec));
            memcpy(mem, w_content_c.c_str(), w_content_c.size());
            LOG_DEBUG("shm_write : %s", w_content_c.c_str());
        }
        else if (3 == i)
        {
            memcpy(&w_content_d[0], &millisec, sizeof(millisec));
            memcpy(&w_content_d[0] + (w_content_d.size() - sizeof(millisec)), &millisec, sizeof(millisec));
            memcpy(mem, w_content_d.c_str(), w_content_d.size());
            LOG_DEBUG("shm_write : %s", w_content_d.c_str());
        }
        else
        {
            i = 0;
        }
    }
}

void shm_read(const std::string &name)
{
    SGPosixShm shm(name.c_str(), r_content.size(), ipcdefs::FLAG_RD);
    while (true)
    {
        struct stat st;
        bzero(&st, sizeof(st));
        shm.fstat(&st);
        void *mem = shm.get();
        memcpy(&r_content[0], mem, st.st_size);

        long millisecStart, millisecEnd;
        bzero(&millisecStart, sizeof(millisecStart));
        bzero(&millisecEnd, sizeof(millisecEnd));

        memcpy(&millisecStart, &r_content[0], sizeof(millisecStart));
        memcpy(&millisecEnd, &r_content[0] + (r_content.size() - sizeof(millisecEnd)), sizeof(millisecStart));

        if (millisecStart != millisecEnd)
        {
            LOG_DEBUG("shm_read not complete, start : %ld, end : %ld", millisecStart, millisecEnd);
        }
        else
        {
            LOG_DEBUG("shm_read complete, start : %ld, end : %ld", millisecStart, millisecEnd);
        }
        
        // LOG_DEBUG("shm_read : %s", r_content.c_str());
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        std::string name = argv[1];
        std::string mode = argv[2];
        if (mode == "R1")
        {
            g_sgLog4cplus.init("sgLog4cplus_R1.properties");
            LOG_DEBUG("Input name : %s, R mode", name.c_str());
            shm_read(name);
        }
        if (mode == "R2")
        {
            g_sgLog4cplus.init("sgLog4cplus_R2.properties");
            LOG_DEBUG("Input name : %s, R mode", name.c_str());
            shm_read(name);
        }
        else if (mode == "W")
        {
            g_sgLog4cplus.init("sgLog4cplus_W.properties");
            LOG_DEBUG("Input name : %s, W mode", name.c_str());
            shm_write(name);
        }
        else
        {
            LOG_ERROR("Input error");
        }
    }
    else
    {
        std::cout << "Input error" << std::endl;
        std::cout << "Usage : sgShm [name] [mode]" << std::endl;
    }


    std::cout << "Shm test main exit" << std::endl;
    return 0;
}
