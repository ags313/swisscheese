#include "library.h"
#include "swiss_meter/lua_interop.h"
#include "swiss_meter/MeasurementApi.h"
#include "swiss_meter/Output.h"

static SwissMeter::MeasurementApi *api = nullptr;

static void dllStart() {
    if (api == nullptr) {
        api = new SwissMeter::MeasurementApi();
    }
}

static int exportStart(lua_State *L) { return 0; }
static int exportStop(lua_State *L) { return 0; }

static int missionLoaded(lua_State *LUA) {
    // DCS.getMissionName()
    const auto missionName = extractString(LUA, 1);
    api->startMeasurementStream(missionName);

    return 0;
}

static int setMeasuringDirectory(lua_State *LUA) {
    const auto directory = extractString(LUA, 1);
    api->setMeasurementDirectory(directory);

    return 0;
}

static int nameColumn(lua_State *LUA) {
    const auto columnName = extractString(LUA, 1);
    api->nameEvent(columnName);

    return 0;
}

static int sinceStart(lua_State *LUA) {
    int idx = 1;
    const auto column = (int) lua_tointeger(LUA, idx++);
    api->observeSinceStart(column);

    return 0;
}

static int start(lua_State *LUA) {
    int idx = 1;
    const auto column = (int) lua_tointeger(LUA, idx++);
    api->start(column);

    return 0;
}

static int finish(lua_State *LUA) {
    int idx = 1;
    const auto column = (int) lua_tointeger(LUA, idx++);
    api->finish(column);

    return 0;
}

static int newSample(lua_State *LUA) {
    api->startObservation();

    return 0;
}

static int rawValue(lua_State *LUA) {
    int idx = 1;
    const auto column = (int) lua_tointeger(LUA, idx++);
    const auto value = lua_tointeger(LUA, idx++);
    api->observerRawValue(value, column);
    return 0;
}

#ifdef _WIN32
#define EXPORT_SYMBOL __declspec(dllexport)
#else
#define EXPORT_SYMBOL __attribute__((visibility("default")))
#endif
extern "C" EXPORT_SYMBOL int luaopen_swisscheese(lua_State *L) {
    dllStart();

    static const luaL_Reg luaBridgeCalls[] = {
        {"missionLoaded", missionLoaded},
        {"setMeasuringDirectory", setMeasuringDirectory},

        {"exportStart", exportStart},
        {"exportStop", exportStop},

        {"nameColumn", nameColumn},
        {"sinceStart", sinceStart},
        {"newSample", newSample},
        {"rawValue", rawValue},
        {"start", start},
        {"finish", finish},

        {nullptr, nullptr}
    };
    luaL_register(L, "swisscheese", luaBridgeCalls);

    return 1;
}
