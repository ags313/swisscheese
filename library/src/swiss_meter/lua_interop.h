#include <lua.h>
#include <string>

static std::string extractStringFromNamedField(lua_State *LUA, int idx, const char *field) {
    lua_getfield(LUA, idx, field);
    size_t len = 0;
    const char *result = lua_tolstring(LUA, -1, &len);
    lua_pop(LUA, 1); // Remove fetched value
    return std::string{result, len};
}

static std::string extractString(lua_State *LUA, int idx) {
    size_t len = 0;
    auto buffer = lua_tolstring(LUA, idx++, &len);
    std::string value(buffer, len);
    return value;
}