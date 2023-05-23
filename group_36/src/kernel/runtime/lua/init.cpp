//
// Created by per on 1/1/23.
//
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

int lua_example(){
    // TODO - This will not work - Our kernel is far from strong enough!
    lua_State* L;

    // initialize Lua
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushstring(L, "0.7");
    lua_setglobal(L, "VERSION");


    //  get number of arguments
    int n = lua_gettop(L);
    double sum = 0;
    int i;

    //  loop through each argument
    for (i = 1; i <= n; i++)
    {
        if (!lua_isnumber(L, i))
        {
            lua_pushstring(L, "Incorrect argument to 'average'");
            lua_error(L);
        }

        // total the arguments
        sum += lua_tonumber(L, i);
    }

    // push the average
    lua_pushnumber(L, sum / n);

    // push the sum
    lua_pushnumber(L, sum);

    //  return the number of results
    return 2;
}

};
