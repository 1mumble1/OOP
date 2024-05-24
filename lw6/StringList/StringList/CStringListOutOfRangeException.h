#pragma once
#include <stdexcept>

class CStringListOutOfRangeException : std::out_of_range
{
public:
	CStringListOutOfRangeException(const std::string& message)
		: std::out_of_range(message)
	{}
};

