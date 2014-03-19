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

#ifndef _SG_REDIS_H_
#define _SG_REDIS_H_

#include "sgRoot.h"
#include "sgException.h"
#include "sgLog4cplus.h"
#include "hiredis.h"

namespace sg
{

class SGRedis : public SGNonCopyable
{
    public:
        SGRedis(std::string host = "localhost", uint32 port = 6379, uint32 timeout = 1500);
        virtual ~SGRedis();

        void select(uint32 index);

        bool check_error(redisReply *r)
        {
            if (r == NULL)
            {
                _SGTHROW_FMT(Error, "REDIS_ERR : %s", _rc->errstr);
                LOG_ERROR("REDIS_ERR : %s", _rc->errstr);
                return _error = true;
            }
            if (r->type == REDIS_REPLY_ERROR)
            {
                _SGTHROW_FMT(Error, "REDIS_REPLY_ERROR : %s", r->str);
                LOG_ERROR("REDIS_REPLY_ERROR : %s", r->str);
                return _error = true;
            }
            return _error = false;
        }

        template<typename T> T result(redisReply *r)
        {
            return T();
        }

        void prepare_args(const char *cmd, const char **args, std::vector<std::string> keys);
        bool prepare_args_interleaved(const char *cmd, const char **args, std::vector<std::string> keys, std::vector<std::string> vals);

        /*********************************************************** KEYS *********************************************************** */
        /**
         * Delete one key
         */
        int64 del(const std::string &key);
        /**
         * Delete multiple keys
         */
        int64 mdel(const std::vector<std::string> &keys);
        /**
         * Key existed or not
         */
        int64 exists(const std::string &key);
        /**
         * Get all keys which meet the pattern
         */
        std::vector<std::string> keys(const std::string &pattern);
        /**
         * Set the expire time of a key
         */
        int64 expire(const std::string &key, int expire);
        int64 expireat(const std::string &key, uint32 expire);
        int64 pexpire(const std::string &key, int expire);
        int64 pexpireat(const std::string &key, uint64 expire);
        /**
         * Remove expire time from a key
         */
        int64 persist(const std::string &key);
        /**
         * Get the rest time of a key
         */
        int64 ttl(const std::string &key);
        int64 pttl(const std::string &key);
        /**
         * Return a random key
         */
        std::string randomkey();
        /**
         * Rename key
         */
        void rename(const std::string &key, const std::string &newkey);
        /**
         * Rename key when newkey not exists
         */
        int64 renamenx(const std::string &key, const std::string &newkey);
        /**
         * Return key type
         */
        std::string type(const std::string &key);

        /********************************************************* STRINGS ********************************************************** */
        void set(const std::string &key, const std::string &val);
        std::string get(const std::string &key);
        int64 append(const std::string &key, const std::string &val);
        int64 decr(const std::string &key);
        int64 decrby(const std::string &key);
        int64 getbit(const std::string &key, int offset);
        std::string getrange(const std::string &key, int start, int end);
        std::string getset(const std::string &key, const std::string &val);
        int64 incr(const std::string &key);
        int64 incrby(const std::string &key, int val);
        std::string incrbyfloat(const std::string &key, float val);
        std::vector<std::string> mget(const std::vector<std::string> &keys);
        void mset(const std::vector<std::string> &keys, const std::vector<std::string> &vals);
        int64 msetnx(const std::vector<std::string> &keys, const std::vector<std::string> &vals);
        void psetex(const std::string &key, int expire, const std::string &val);
        int64 setbit(const std::string &key, int offset, int val);
        void setex(const std::string &key, int expire, const std::string &val);
        int64 setnx(const std::string &key, const std::string &val);
        int64 setrange(const std::string &key, int start, const std::string &val);
        int64 strlen(const std::string &key);

    private:
        redisContext *_rc;        
        bool _error;
};

} // namespace sg

#endif // _SG_REDIS_H_
