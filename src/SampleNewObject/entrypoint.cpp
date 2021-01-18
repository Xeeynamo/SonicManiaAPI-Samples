#include <cstdio> // Required by printf
#include <Windows.h> // Required by ManiaModLoader.h
#include <ManiaModLoader.h>
#include <SonicMania.h>
#include "MyObject.h"

extern "C" __declspec(dllexport) ModInfo ManiaModInfo = { ModLoaderVer, GameVer };
extern "C" __declspec(dllexport) void LinkGameLogic() { MyObject_Create(); }