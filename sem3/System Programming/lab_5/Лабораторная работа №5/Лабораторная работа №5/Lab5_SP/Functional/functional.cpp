#include "plugins_manager.h"

void LoadPlugins(bool lang)
{
	pluginsCount = 0;
	WIN32_FIND_DATA file;//file description
	HANDLE hFile = FindFirstFile("Plugins\\*.dll", &file);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		if (pluginsCount == MAXPLUGINSALLOWED)
		{
			break;
		}
		char buf[256] = "Plugins\\";
		strcat_s(buf, 256, file.cFileName);
		Plugins[pluginsCount] = LoadLibrary(buf);
		++pluginsCount;
	} while (FindNextFile(hFile, &file));
	FindClose(hFile);

	if (!lang)
		printf("Загружено плагинов: %d \n\n", pluginsCount);
	else
		printf("Plugins loaded: %d \n\n", pluginsCount);
}

void UnloadPlugins(bool lang)
{
	if (pluginsCount == 0)
	{
		if (!lang)
			printf("%s\n\n", "Плагины не были загружены");
		else
			printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	do
	{
		FreeLibrary(Plugins[pluginsCount - 1]);
		Plugins[pluginsCount - 1] = NULL;
		--pluginsCount;
	} while (pluginsCount != 0);

	if (!lang)
		printf("%s\n\n", "Все плагины были выгружены");
	else
		printf("%s\n\n", "All plugins were unloaded.");
}

void ShowListOfPlugins(bool lang)
{
	if (pluginsCount == 0)
	{
		if (!lang)
			printf("%s\n\n", "Плагины не были загружены");
		else
			printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	/**
	DWORD bufdword = 0;
	char buffer[512];
	PluginInfo PI;
	*/
	for (int i = 0; i < pluginsCount; ++i)
	{
		/*
		PI = (PluginInfo)GetProcAddress(Plugins[i], "GetDescription");
		PI(buffer, 512, &bufdword);
		*/
		if (!lang)
			printf("Плагин %d;\n", i + 1);
		else
			printf("Plugin %d;\n", i + 1);
	}
}

void ShowInfo(bool lang)
{
	if (pluginsCount == 0)
	{
		if (!lang)
			printf("%s\n\n", "Плагины не были загружены");
		else
			printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	DWORD bufdword = 0;
	char buffer[512];
	PluginInfo PI;
	for (int i = 0; i < pluginsCount; ++i)
	{
		PI = (PluginInfo)GetProcAddress(Plugins[i], "GetDescription");
		PI(buffer, 512, &bufdword);

		if (!lang)
			printf("Описание плагина%d: %s\n", i + 1, buffer);
		else
			printf("Plugin%d description: %s\n", i + 1, buffer);

		PI = (PluginInfo)GetProcAddress(Plugins[i], "GetAuthor");
		PI(buffer, 512, &bufdword);
		if (!lang)
			printf("Автор: %s\n\n", buffer);
		else
			printf("Author: %s\n\n", buffer);
	}
}

void RunPlugins(bool lang)
{
	if (pluginsCount == 0)
	{
		if (!lang)
			printf("%s\n\n", "Плагины не были загружены");
		else
			printf("%s\n\n", "There're no loaded plugins");
		return;
	}
	PluginExecute PE;
	for (int i = 0; i < pluginsCount; ++i)
	{
		PE = (PluginExecute)GetProcAddress(Plugins[i], "Execute");
		PE();
	}
}


void Exit(bool lang)
{
	if (pluginsCount != 0)
	{
		do
		{
			FreeLibrary(Plugins[pluginsCount - 1]);//сообщит Windows, что данная программа DLL больше не использует
			Plugins[pluginsCount - 1] = NULL;
			--pluginsCount;
		} while (pluginsCount != 0);
		if (!lang)
			printf("%s\n\n", "Все плагины были выгружены");
		else
			printf("%s\n\n", "All plugins were unloaded.");
	}
	if (!lang)
		printf("%s", "Программа завершена...");
	else
		printf("%s", "Program finished...");
}