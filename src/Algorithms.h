#pragma once

#include <string>
#include <vector>
#include <functional>

class Algorithms
{
public:
	std::vector<int> generateKey();
	std::string generatePassword(const std::string& keyword, const std::string& key, const std::string& txt);

private:
	void exclusiveOR(std::string& password, const std::string& txt);



private:
	std::string key;
	std::string txt;

	std::vector<std::function<bool(std::string&)>> algorithms;
};

