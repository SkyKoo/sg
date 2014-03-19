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

#include "sgException.h"

namespace sg
{

SGBaseException::SGBaseException(const char *file, int line, const char *func, int errnum, const std::string &msg) throw() :
    _file(file),
    _line(line),
    _func(func),
    _errnum(errnum),
    _errstr(""),
    _msg(msg),
    _time("")
{
    // Get errstr
    _errstr = strerror(_errnum);

    // Get time
    char buf[64];
    struct tm *tm;
    time_t now;
    time(&now);
    tm = localtime(&now);
    
    snprintf(buf, sizeof(buf), "%04d/%02d/%02d-%02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    _time = buf;
}

SGBaseException::~SGBaseException() throw()
{
}

const char *SGBaseException::what() const throw()
{
    if (_what.empty())
    {
        std::stringstream sstr("");
        sstr << "\n----------------------------------------\n";
        if (_line > 0)
        {
            sstr << "FILE\t= " << _file << std::endl;
            sstr << "LINE\t= " << _line << std::endl;
            sstr << "FUNC\t= " << _func << std::endl;
            sstr << "ERRNO\t= " << _errnum << std::endl;
            sstr << "ERRSTR\t= " << _errstr << std::endl;
        }
        sstr << "CLASS\t= " << getClassName() << std::endl;
        if (_msg.empty())
        {
            sstr << "NO MSG" << std::endl;
        }
        else
        {
            sstr << "MSG\t= " << _msg << std::endl;
        }
        sstr << "TIME\t= " << _time << std::endl;
        sstr << "----------------------------------------";
        _what = sstr.str();
    }
    return _what.c_str();
}

} // namespace sg
