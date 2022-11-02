#include "BitNCrypt.h"

#include "Utility/CppLog.h"
#include "Utility/IOManager.h"
#include "Utility/Maths.h"

#include <iostream>

#include <thread>

BitNCrypt::BitNCrypt(int count, char** args)
{
    if (count < 2)
    {
        // check for minimum arguments
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

    // generate the password # MAIN METHOD #
    go();
}

void BitNCrypt::go()
{
    // handle invalid inputs and helps
    if (!(argumentsHandler->processArguments()))
    {
        help();
        return;
    }

    // initialize the algorithm class if there are no invalid inputs
    algorithms = new Algorithms();
    
    // if user wants to -get a password
    if (argumentsHandler->getFirstArg() == "-get")
    {
        std::vector<std::string> fileData;
        // check if the key file is provided
        if (!IOManager::readFromFile("key", fileData))
        {
            std::cout << "please provide the key file" << std::endl
                << "See -help for more details" << std::endl;
            help();
            return;
        }
        
        std::string txt;
        std::thread convert([&]() {
            for (auto& line : fileData)
            {
                // convert the random symbols into numbers
                for (int k : line)
                {
                    txt += k;
                }
            }
        });

        // the main password that will be computed
        std::string password = "password";

        // get the password from the user
        std::cout << "Please enter the key: ";
        std::string key;
        std::cin >> key;

        // wait for the conversion
        convert.join();

        // compute the password for the given keyword
        password = algorithms->generatePassword(argumentsHandler->getKeyword(), key, txt);
        
        // if the user wants to -display the generated password
        std::thread display([&]() {
            if (argumentsHandler->getArgAt(1) == "-display")
            {
                char choice = 'n';
                // ask for a confirmation
                std::cout << "Are you sure? (Y/N) ";
                std::cin >> choice;

                if (choice == 'Y' || choice == 'y')
                {
                    std::cout << password << std::endl;
                }
            }
        });

        if (!IOManager::copyToClipboard(password.c_str()))
        {
            std::cout << "Unable to copy to clipboard." << std::endl
                << "Please use -display.";
        }
        display.join();
    }
    // if the user wants to -generate a password and txt
    else if (argumentsHandler->getFirstArg() == "-generate")
    {
        std::vector<std::string> fileData;
        // check if key.txt is provided
        if (!IOManager::readFromFile("key.txt", fileData))
        {
            std::cout << "File not found: key.txt" << std::endl
                << "See -help for more details" << std::endl;
            help();
            return;
        }

        /// Here multiple threads are being created to 
        /// 1) generate and display the password key
        /// 2) jumble the key file
        /// 3) delete the old key.txt
        /// this is done for improving execution speed

        // Generate and display the password key
        std::thread genKey([&]() {
            std::vector<int> key;
            key.reserve(6);
            algorithms->generateKey(key);
            std::cout << "Press any key to display your password...";
            std::cin.get();
            for (auto& k : key)
            {
                std::cout << k;
            }
            std::cout << std::endl << "Please remember it and don't share it" << std::endl;            
        });

        // Jumble the key file
        std::thread jumbleFile([&]() {

            // convert the multiple line into a single line
            std::string data;
            for (auto& line : fileData)
            {
                data += line;
            }

            // 50% chance of adding or subtracting
            // a random number from each character
            std::string bytes = "";
            for (int c : data)
            {
                bytes += c;
                if (Math::random(1))
                {
                    bytes += c - Math::random();
                }
                else
                {
                    bytes += c + Math::random();
                }
            }

            // write to file
            IOManager::writeToFile(bytes);

            std::cout << "key file is generated..." << std::endl
                << "keep it safe!" << std::endl;
        });

        // remove the old key.txt
        std::thread removeFile([&]() {
            int status = remove("key.txt");
            if (status)
            {
                // if status failed ask user to manually delete the file
                std::cout << "WARNING: Unable to delete key.txt" << std::endl
                    << "Please delete it manually." << std::endl;
            }
        });

        // wait for all threads to terminate
        removeFile.join();
        jumbleFile.join();
        genKey.join();
    }
}

void BitNCrypt::help() const
{
    std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "\t\x1B[32mBitNCrypt Help\x1B[00m" << std::endl << std::endl;
    std::cout << "\x1B[33m-get\x1B[00m <keyword>" << "\t\t" << "It is used to get a password. A keyword is required." << std::endl << std::endl;
    std::cout << "\x1B[33m-generate\x1B[00m" << "\t\t" << "It generates a key for you to remember. And it jumbles key.txt (required to be kept in same directory as the exe)" << std::endl << std::endl;
    std::cout << "\x1B[33m-display\x1B[00m" << "\t\t" << "It will display the generated password." << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}

BitNCrypt::~BitNCrypt()
{
    // free the memory
    delete argumentsHandler;
    delete algorithms;
}
