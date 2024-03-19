// vector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"
#include "Multiply.h"

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		std::cout << "Invalid arguments count" << std::endl;
		return 1;
	}

	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

	if (std::cin.bad() || !std::cin.eof())
	{
		std::cout << "Failed to read data from input stream" << std::endl;
		return 1;
	}

	MultiplyVectorOnMinElement(numbers);	
	std::sort(numbers.begin(), numbers.end());

	std::cout << std::setprecision(3) << std::fixed;
	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));

	return 0;
}