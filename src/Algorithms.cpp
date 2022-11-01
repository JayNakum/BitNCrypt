#include "Algorithms.h"

#include <iostream>

#include "Utility/IOManager.h"
#include "Utility/Maths.h"

std::string Algorithms::generatePassword(const std::string& keyword, const std::string& key, const std::string& txt)
{
	std::string password = keyword;

	exclusiveOR(password, txt);

	return password;
}

void Algorithms::exclusiveOR(std::string& password, const std::string& txt)
{
	if (password.length() < txt.length())
	{
		while (password.length() < txt.length())
		{
			password += password;
		}
	}

	std::string result = "";

	int len = (password.length() < txt.length()) ? password.length() : txt.length();
	for (int i = 0; i < len; i++)
	{
		result += ((password[i] ^ txt[i]) % 26) + 97;
	}

	// std::cout << "XOR: " << result << std::endl;

	password = result;
}

std::vector<int> Algorithms::generateKey()
{
	std::vector<int> key;
	int tempKey = 0;

	// the key password will be of 6 digits
	while(key.size() < 6)
	{
		// shuffle allows duplicate numbers in key
		bool shuffle = false;

		// generate a random number between 1 to 9
		tempKey = Math::random(1, 9);

		// find if the generated random number is already in the key
		for (auto& k : key)
		{
			if (tempKey == k)
			{
				// if found enable shuffle
				shuffle = true;
				break;
			}
		}

		// shuffle is a 1 in 6*4 = 24 chance that the duplicate number will be added
		// 1 in 24 because we prefer unique numbers
		// but occasional duplicate will encourage confusion
		if (shuffle && Math::random(24) % 24 != 0)
		{
			continue;
		}

		// insert the generated number to the vector
		key.push_back(tempKey);
	}

	return key;
}
