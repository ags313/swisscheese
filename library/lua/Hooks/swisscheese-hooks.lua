SwissCheese   = { }

package.path      = package.path .. ";" .. lfs.writedir() .. "\\Mods\\tech\\swisscheese\\lua\\?.lua"
package.cpath     = package.cpath .. ';' .. lfs.writedir() .. '\\Mods\\tech\\swisscheese\\bin\\?.dll;'
local status, dll = pcall(require, 'swisscheese')
if (not status) then
    net.log("[swisscheese]", "Failed to load DLL")
else
    net.log("[swisscheese]", "Loaded Swiss Cheese, let's count the holes")
    SwissCheese.DLL = dll
end

SwissCheese.countPlayers = function()
    local playerCount = 0;
    local serverPlayers = net.get_player_list()
    for index, value in ipairs(serverPlayers) do
        playerCoount = playerCount + 1;
    end;
    return playerCoount;
end

SwissCheese.onMissionLoadEnd = function()
    SwissCheese.DLL.missionLoaded(DCS.getMissionName());
end

SwissCheese.onSimulationStart = function()
    local playerCount = SwissCheese.countPlayers();

    SwissCheese.DLL.rawValue(5, playerCount);
end

SwissCheese.onPlayerConnect = function()
    local playerCount = SwissCheese.countPlayers();

    SwissCheese.DLL.rawValue(5, playerCount);
end

SwissCheese.onPlayerDisconnect = function()
    local playerCount = SwissCheese.countPlayers();

    SwissCheese.DLL.rawValue(5, playerCount);
end

SwissCheese.onSimulationFrame = function()
    SwissCheese.DLL.sinceStart(3);
end


if DCS.isServer() then
    SwissCheese.DLL.setMeasuringDirectory("c:\\temp\\swiss\\");
    SwissCheese.DLL.nameColumn("wrapped before next (micros)");
    SwissCheese.DLL.nameColumn("frame time (micros)");
    SwissCheese.DLL.nameColumn("frame start to server side callback (micros)");
    SwissCheese.DLL.nameColumn("wrapped after next (micros)");
    SwissCheese.DLL.nameColumn("player count");
    DCS.setUserCallbacks(SwissCheese);
end