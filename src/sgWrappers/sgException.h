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

#ifndef _SG_EXCEPTION_H_
#define _SG_EXCEPTION_H_

#include "sgRoot.h"

namespace sg
{

#define DEFINECLASS_CHILD_EXCEPTION(ExceptClass, Base) \
        \
        class ExceptClass : public Base \
        { \
            public: \
                ExceptClass(const char *file, int line, const char *func, int errnum, const std::string &msg) throw() : \
                    Base(file, line, func, errnum, msg) \
                { \
                } \
                virtual std::string getClassName() const \
                { \
                    return #ExceptClass; \
                } \
        };

#define _SGTHROW(ExceptClass, msg) \
        { \
            throw ExceptClass(__FILE__, __LINE__, __PRETTY_FUNCTION__, errno, msg); \
        }

#define _SGTHROW_FMT(ExceptClass, format, ...) \
        { \
            char msg[4096] = {0}; \
            snprintf(msg, sizeof(msg), format, __VA_ARGS__); \
            throw ExceptClass(__FILE__, __LINE__, __PRETTY_FUNCTION__, errno, msg); \
        }

class SGBaseException : public std::exception, public SGObject
{
    public:
        SGBaseException(const char *file, int line, const char *func, int errnum, const std::string &msg) throw();
        virtual ~SGBaseException() throw();

        virtual const char *what() const throw();
        
    protected:
        virtual std::string getClassName() const
        {
            return "SGBaseException";
        }

    private:
        const char *_file;
        int _line;
        const char *_func;
        int _errnum;
        std::string _errstr;
        std::string _msg;
        std::string _time;
        mutable std::string _what;
};

// Fatal
DEFINECLASS_CHILD_EXCEPTION(Fatal, SGBaseException);

// Error
DEFINECLASS_CHILD_EXCEPTION(Error, SGBaseException);
DEFINECLASS_CHILD_EXCEPTION(SyscallExcuteError, Error);
DEFINECLASS_CHILD_EXCEPTION(NullPointerError, Error);
DEFINECLASS_CHILD_EXCEPTION(ValueError, Error);
DEFINECLASS_CHILD_EXCEPTION(InterfaceCallError, Error);

// Warning
DEFINECLASS_CHILD_EXCEPTION(Warning, SGBaseException);

// Info
DEFINECLASS_CHILD_EXCEPTION(Info, SGBaseException);



} // namespace sg

#endif // _SG_EXCEPTION_H_
