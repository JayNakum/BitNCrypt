#pragma once

#include <fstream>

#include <vector>
#include <string>

namespace IOManager {
	// read from a file
	bool readFromFile(const char* filePath, std::vector<std::string>& out_data);

	// write to a file
	bool writeToFile(const std::string& data, const char* filePath = "key");

	// copy data to clipboard
	bool copyToClipboard(const char* data);
}
