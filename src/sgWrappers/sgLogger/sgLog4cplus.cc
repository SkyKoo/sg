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

#include "sgLog4cplus.h"
#include "sgException.h"

#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loggingmacros.h>

namespace sg
{

#define LOG_BUF_SIZE 1024 * 500

#define DO_LOGGER(logLevel, filename, line, format) \
    log4cplus::Logger logger = log4cplus::Logger::getRoot(); \
    \
    if (logger.isEnabledFor(logLevel)) \
    { \
        va_list args; \
        char buf[LOG_BUF_SIZE] = {0}; \
        va_start(args, format); \
        vsnprintf(buf, sizeof(buf), format, args); \
        va_end(args); \
        logger.forcedLog(logLevel, buf, filename, line); \
    } \

SGLog4cplus::SGLog4cplus()
{
}

SGLog4cplus::~SGLog4cplus()
{
    log4cplus::Logger logger = log4cplus::Logger::getRoot();
    LOG4CPLUS_INFO(logger, "Logger System Close Finish.");
}

void SGLog4cplus::init(const char *properties)
{
    if (NULL == properties)
    {
        _SGTHROW(NullPointerError,"NULL == properties");
        return;
    }

    log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
    log4cplus::PropertyConfigurator::doConfigure(properties);
    log4cplus::Logger logger = log4cplus::Logger::getRoot();
    LOG4CPLUS_INFO(logger, "Logger System init Finish.");
}


void SGLog4cplus::close()
{
}

void SGLog4cplus::trace(const char *filename, int line, const char *format, ...)
{
    DO_LOGGER(log4cplus::TRACE_LOG_LEVEL, filename, line, format);
}

void SGLog4cplus::debug(const char *filename, int line, const char *format, ...)
{
    DO_LOGGER(log4cplus::DEBUG_LOG_LEVEL, filename, line, format);
}

void SGLog4cplus::info(const char *filename, int line, const char *format, ...)
{
    DO_LOGGER(log4cplus::INFO_LOG_LEVEL, filename, line, format);
}

void SGLog4cplus::warn(const char *filename, int line, const char *format, ...)
{
    DO_LOGGER(log4cplus::WARN_LOG_LEVEL, filename, line, format);
}

void SGLog4cplus::error(const char *filename, int line, const char *format, ...)
{
    DO_LOGGER(log4cplus::ERROR_LOG_LEVEL, filename, line, format);
}

void SGLog4cplus::fatal(const char *filename, int line, const char *format, ...)
{
    DO_LOGGER(log4cplus::FATAL_LOG_LEVEL, filename, line, format);
}

} // namespace sg
