#pragma once

#include "ArgumentsHandler.h"
#include "Algorithms.h"

#include <string>
#include <vector>

class BitNCrypt
{
public:
	BitNCrypt(int count, char** arguments);
	// a destructor to free the memory
	~BitNCrypt();
private:
	// generating a new password
	void go();
	// print help message
	void help() const;

private:
	ArgumentsHandler* argumentsHandler;
	Algorithms* algorithms;
};
