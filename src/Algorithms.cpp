#include "Algorithms.h"

#include <iostream>
#include <thread>

#include "Utility/IOManager.h"
#include "Utility/Maths.h"

std::string Algorithms::generatePassword(const std::string& keyword, const std::string& key, const std::string& txt)
{
	std::string password = keyword;
	
	initialPermutation(password, txt);

	shifting(password, key);
	exclusiveOR(password, txt);

	finalPermutation(password, key);

	return password;
}

void Algorithms::initialPermutation(std::string& password, const std::string& txt)
{
	// get the password to equal length of txt
	while (password.length() < txt.length())
		password += password;
	
	// perform AND operation with txt
	std::string result = "";
	for (int i = 0; i < txt.length(); i++)
	{
		result += password[i] & txt[i];
	}
	password = result;
}

void Algorithms::finalPermutation(std::string& password, const std::string& key)
{
	std::string symbols = "!@#$";
	
	// divide password into 6 parts
	int n = std::floor(password.length() / 6);
	std::string subStr[6] = {
		password.substr(5*n, n),
		password.substr(4*n, n),
		password.substr(3*n, n),
		password.substr(2*n, n),
		password.substr(n, n),
		password.substr(0, n)
	};

	std::string result = "";

	for (int i = 0; i < key.length(); i++)
	{
		int k = key[i] - '0';
		std::string ss = subStr[i];
		// get one character from each substring according to key
		char s = ss[k % n];

		// if the character is an alphabet then insert it
		// else insert key[n - i]
		if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z'))
			result += s;
		else
			result += (s % 26) + 'A';

		// based on weired maths insert a symbol or key
		if (k % 2 == 0) result += key[i];
		if (k % 3 == 0) result += symbols[k % 4];
	}
	password = result;
}

void Algorithms::shifting(std::string& password, const std::string& key)
{
	int k1 = key[2] - '0';
	int k2 = key[3] - '0';
	int k3 = key[4] - '0';
	int k4 = key[5] - '0';
	
	std::string result[4] = { "", "", "", "" };

	// divide the password into 4 sections
	int n = std::floor(password.length() / 4);

	// four seperate threads to perform following operation on 4 sections
	// if key[i] is even then left circular shift each character by key[i]
	// if key[i] is odd then right circular shift each character by key[i]

	std::thread t_m1([&]() {
		for (int x : password.substr(0, n))
		{
			int add;
			if ((x * k4) % 2) add = 'A';
			else add = 'a';
			
			if (k1 % 2 == 0)
				result[0] += (Math::leftCircularShift(x, k1) + add);
			else
				result[0] += (Math::rightCircularShift(x, k1) + add);
		}
	});

	std::thread t_m2([&]() {
		for (int x : password.substr(n, n))
		{
			int add;
			if ((x * k3) % 2) add = 'A';
			else add = 'a';

			if (k2 % 2 == 0)
				result[1] += (Math::leftCircularShift(x, k2) + add);
			else
				result[1] += (Math::rightCircularShift(x, k2) + add);
		}
	});

	std::thread t_m3([&]() {
		for (int x : password.substr(2*n, n))
		{
			int add;
			if ((x * k2) % 2) add = 'A';
			else add = 'a';

			if (k3 % 2 == 0)
				result[2] += (Math::leftCircularShift(x, k3) + add);
			else
				result[2] += (Math::rightCircularShift(x, k3) + add);
		}
	});

	std::thread t_m4([&]() {
		for (int x : password.substr(3*n, n))
		{
			int add;
			if ((x * k1) % 2) add = 'A';
			else add = 'a';

			if (k4 % 2 == 0)
				result[3] += (Math::leftCircularShift(x, k4) + add);
			else
				result[3] += (Math::rightCircularShift(x, k4) + add);
		}
	});

	t_m1.join();
	t_m2.join();
	t_m3.join();
	t_m4.join();

	password = "";
	// insert the results based on key
	for (int i = 0; i <= 3 ; i++)
	{
		password += result[key[i] % 3];
	}
}

void Algorithms::exclusiveOR(std::string& password, const std::string& txt)
{
	std::string result = "";

	// get the minimum length
	int len = (password.length() < txt.length()) ? password.length() : txt.length();
	
	// perform xor on each character of password and txt upto len
	for (int i = 0; i < len; i++)
	{
		int add;
		if (i * len % 2) add = 'A';
		else add = 'a';

		// calculate xor
		result += ((password[i] ^ txt[i]) % 26) + add;
	}

	password = result;
}

void Algorithms::generateKey(std::vector<int>& out_key)
{
	bool insertedNumbers[] = {
		false, // 0
		false, // 1
		false, // 2
		false, // 3
		false, // 4
		false, // 5
		false, // 6
		false, // 7
		false, // 8
		false  // 9
	};

	int tempKey = 0;

	// the key password will be of 6 digits
	while(out_key.size() < 6)
	{
		// shuffle allows duplicate numbers in key
		bool shuffle = false;

		// generate a random number between 0 to 9
		tempKey = Math::random(9);

		if (insertedNumbers[tempKey])
		{
			shuffle = true;
		}

		// shuffle is a 1 in 6*2 = 12 chance that the duplicate number will be added
		// 1 in 12 because we prefer unique numbers
		// but occasional duplicate will encourage confusion
		if (shuffle && Math::random(12) % 12 != 0)
		{
			continue;
		}

		// insert the generated number to the vector
		insertedNumbers[tempKey] = true;
		out_key.push_back(tempKey);
	}
}
