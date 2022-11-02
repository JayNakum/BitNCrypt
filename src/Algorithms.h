#pragma once

#include <string>
#include <vector>
#include <functional>

class Algorithms
{
public:
	void generateKey(std::vector<int>& out_key);
	std::string generatePassword(const std::string& keyword, const std::string& key, const std::string& txt);

private:
	void shifting(std::string& password, const std::string& key);
	void exclusiveOR(std::string& password, const std::string& txt);

private:
	void initialPermutation(std::string& password, const std::string& txt);
	void finalPermutation(std::string& password, const std::string& key);

private:
	std::string key;
	std::string txt;

	std::vector<std::function<bool(std::string&)>> algorithms;
};

