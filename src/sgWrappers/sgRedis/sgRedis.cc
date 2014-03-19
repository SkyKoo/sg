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

SGRedis::SGRedis(std::string host, uint32 port, uint32 timeout) :
    _rc(NULL),
    _error(false)
{
    struct timeval tm = {timeout / 1000, timeout % 1000};
    _rc = redisConnectWithTimeout(host.c_str(), port, tm);
    if (_rc->err)
    {
        LOG_ERROR("redisConnectWithTimeout, host : %s, port : %lu, timeout : %lu, errstr : %s", host.c_str(), port, timeout, _rc->errstr);
        _SGTHROW_FMT(InterfaceCallError, "redisConnectWithTimeout, host : %s, port : %lu, timeout : %lu, errstr : %s", host.c_str(), port, timeout, _rc->errstr);
        _error = true;
    }
    LOG_DEBUG("redisConnectWithTimeout, host : %s, port : %lu, timeout : %lu", host.c_str(), port, timeout);
    LOG_TRACE("SGRedis constructor done!");
}

SGRedis::~SGRedis()
{
    redisFree(_rc);
    LOG_TRACE("SGRedis destructor done!");
}

void SGRedis::select(uint32 index)
{
    freeReplyObject((redisReply *)redisCommand(_rc, "SELECT %lu", index));
}

void SGRedis::prepare_args(const char *cmd, const char **args, std::vector<std::string> keys)
{
    args[0] = cmd;
    for (int i = 0; i < keys.size(); i++)
    {
        args[i + 1] = keys[i].c_str();
    }
}

bool SGRedis::prepare_args_interleaved(const char *cmd, const char **args, std::vector<std::string> keys, std::vector<std::string> vals)
{
    if (keys.size() != vals.size())
    {
        return _error = true;
    }

    args[0] = cmd;
    for (int i = 0; i < keys.size(); i++)
    {
        args[i + 1] = keys[i].c_str();
        args[i + 2] = vals[i].c_str();
    }

    return _error = false;
}

template<> std::string SGRedis::result<std::string>(redisReply *r)
{
    std::string ret;
    if (!check_error(r) && r->str != NULL)
    {
        ret = std::string(r->str);
    }
    freeReplyObject(r);
    return ret;
}

template<> int64 SGRedis::result<int64>(redisReply *r)
{
    int64 ret = 0;
    if (!check_error(r))
    {
        ret = r->integer;
    }
    freeReplyObject(r);
    return ret; 
}

template<> std::vector<std::string> SGRedis::result<std::vector<std::string> >(redisReply *r)
{
    std::vector<std::string> ret;
    if (!check_error(r))
    {
        for (int i = 0; i < r->elements; i++)
        {
            if (r->element[i]->str == NULL)
            {
                ret.push_back(std::string());
            }
            else
            {
                ret.push_back(r->element[i]->str);
            }
        }
    }
    freeReplyObject(r);
    return ret;
}

} // namespace sg
