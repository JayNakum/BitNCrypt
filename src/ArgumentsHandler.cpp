#include "ArgumentsHandler.h"

#include "Utility/CppLog.h"
#include "Utility/IOManager.h"

#include <iostream>

ArgumentsHandler::ArgumentsHandler(const std::vector<std::string>& args)
	: arguments(args) {}

bool ArgumentsHandler::processArguments()
{
	// if the user has entered a keyword
	bool hasKeyword = false;

	// check if the first argument is an option or not
	// an option is mandatory
	std::string arg1 = arguments[0];
	if (arg1[0] != '-')
	{
		std::cout << "Invalid option: " << arg1 << std::endl;
		std::cout << "Please refer to -help" << std::endl;
		return false;
	}

	// return false if help
	// it will automaticaly print the help 
	if (arg1 == "-help") return false;
	// invlid -display before -get
	if (arg1 == "-display")
	{
		std::cout << "Invalid format." << std::endl;
		std::cout << "See -help for details." << std::endl;
		return false;
	}

	// if user wants to generate new key
	if (arg1 == "-generate") return true;

	for (auto& arg : arguments)
	{
		bool checkFlg = false;

		// Check if it matches with any valid argument
		if (arg[0] == '-')
		{
			for (auto& opt : valid_options)
			{
				if (arg == opt)
				{
					checkFlg = true;
					break;
				}
			}
		}
		else
		{
			// break the loop when we get keyword
			hasKeyword = true;
			break;
		}

		if (!checkFlg)
		{
			std::cout << "Invalid option: " << arg << std::endl;
			std::cout << "Please refer to --help or -h" << std::endl;
			return false;
		}
	}

	if (!hasKeyword)
	{
		std::cout << "Please enter a keyword." << std::endl;
		std::cout << "See -help for reference." << std::endl;
		return false;
	}
	return true;
}
