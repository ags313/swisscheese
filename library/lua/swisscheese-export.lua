-- version 0.0.1

if swissCheeseInitialised ~= true then
    swissCheeseInitialised = true;
    package.path           = package.path .. ";" .. lfs.writedir() .. "\\Mods\\tech\\swisscheese\\lua\\?.lua"
    package.cpath          = package.cpath .. ';' .. lfs.writedir() .. '\\Mods\\tech\\swisscheese\\bin\\?.dll;'

    SwissCheese            = {
        wrapped = {
            LuaExportStart           = function()
                --    noop
            end,
            LuaExportStop            = function()
                --    noop
            end,
            LuaExportBeforeNextFrame = function()
                --    noop
            end,
            LuaExportAfterNextFrame  = function()
                --    noop
            end,
        }
    }

    if LuaExportStart then
        SwissCheese.wrapped.LuaExportStart = LuaExportStart;
    end
    if LuaExportStop then
        SwissCheese.wrapped.LuaExportStop = LuaExportStop;
    end
    if LuaExportBeforeNextFrame then
        SwissCheese.wrapped.LuaExportBeforeNextFrame = LuaExportBeforeNextFrame;
    end
    if LuaExportAfterNextFrame then
        SwissCheese.wrapped.LuaExportAfterNextFrame = LuaExportAfterNextFrame;
    end

    local status, dll      = pcall(require, 'swisscheese')
    if (not status) then
        log.write("[swisscheese]", log.ERROR, "swisscheese DLL failed to load")
    else
        SwissCheese.DLL = dll
        log.write("[swisscheese]", log.INFO, "Loaded Swiss Cheese, let's count the holes")
    end

    function LuaExportStart()
        SwissCheese.DLL.exportStart();
        SwissCheese.wrapped.LuaExportStart();
    end

    function LuaExportStop()
        SwissCheese.DLL.exportStop();
        SwissCheese.wrapped.LuaExportStop();
    end

    function LuaExportBeforeNextFrame()
        SwissCheese.DLL.newSample();
        SwissCheese.wrapped.LuaExportBeforeNextFrame();
        SwissCheese.DLL.sinceStart(1);
        SwissCheese.DLL.start(2);
    end

    function LuaExportAfterNextFrame()
        SwissCheese.DLL.finish(2);
        SwissCheese.DLL.start(4);
        SwissCheese.wrapped.LuaExportAfterNextFrame();
        SwissCheese.DLL.finish(4);
    end
end
