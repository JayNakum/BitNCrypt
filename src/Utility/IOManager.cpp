#include "CppLog.h"

#include "IOManager.h"

// A simple utility file to handle IO

namespace IOManager {

	// readFromFile(filePath) : vector<string>data, bool status
	bool readFromFile(const char* filePath, std::vector<std::string>& out_data)
	{
		LOG_DEBUG("Reading file: %s", filePath);
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
		LOG_INFO("File reading successful");
		return true;
	}

	// copyToClipboard(data) : bool <status>
	bool copyToClipboard(const char* data)
	{
		return false;
	}
}
