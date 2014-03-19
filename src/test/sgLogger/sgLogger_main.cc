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

/*#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/fileappender.h>

#include "sgStreamLogger.h"

using namespace log4cplus;
using namespace log4cplus::helpers;

std::string teststr(1024, 'a');
void testLog4cplus()
{
    // SharedAppenderPtr _append(new ConsoleAppender());
    // _append->setName("append test");
    // Logger _logger = Logger::getInstance("test");
    // _logger.addAppender(_append);

    // LOG4CPLUS_DEBUG(_logger, "This is the First log message...");
    // sleep(1);
    // LOG4CPLUS_WARN(_logger, "This is the Second log message...");
    // return 0;

    SharedAppenderPtr _append(new FileAppender("Test.log"));
    _append->setName("file log test");
    Logger _logger = Logger::getInstance("test.subtestof_filelog");
    _logger.addAppender(_append);
    
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);

    int i;
    for (i = 0; i < 1000000; ++i)
    {
        LOG4CPLUS_DEBUG(_logger, teststr.c_str());
    }
    
    gettimeofday(&end, NULL);
    uint32 time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec = start.tv_usec) / 1000;

    std::cout << time << std::endl;
}


void testStreamLogger()
{
    sg::SGStreamLogger l("log.log");


    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    for (int i = 0; i < 1000000; i++)
    {
        l.log("INFO", 0) << teststr;
    }
    gettimeofday(&end, NULL);
    uint32 time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec = start.tv_usec) / 1000;

    std::cout << time << std::endl;

}
*/
#include "sgLog4cplus.h"

using namespace sg;
void testLog4cplusLogger()
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    std::string output(1024, 'a');
    
    g_sgLog4cplus.init("sgLog4cplus.properties");

    int i = 0;
    for (i; i < 10; i++)
    {
        LOG_DEBUG("Debug log[%d]:%s", i, output.c_str());
    }
    gettimeofday(&end, NULL);
    uint32 time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;

    std::cout << time << std::endl;
}

int main(int argc, char *argv[])
{
//    if (argc == 1)
//        testStreamLogger();
//    else
//        testLog4cplus();

    testLog4cplusLogger();
    return 0;
}
