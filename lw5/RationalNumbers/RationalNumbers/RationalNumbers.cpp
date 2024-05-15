// RationalNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CRational.h"

int main()
{
    CRational a = 5, b = 6, c = 7;

    (a += b) += c;
    std::cout << a;

    return 0;
}