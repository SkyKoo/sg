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

#ifndef _SG_LOG4CPLUS_H_
#define _SG_LOG4CPLUS_H_

#include "sgRoot.h"

namespace sg
{

class SGLog4cplus : public SGNonCopyable
{
    public:
        SGLog4cplus();
        virtual ~SGLog4cplus();

        void init(const char *properties);

        void close();

        void trace(const char *filename, int line, const char *format, ...);

        void debug(const char *filename, int line, const char *format, ...);

        void info(const char *filename, int line, const char *format, ...);

        void warn(const char *filename, int line, const char *format, ...);

        void error(const char *filename, int line, const char *format, ...);

        void fatal(const char *filename, int line, const char *format, ...);

        static inline SGLog4cplus *getSingletonPtr()
        {
            return &getSingleton();
        }

        static inline SGLog4cplus &getSingleton()
        {
            static SGLog4cplus instance;
            return instance;
        }
};

#define g_sgLog4cplus SGLog4cplus::getSingleton()
#define g_psgLog4cplus SGLog4cplus::getSingletonPtr()

#define LOG_TRACE(...) g_sgLog4cplus.trace(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) g_sgLog4cplus.info(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) g_sgLog4cplus.debug(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) g_sgLog4cplus.warn(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) g_sgLog4cplus.error(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) g_sgLog4cplus.fatal(__FILE__, __LINE__, __VA_ARGS__)


} // namespace sg

#endif // _SG_LOG4CPLUS_H_ 
