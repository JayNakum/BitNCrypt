#include "Maths.h"

#include <cstdlib>
#include <ctime>

namespace Math {
	
	// SHIFTING
	int leftCircularShift(unsigned n, int k)
	{
		// left shift by `k`
		return (((n << k) | (n >> ((sizeof(int) * 8) - k))) % 26);
	}

	int rightCircularShift(unsigned n, int k)
	{
		// right shift by `k`
		return (((n >> k) | (n << ((sizeof(int) * 8) - k))) % 26);
	}

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
