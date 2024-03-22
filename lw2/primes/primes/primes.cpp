// primes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <iterator>
#include <sstream>
#include "GeneratePrimes.h"

const std::string INVALID_ARGS = "Invalid arguments.\nUsage: primes.exe <number>\n<number> should be smaller than 100 000 000.";

bool ConvertStrToInt(const std::string& str, int& num)
{
	for (char ch : str)
	{
		if (ch >= '0' && ch <= '9')
		{
			num = num * 10 + (ch - '0');
		}
		else
		{
			return false;
		}
	}
	return true;
}

std::optional<int> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	std::string upperBoundString = argv[1];
	int upperBound;

	if (!ConvertStrToInt(upperBoundString, upperBound))
	{
		return std::nullopt;
	}

	if (upperBound > MAX_LIMIT)
	{
		return std::nullopt;
	}
	
	return upperBound;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << INVALID_ARGS;
		return 1;
	}

	std::set<int> primes = GeneratePrimeNumbersSet(args.value());
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<int>(std::cout, " "));

	return 0;
}