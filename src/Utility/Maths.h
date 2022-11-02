#pragma once

namespace Math {

	// Left or Right circular shifting
	int leftCircularShift(unsigned n, int k);
	int rightCircularShift(unsigned n, int k);


	// Function to generate a random number
	int random();
	
	// Function to generate a random number between 0 and given bound
	int random(const int bound);
	
	// Function to generate a random number in a given range
	int random(const int min, const int max);
}