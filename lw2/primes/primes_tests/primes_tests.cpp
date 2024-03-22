// primes_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../primes/GeneratePrimes.h"

SCENARIO("If number smaller than 2, it gives empty set")
{
	std::set<int> primes = GeneratePrimeNumbersSet(0);
	REQUIRE(primes.empty());
}

SCENARIO("If number = 2, it gives set with only one number = 2")
{
	std::set<int> primes = GeneratePrimeNumbersSet(2);
	std::set<int> example = { 2 };
	REQUIRE(primes == example);
}

SCENARIO("If number greater than 2, it gives set with several values")
{
	std::set<int> primes = GeneratePrimeNumbersSet(21);
	std::set<int> example = { 2, 3, 5, 7, 11, 13, 17, 19 };
	REQUIRE(primes == example);
}

SCENARIO("If number = MAX, it gives set with 5761455 values")
{
	std::set<int> primes = GeneratePrimeNumbersSet(MAX_LIMIT);
	int size = 5761455;
	REQUIRE(primes.size() == size);
}

SCENARIO("If number = MAX + 1, it gives empty set")
{
	std::set<int> primes = GeneratePrimeNumbersSet(MAX_LIMIT + 1);
	REQUIRE(primes.empty());
}

SCENARIO("If number = 1, it gives empty set")
{
	std::set<int> primes = GeneratePrimeNumbersSet(1);
	REQUIRE(primes.empty());
}

SCENARIO("If number = -1, it gives empty set")
{
	std::set<int> primes = GeneratePrimeNumbersSet(-1);
	REQUIRE(primes.empty());
}

SCENARIO("If number = 13, it gives set {2, 3, 5, 7, 11, 13}")
{
	std::set<int> primes = GeneratePrimeNumbersSet(13);
	std::set<int> example = { 2, 3, 5, 7, 11, 13 };
	REQUIRE(primes == example);
}