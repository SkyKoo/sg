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

#ifndef _SG_HEADER_FILE_DEFINATION_H
#define _SG_HEADER_FILE_DEFINATION_H

typedef unsigned char uint8;

typedef unsigned short uint16;

typedef unsigned int uint32;

typedef unsigned long long uint64;

typedef char int8;

typedef short int16;

typedef int int32;

typedef long long int64;

#ifndef ISNULL
#define ISNULL(p) ( NULL == (void *)p )
#endif // ISNULL

#endif // _SG_HEADER_FILE_DEFINATION_H
