#include "Multiply.h"
#include "stdafx.h"

void MultiplyVectorOnMinElement(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}

	double result = *std::min_element(numbers.begin(), numbers.end());

	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [result](double num) { return num * result; });
}