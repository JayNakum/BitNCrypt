#pragma once

#include <string>
#include <vector>

class ArgumentsHandler
{
public:
	ArgumentsHandler(const std::vector<std::string>& args);
	// process the arguments
	bool processArguments();

	// get argument at index
	inline const std::string getFirstArg() const { return arguments.at(0); }
	inline const std::string getArgAt(const int index) const { return arguments.at(index); }
	inline const std::string getKeyword() const { return arguments.back(); }

private:
	// all arguments from user input
	std::vector<std::string> arguments;

private:
	// a vector of valid options
	// to check the syntax
	const std::vector<std::string> valid_options = {
		"-help",
		"-generate",
		"-get",
		"-display"
	};
};
