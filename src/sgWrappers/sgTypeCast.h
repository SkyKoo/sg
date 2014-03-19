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

#ifndef _SG_TYPE_CAST_H_
#define _SG_TYPE_CAST_H_

#include "sgRoot.h"

namespace sg
{

class SGTypeCast : public SGNonCopyable
{
    public:
        static std::string toString(int);

        static std::string toString(char);

        static std::string toString(long);
        
        static std::string toString(float);

        static void toInt(int &value, const std::string &);
};

} // namespace sg

#endif // _SG_TYPE_CAST_H_
