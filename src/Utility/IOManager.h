#pragma once

#include <fstream>

#include <vector>
#include <string>

namespace IOManager {
	// method to read from a file
	bool readFromFile(const char* filePath, std::vector<std::string>& out_data);

	// copy data to clipboard
	bool copyToClipboard(const char* data);
}
