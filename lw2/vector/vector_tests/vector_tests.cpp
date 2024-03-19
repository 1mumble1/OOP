// vector_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../../vector/vector/stdafx.h"
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../../vector/vector/Multiply.h"
#include <sstream>

SCENARIO("Multiply empty vector gives empty vector")
{
	std::vector<double> empty;
	MultiplyVectorOnMinElement(empty);
	REQUIRE(empty.empty());
}

SCENARIO("Multiply vector on min element with value 1 gives same vector")
{
	std::vector<double> one{ 1, 2, 3, 4 };
	std::vector<double> sameOne{ 1, 2, 3, 4 };
	MultiplyVectorOnMinElement(one);
	REQUIRE(one == sameOne);
}

SCENARIO("Multiply vector on min element with value 0 gives vector full of 0")
{
	std::vector<double> withZero{ 0, 2, 3, 4 };
	std::vector<double> zeros{ 0, 0, 0, 0 };
	MultiplyVectorOnMinElement(withZero);
	REQUIRE(withZero == zeros);
}

SCENARIO("Multiply vector on min element with any value gives new vector")
{
	std::vector<double> vec{ 10, 0.1, 30, 45 };
	std::vector<double> newVec{ 1, 0.01, 3, 4.5 };
	MultiplyVectorOnMinElement(vec);
	REQUIRE(vec == newVec);
}

SCENARIO("Multiply vector on min element with negative value gives new vector")
{
	std::vector<double> vec{ 10, -0.1, 30, 45 };
	std::vector<double> newVec{ -1, 0.01, -3, -4.5 };
	MultiplyVectorOnMinElement(vec);
	REQUIRE(vec == newVec);
}

SCENARIO("")
{

	std::istringstream iss("123 123 a");
	std::vector<double> numbers(std::istream_iterator<double>(iss), (std::istream_iterator<double>()));
	if (iss.bad() || !iss.eof())
	{
		std::cout << "Failed to read data from input stream" << std::endl;
	}
	REQUIRE();
}