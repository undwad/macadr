/*
** macadr.cpp by undwad
** crossplatform mac address reader for lua 5.2
** https://github.com/undwad/macadr mailto:undwad@mail.ru
** see copyright notice at the end of this file
*/

#if defined( __SYMBIAN32__ )
#	define SYMBIAN
#elif defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
#	ifndef WIN32
#		define WIN32
#	endif
#elif defined( __APPLE_CC__)
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#		define IOS
#   else
#		define OSX
#   endif
#elif defined(linux) && defined(__arm__)
#	define TEGRA2
#elif defined(__ANDROID__)
#	define ANDROID
#elif defined( __native_client__ )
#	define NATIVECLIENT
#else
#	define LINUX
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "luaM.h"

#if defined(WIN32)
#	include <winsock2.h> 
#	include <iphlpapi.h> 
#	pragma comment(lib, "ws2_32.lib")

	luaM_func_begin(read)
		//luaM_reqd_param(function, callback)
		//lua_rawgeti(L, LUA_REGISTRYINDEX, callback);
		//lua_newtable(L); 
		//int error = lua_pcall(L, 1, 0, 0);
		//luaL_unref(L, LUA_REGISTRYINDEX, callback);
		//if(error)
		//	return lua_error(L);
	luaM_func_end

#elif defined(LINUX)

#   include <unistd.h>

	luaM_func_begin(connect)
		luaM_opt_param(integer, flags, 0)
		luaM_reqd_param(function, callback)
		luaM_return_userdata(context_t, init, context, L, callback, nullptr)
        if(context->poll = avahi_simple_poll_new())
        {
            int error;
            if(context->client = avahi_client_new(avahi_simple_poll_get(context->poll), flags, client_callback, context, &error))
            {
            }
            else
                return luaL_error(L, avahi_strerror(error));
        }
        else
            return luaL_error(L, "avahi_simple_poll_new() failed");
	luaM_func_end

#elif defined(OSX)
#	error incompatible platform
#else
#	error incompatible platform
#endif

static const struct luaL_Reg lib[] =
{
	//{"savestack", luaM_save_stack},
	{"connect", connect},
    {nullptr, nullptr},
};

#define conf0_reg_enum(NAME) \
	lua_newtable(L); \
	conf0_reg_##NAME(L); \
	lua_setfield(L, -2, #NAME);

extern "C"
{
	LUAMOD_API int luaopen_macadr(lua_State *L)
	{
		luaL_newlib (L, lib);
		lua_setglobal(L, "macadr");
		return 1;
	}
}

/******************************************************************************
* Copyright (C) 2013 Undwad, Samara, Russia
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/
