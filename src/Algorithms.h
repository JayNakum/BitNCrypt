#pragma once

#include <string>
#include <vector>
#include <functional>

class Algorithms
{
public:
	Algorithms(std::string keyword);

	std::vector<int> generateKey();
	std::string generatePassword();

private:
	std::string key;
	std::string txt;

	std::vector<std::function<bool(std::string&)>> algorithms;
};

