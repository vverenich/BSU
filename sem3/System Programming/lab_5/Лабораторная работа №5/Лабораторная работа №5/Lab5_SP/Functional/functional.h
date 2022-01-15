#pragma once

#include <stdio.h>
#include <windows.h>

#define  MAXPLUGINSALLOWED 10

#ifdef __cplusplus

extern "C" 
{
#endif

	typedef void(*PluginExecute)();
	typedef bool(*PluginInfo)(LPSTR, DWORD, DWORD*);
	__declspec(dllexport) HINSTANCE Plugins[MAXPLUGINSALLOWED];//возможность создавать DLL без DEF файлов
	__declspec(dllexport) int pluginsCount;//сообщает компоновщику, что вы хотите, чтобы этот объект был доступен для других DLL для импорта. Он используется при создании DLL, с которой другие могут ссылаться.

	__declspec(dllexport) void LoadPlugins(bool lang);
	__declspec(dllexport) void UnloadPlugins(bool lang);
	__declspec(dllexport) void ShowInfo(bool lang);
	__declspec(dllexport) void RunPlugins(bool lang);
	__declspec(dllexport) void Exit(bool lang);

#ifdef __cplusplus
};
#endif