#include "BitNCrypt.h"

#include "Utility/CppLog.h"
#include "Utility/IOManager.h"

#include <iostream>

BitNCrypt::BitNCrypt(int count, char** args)
{
    LOG_DEBUG("Initializing");
    if (count < 3)
    {
        // check for minimum arguments
        LOG_WARNING("No Arguments Found");
        std::cout << "Invalid arguments." << std::endl;
        std::cout << "See -help for reference." << std::endl;
        help();
        return;
    }

    // convert the char** to a vector<string> to pass to the arguments handler
    std::vector<std::string> arguments;
    for (int i = 1; i < count; i++)
    {
        arguments.push_back(args[i]);
    }

    // initialize the arguments handler
    argumentsHandler = new ArgumentsHandler(arguments);

    LOG_INFO("Initialization Successful");

    // generate the password # MAIN METHOD #
    go();
}

void BitNCrypt::go()
{
    LOG_DEBUG("Generating...");

    // handle invalid inputs and helps
    if (!(argumentsHandler->processArguments()))
    {
        help();
        return;
    }

    algorithms = new Algorithms(argumentsHandler->getKeyword());
    bool generate = false, get = false, display = false;

    if (argumentsHandler->getFirstArg() == "-get")
    {
        get = true;
    }
    else if (argumentsHandler->getFirstArg() == "-generate")
    {
        generate = true;
        std::vector<int> key = algorithms->generateKey();
        std::cout << "Displaying the key" << std::endl << "Press any key to continue...";
        std::cin.get();
        for (auto& k : key)
        {
            std::cout << k;
        }
        std::cout << std::endl;

    }

    if (argumentsHandler->getArgAt(1) == "-display")
    {
        char choice = 'n';
        std::cout << "Are you sure? (Y/N) ";
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y')
        {
            display = true;
        }

    }
    



    LOG_INFO("Generating Complete");
}

void BitNCrypt::help() const
{
    std::cout << "***************Help***************" << std::endl;
}

BitNCrypt::~BitNCrypt()
{
    LOG_DEBUG("Terminating BitNCrypt");
    // free the memory
    delete argumentsHandler;
}
