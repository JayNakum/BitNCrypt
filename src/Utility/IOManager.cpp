#define _CRT_SECURE_NO_WARNINGS

#include "CppLog.h"

#include "IOManager.h"

#include <iostream>
#include <cstring>

#include <Windows.h>

// A simple utility file to handle IO

namespace IOManager {

	// readFromFile(filePath) : vector<string>data, bool status
	bool readFromFile(const char* filePath, std::vector<std::string>& out_data)
	{
		std::ifstream file(filePath);
		
		if (!file.is_open())
		{
			LOG_ERROR("Failed to read file: %s", filePath);
			return false;
		}

		std::string line;
		while (std::getline(file, line))
		{
			out_data.push_back(line);
		}
		file.close();
		return true;
	}

	// writeToFile(data, filePath) : bool status
	bool writeToFile(const std::string& data, const char* filePath)
	{
		std::ofstream file(filePath);

		if (!file.is_open())
		{
			LOG_ERROR("Failed to write file: %s", filePath);
			return false;
		}
		
		file << data;

		file.close();
		return true;
	}

	// copyToClipboard(data) : bool <status>
	bool copyToClipboard(const char* data)
	{
		char some[256]; // your text here, zero ended
		std::strcpy(some, data);
		OpenClipboard(GetDesktopWindow());
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, ARRAYSIZE(some) + 1);
		if (!hg)
		{
			CloseClipboard();
			return false;
		}
		memcpy(GlobalLock(hg), some, ARRAYSIZE(some) + 1);
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
		return true;
	}
}
