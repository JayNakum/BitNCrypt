#include "Algorithms.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <vector>

Algorithms::Algorithms(std::string keyword)
{
}

std::vector<int> Algorithms::generateKey()
{
	std::srand(std::time(0));
	std::vector<int> key;
	int tempKey = 0;

	while(key.size() <= 6)
	{
		tempKey = (rand() % 9) + 1;
		bool shuffle = false;

		for (auto& k : key)
		{
			if (tempKey == k)
			{
				shuffle = true;
				break;
			}
		}

		if (shuffle)
		{

		}
		else
		{
			key.push_back(tempKey);
		}
	}

	return key;
}

std::string Algorithms::generatePassword()
{
	return std::string();
}
