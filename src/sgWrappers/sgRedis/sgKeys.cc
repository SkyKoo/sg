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
int64 SGRedis::del(const std::string &key)
{
    return result<int64>((redisReply *)redisCommand(_rc, "DEL %s", key.c_str()));
}

int64 SGRedis::mdel(const std::vector<std::string> &keys)
{
    char cmd[] = "DEL";
    const char *args[keys.size() + 1];
    prepare_args(cmd, args, keys);

    return result<int64>((redisReply *)redisCommandArgv(_rc, keys.size() + 1, args, NULL));
}

int64 SGRedis::exists(const std::string &key)
{
    return  result<int64>((redisReply *)redisCommand(_rc, "EXISTS %s", key.c_str()));
}

std::vector<std::string> SGRedis::keys(const std::string &pattern)
{
    return result<std::vector<std::string> >((redisReply *)redisCommand(_rc, "KEYS %s", pattern.c_str()));
}

int64 SGRedis::expire(const std::string &key, int expire)
{
    return result<int64>((redisReply *)redisCommand(_rc, "EXPIRE %s %d", key.c_str(), expire));
}

int64 SGRedis::expireat(const std::string &key, uint32 expire)
{
    return result<int64>((redisReply *)redisCommand(_rc, "EXPIREAT %s %u", key.c_str(), expire));
}

int64 SGRedis::pexpire(const std::string &key, int expire)
{
    return result<int64>((redisReply *)redisCommand(_rc, "PEXPIRE %s %d", key.c_str(), expire));
}

int64 SGRedis::pexpireat(const std::string &key, uint64 expire)
{
    return result<int64>((redisReply *)redisCommand(_rc, "PEXPIREAT %s %u", key.c_str(), expire));
}

int64 SGRedis::persist(const std::string &key)
{
    return result<int64>((redisReply *)redisCommand(_rc, "PERSIST %s", key.c_str()));
}

int64 SGRedis::ttl(const std::string &key)
{
    return result<int64>((redisReply *)redisCommand(_rc, "TTL %s", key.c_str()));
}

int64 SGRedis::pttl(const std::string &key)
{
    return result<int64>((redisReply *)redisCommand(_rc, "PTTL %s", key.c_str()));
}

void SGRedis::rename(const std::string &key, const std::string &newkey)
{
    freeReplyObject((redisReply *)redisCommand(_rc, "RENAME %s %s", key.c_str(), newkey.c_str()));
}

int64 SGRedis::renamenx(const std::string &key, const std::string &newkey)
{
    return result<int64>((redisReply *)redisCommand(_rc, "RENAMENX %s %s", key.c_str(), newkey.c_str()));
}

std::string SGRedis::type(const std::string &key)
{
    return result<std::string>((redisReply *)redisCommand(_rc, "TYPE %s", key.c_str()));
}

} // namespace sg
