#include "GeneratePrimes.h"

const int FIRST_PRIME = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primes;
	if (upperBound < FIRST_PRIME || upperBound > MAX_LIMIT)
	{
		return primes;
	}

	std::vector<bool> isPrime(upperBound + 1, true);
	for (int i = FIRST_PRIME; i * i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	for (int i = FIRST_PRIME; i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			primes.insert(i);
		}
	}

	return primes;
}