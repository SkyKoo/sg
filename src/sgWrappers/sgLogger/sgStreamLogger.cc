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

#include "sgStreamLogger.h"
#include "sgTime.h"
#include "sgTypeCast.h"

namespace sg
{

SGStreamLogger::SGStreamLogger(std::string path)
{
    _out.open(path.c_str(), std::ofstream::app | std::ofstream::out);
}

SGStreamLogger::~SGStreamLogger()
{
    _out << std::endl;
    _out.flush();
    _out.close();
}

std::ofstream &SGStreamLogger::log(std::string type, int indent)
{
    int i = 0;

    while (i < indent)
    {
        _out << "\t";
        i++;
    }

    _out << std::endl << "[" << type << "]" << "[ " << getTimeDate() << "]\t" << getFileNameFromFullPath(__FILE__) << ":" << __LINE__ << "\t" << __FUNCTION__ << "\t";
    return _out;
}

std::string SGStreamLogger::getTimeDate()
{
    return SGTime::getTimeDate("dd/MM/YYYY - HH:mm:SS");
}

} // namespace sg
