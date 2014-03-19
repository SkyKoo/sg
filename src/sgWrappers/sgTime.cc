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
//

#include "sgTime.h"
#include "sgTypeCast.h"

namespace sg
{

long SGTime::getTimeMilliseconds()
{
    timeval time;
    gettimeofday(&time, 0);
    long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return millis;
}

std::string SGTime::getTimeDate()
{
    time_t lt;
    lt = time(NULL);
    std::string s(ctime(&lt));
    return s;
}

std::string SGTime::getTimeDate(std::string format)
{
    static time_t last;
    static std::string lastresult;
//    static uint j = 0;

    time_t now;
    struct tm *tm;
    now = time(NULL);
    if (last == now)
    {
        //std::cout << "last == now" << j++ << std::endl;
        return lastresult;
    }
    last = now;

    tm = localtime(&now);

    std::string result;
    uint32 i = 0;

    while ( i < format.length())
    {
        switch (format[i])
        {
            case 'd': /* day */
                if (tm->tm_mday < 10)
                    result.append("0");

                result.append(SGTypeCast::toString(tm->tm_mday));
                i += 2;
                break;
            case 'M': /* month */
                if (tm->tm_mon < 9)
                    result.append("0");

                result.append(SGTypeCast::toString(tm->tm_mon + 1));
                i += 2;
                break;
            case 'Y': /* year */
                result.append(SGTypeCast::toString(tm->tm_year + 1900));
                i += 4;
                break;
            case 'H': /* hour */
                if (tm->tm_hour < 10)
                    result.append("0");

                result.append(SGTypeCast::toString(tm->tm_hour));
                i += 2;
                break;
            case 'm': /* minute */
                if (tm->tm_min < 10)
                    result.append("0");

                result.append(SGTypeCast::toString(tm->tm_min));
                i += 2;
                break;
            case 'S': /* sec */
                if (tm->tm_sec < 10)
                    result.append("0");

                result.append(SGTypeCast::toString(tm->tm_sec));
                i += 2;
                break;
                
            default:
                result.append(SGTypeCast::toString(format[i]));
                i += 1;
                break;
        } // switch
    } // while

    lastresult = result;
    return result;
}

} // namespace sg
