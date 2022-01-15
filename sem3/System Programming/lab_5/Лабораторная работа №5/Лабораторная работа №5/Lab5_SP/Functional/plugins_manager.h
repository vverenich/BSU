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
	__declspec(dllexport) HINSTANCE Plugins[MAXPLUGINSALLOWED];
	__declspec(dllexport) int pluginsCount;

	__declspec(dllexport) void LoadPlugins(bool lang);
	__declspec(dllexport) void UnloadPlugins(bool lang);
	__declspec(dllexport) void ShowListOfPlugins(bool lang);
	__declspec(dllexport) void ShowInfo(bool lang);
	__declspec(dllexport) void RunPlugins(bool lang);
	__declspec(dllexport) void Exit(bool lang);

#ifdef __cplusplus
};
#endif