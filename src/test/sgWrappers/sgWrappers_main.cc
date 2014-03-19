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
#include "sgException.h"
#include "sgIPC.h"
#include "sgGlobalFunWrappers.h"
#include "sgLog4cplus.h"

class TestThread : public sg::SGThread
{
    protected:
        virtual void run()
        {
            int i = 100;

            for (int j = 0; j <= i; j++)
            {
                std::cout << j << " ";
                if (j % 10 == 0)
                    std::cout << std::endl;
            }
        }
};
using namespace sg;

void testSGThread()
{
    TestThread t;
    t.start();
    t.join();
}

void testSGException()
{
    _SGTHROW(Error,"asdfasdf");
}

void testIPCSysVShm(int argc, char *argv[])
{
    std::string mode("");
    if (argc == 2)
    {
        mode = argv[1];
        if (mode == "R")
        {
            std::cout << "Read Mode" << std::endl;
            SGSysVShm shm(12345, 0, 0); // open
            void *shareMemery = shm.getShmAddr();
            char buf[32];
            bzero(buf, sizeof(buf));
            memcpy(buf, shareMemery, sizeof(buf));
            std::cout << "Read content : " << buf << std::endl;
            shm.remove(); // delete shm
        }
    }
    else if (argc == 3)
    {
        mode = argv[1];
        if (mode == "W")
        {
            std::cout << "Write Mode" << std::endl;
            std::string content("");
            content = argv[2];
            std::cout << "Write Content : " << content << std::endl;
            SGSysVShm shm(12345, 1024); // create shm
            void *shareMemery = shm.getShmAddr();
            memcpy(shareMemery, content.c_str(), content.size()); 
            std::cout << "Write End" << std::endl;
        }
    }
    else
    {
        std::cout << "input error, argc : " << argc << std::endl;
    }
}

void testIPCPosixShm(int argc, char *argv[])
{
    std::string name("");
    std::string mode("");
    std::string content(512, '\0');
    if (argc == 3)
    {
        name = argv[1];
        mode = argv[2];
        if (mode == "R")
        {
            std::cout << "Read Mode" << std::endl;
            SGPosixShm shm(name.c_str(),126, ipcdefs::FLAG_RD);
            void *shareMem = shm.get();
            memcpy(&content[0], shareMem, 126);            
        }
        std::cout << "name : " << name << " mode : " << mode << " content : " << content << std::endl;
    }
    else if (argc == 4)
    {
        name = argv[1];
        mode = argv[2];
        content = argv[3];
        if (mode == "W")
        {
            std::cout << "Write Mode" << std::endl;
            SGPosixShm shm(name.c_str(), 512);
            void *shareMem = shm.get();
            memcpy(shareMem, content.c_str(), 512);
        }

        std::cout << "name : " << name << " mode : " << mode << " content : " << content << std::endl;
    }
    else
    {
        std::cout << "inpub error, argc : " << argc << std::endl;
    }
}

int main(int argc, char *argv[])
{
    g_sgLog4cplus.init("sgLog4cplus.properties");
    // testSGThread();
    
    /*try
    {
        testSGException()
    }
    catch (Error e)
    {
        std::cout << "catch exception\n" << e.what() << std::endl;
    }*/

    // testIPCSysVShm(argc, argv);
    //getFileNameFromFullPath(__FILE__);
    try
    {
        testIPCPosixShm(argc, argv);
    }
    catch (Error e)
    {
        std::cout << "catch exception\n" << e.what() << std::endl;
    }
    catch (...)
    {
        //std::cout << "catch exception\n" << e.what() << std::endl;
        std::cout << "catch exception\n" << std::endl;
    }

    std::cout << "main exit" << std::endl;
    return 0;
}
