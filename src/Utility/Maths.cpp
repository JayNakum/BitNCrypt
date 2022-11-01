#include "Maths.h"

#include <cstdlib>
#include <ctime>

namespace Math {
	
	// RANDOM NUMBER GENERATORS
	
	/// each function uses the current time as the seed of random number generator

	// for any random number
	int random()
	{
		std::srand(std::time(0));
		return rand();
	}

	// for a number between 0 to bound (inclusive)
	int random(const int bound)
	{
		std::srand(std::time(0));
		return (rand() % bound);
	}

	// for a number in a given range (inclusive)
	int random(const int min, const int max)
	{
		std::srand(std::time(0));
		return (rand() % max) + min;
	}

}
