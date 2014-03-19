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

#include "sgRedis.h"

namespace sg
{
void SGRedis::set(const std::string &key, const std::string &val)
{
    freeReplyObject((redisReply *)redisCommand(_rc, "SET %s %s", key.c_str(), val.c_str()));
}

std::string SGRedis::get(const std::string &key)
{
    return result<std::string>((redisReply *)redisCommand(_rc, "GET %s", key.c_str()));
}

} // namespace sg

