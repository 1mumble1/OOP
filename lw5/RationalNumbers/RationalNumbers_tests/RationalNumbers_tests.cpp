// RationalNumbers_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../RationalNumbers/CRational.h"
#include <sstream>

TEST_CASE("Create numbers")
{
	WHEN("constructor is empty")
	{
		CRational number;
		THEN("numerator = 0, denominator = 1")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == static_cast<double>(0) / 1);
		}
	}

	WHEN("constructor has one parameter")
	{
		CRational number(5);
		THEN("numerator = 5, denominator = 1")
		{
			REQUIRE(number.GetNumerator() == 5);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == static_cast<double>(5) / 1);
		}
	}

	WHEN("constructor has two parameters")
	{
		CRational number(3, 4);
		THEN("numerator = 3, denominator = 4")
		{
			REQUIRE(number.GetNumerator() == 3);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == static_cast<double>(3) / 4);
		}
	}

	WHEN("numerator = 0")
	{
		CRational number(0, 3);
		THEN("set rational numbers num = 0, den = 1")
		{
			REQUIRE(number.GetNumerator() == 0);
			REQUIRE(number.GetDenominator() == 1);
			REQUIRE(number.ToDouble() == static_cast<double>(0) / 1);
		}
	}

	WHEN("denominator = 0")
	{
		THEN("will be thrown exception")
		{
			std::string exception;
			try
			{
				CRational(1, 0);
			}
			catch(std::invalid_argument e)
			{
				exception = e.what();
			}

			REQUIRE(exception == "Invalid value of denominator: it must be not null");
		}
	}

	WHEN("numerator < 0")
	{
		CRational number(-2, 5);
		THEN("numerator = -2, denominator = 5")
		{
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 5);
			REQUIRE(number.ToDouble() == static_cast<double>(-2) / 5);
		}
	}

	WHEN("denominator < 0")
	{
		CRational number(2, -5);
		THEN("numerator = -2, denominator = 5")
		{
			REQUIRE(number.GetNumerator() == -2);
			REQUIRE(number.GetDenominator() == 5);
			REQUIRE(number.ToDouble() == static_cast<double>(-2) / 5);
		}
	}
}

TEST_CASE("Check unary operations")
{
	WHEN("unary +")
	{
		CRational number(-3, 4);
		number = +number;
		THEN("number = -3/4")
		{
			REQUIRE(number.GetNumerator() == -3);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == static_cast<double>(-3) / 4);
		}
	}

	WHEN("unary -")
	{
		CRational number(-3, 4);
		number = -number;
		THEN("number = 3/4")
		{
			REQUIRE(number.GetNumerator() == 3);
			REQUIRE(number.GetDenominator() == 4);
			REQUIRE(number.ToDouble() == static_cast<double>(3) / 4);
		}
	}
}

TEST_CASE("Check binary operation +, -")
{
	WHEN("binary +")
	{
		CRational num1(2, 3);
		CRational num2(1, 3);
		CRational res = num1 + num2;
		THEN("res = 1")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 1);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 1);
		}
	}

	WHEN("binary + (different denominators)")
	{
		CRational num1(1, 4);
		CRational num2(1, 12);
		CRational res = num1 + num2;
		THEN("res = 1/3")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("num + int")
	{
		CRational num1(1, 3);
		CRational res = num1 + 1;
		THEN("res = 4/3")
		{
			REQUIRE(res.GetNumerator() == 4);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(4) / 3);
		}
	}

	WHEN("int + num")
	{
		CRational num1(1, 3);
		CRational res = 1 + num1;
		THEN("res = 4/3")
		{
			REQUIRE(res.GetNumerator() == 4);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(4) / 3);
		}
	}

	WHEN("bin -")
	{
		CRational num1(2, 3);
		CRational num2(1, 3);
		CRational res = num1 - num2;
		THEN("res = 1/3")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("int - num")
	{
		CRational num1(1, 2);
		CRational res = 1 - num1;
		THEN("res = 1/2")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 2);
		}
	}

	WHEN("num - int")
	{
		CRational num1(1, 2);
		CRational res = num1 - 1;
		THEN("res = -1/2")
		{
			REQUIRE(res.GetNumerator() == -1);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == static_cast<double>(-1) / 2);
		}
	}
}

TEST_CASE("+=, -=")
{
	WHEN("+=")
	{
		CRational num1(1, 2);
		CRational num2(1, 6);
		num1 += num2;
		THEN("num1 = 2/3")
		{
			REQUIRE(num1.GetNumerator() == 2);
			REQUIRE(num1.GetDenominator() == 3);
			REQUIRE(num1.ToDouble() == static_cast<double>(2) / 3);
		}
	}

	WHEN("num += int")
	{
		CRational num(1, 2);
		num += 1;
		THEN("num = 3/2")
		{
			REQUIRE(num.GetNumerator() == 3);
			REQUIRE(num.GetDenominator() == 2);
			REQUIRE(num.ToDouble() == static_cast<double>(3) / 2);
		}
	}

	WHEN("-=")
	{
		CRational num1(1, 2);
		CRational num2(1, 6);
		num1 -= num2;
		THEN("num1 = 1/3")
		{
			REQUIRE(num1.GetNumerator() == 1);
			REQUIRE(num1.GetDenominator() == 3);
			REQUIRE(num1.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("num -= int")
	{
		CRational num(1, 2);
		num -= 1;
		THEN("num = -1/2")
		{
			REQUIRE(num.GetNumerator() == -1);
			REQUIRE(num.GetDenominator() == 2);
			REQUIRE(num.ToDouble() == static_cast<double>(-1) / 2);
		}
	}
}

TEST_CASE("*, /")
{
	WHEN("*")
	{
		CRational num1(2, 3);
		CRational num2(1, 2);
		CRational res = num1 * num2;
		THEN("res = 1/3")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("num * int")
	{
		CRational num(1, 2);
		CRational res = num * (-3);
		THEN("res = -3/2")
		{
			REQUIRE(res.GetNumerator() == -3);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == static_cast<double>(-3) / 2);
		}
	}

	WHEN("int * num")
	{
		CRational num(2, 3);
		CRational res = 7 * num;
		THEN("res = 14/3")
		{
			REQUIRE(res.GetNumerator() == 14);
			REQUIRE(res.GetDenominator() == 3);
			REQUIRE(res.ToDouble() == static_cast<double>(14) / 3);
		}
	}

	WHEN("/")
	{
		CRational num1(2, 3);
		CRational num2(1, 2);
		CRational res = num2 / num1;
		THEN("res = 3/4")
		{
			REQUIRE(res.GetNumerator() == 3);
			REQUIRE(res.GetDenominator() == 4);
			REQUIRE(res.ToDouble() == static_cast<double>(3) / 4);
		}
	}

	WHEN("num / int")
	{
		CRational num(1, 2);
		CRational res = num / 5;
		THEN("res = 1/10")
		{
			REQUIRE(res.GetNumerator() == 1);
			REQUIRE(res.GetDenominator() == 10);
			REQUIRE(res.ToDouble() == static_cast<double>(1) / 10);
		}
	}

	WHEN("int / num")
	{
		CRational num(2, 3);
		CRational res = 7 / num;
		THEN("res = 21/2")
		{
			REQUIRE(res.GetNumerator() == 21);
			REQUIRE(res.GetDenominator() == 2);
			REQUIRE(res.ToDouble() == static_cast<double>(21) / 2);
		}
	}
}

TEST_CASE("*=, /=")
{
	WHEN("*=")
	{
		CRational num1(1, 2);
		CRational num2(2, 3);
		num1 *= num2;
		THEN("num1 = 1/3")
		{
			REQUIRE(num1.GetNumerator() == 1);
			REQUIRE(num1.GetDenominator() == 3);
			REQUIRE(num1.ToDouble() == static_cast<double>(1) / 3);
		}
	}

	WHEN("num += int")
	{
		CRational num(1, 2);
		num *= 3;
		THEN("num = 3/2")
		{
			REQUIRE(num.GetNumerator() == 3);
			REQUIRE(num.GetDenominator() == 2);
			REQUIRE(num.ToDouble() == static_cast<double>(3) / 2);
		}
	}

	WHEN("/=")
	{
		CRational num1(1, 2);
		CRational num2(2, 3);
		num1 /= num2;
		THEN("num1 = 3/4")
		{
			REQUIRE(num1.GetNumerator() == 3);
			REQUIRE(num1.GetDenominator() == 4);
			REQUIRE(num1.ToDouble() == static_cast<double>(3) / 4);
		}
	}

	WHEN("num /= int")
	{
		CRational num(1, 2);
		num /= 2;
		THEN("res = 1/4")
		{
			REQUIRE(num.GetNumerator() == 1);
			REQUIRE(num.GetDenominator() == 4);
			REQUIRE(num.ToDouble() == static_cast<double>(1) / 4);
		}
	}
}

TEST_CASE("==, !=")
{
	WHEN("==")
	{
		CRational num1(1, 2);
		CRational num2(1, 2);
		THEN("num1 equal num2")
		{
			REQUIRE(num1 == num2);
		}
	}

	WHEN("== int")
	{
		CRational num(3, 1);
		THEN("num equal 3")
		{
			REQUIRE(num == 3);
		}
	}

	WHEN("int ==")
	{
		CRational num(3, 1);
		THEN("num equal 3")
		{
			REQUIRE(3 == num);
		}
	}
	WHEN("nums are not equal")
	{
		CRational num1(1, 2);
		CRational num2(2, 3);
		THEN("it returns false")
		{
			REQUIRE(!(num1 == num2));
		}
	}

	WHEN("!=")
	{
		CRational num1(1, 2);
		CRational num2(5, 2);
		THEN("num1 not equal num2")
		{
			REQUIRE(num1 != num2);
		}
	}

	WHEN("!= int")
	{
		CRational num(1, 2);
		THEN("num not equal 7")
		{
			REQUIRE(num != 7);
		}
	}

	WHEN("int !=")
	{
		CRational num(1, 2);
		THEN("num not equal 7")
		{
			REQUIRE(7 != num);
		}
	}

	WHEN("nums are equal")
	{
		CRational num1(1, 2);
		CRational num2(1, 2);
		THEN("it returns false")
		{
			REQUIRE(!(num1 != num2));
		}
	}
}

TEST_CASE("<, <=, >, >=")
{
	WHEN(">=")
	{
		CRational num1(1, 2);
		CRational num2(1, 3);
		THEN("num1 >= num2")
		{
			REQUIRE(num1 >= num2);
		}

		CRational num3(1, 2);
		CRational num4(1, 2);
		THEN("num3 >= num4")
		{
			REQUIRE(num3 >= num4);
		}

		CRational num5(1, 3);
		CRational num6(1, 2);
		THEN("num5 >= num6 - false")
		{
			REQUIRE(!(num5 >= num6));
		}
	}

	WHEN("int >=")
	{
		CRational num(4, 2);
		THEN("3 >= num")
		{
			REQUIRE(3 >= num);
		}
		THEN("2 >= num")
		{
			REQUIRE(2 >= num);
		}
		THEN("1 >= num - false")
		{
			REQUIRE(!(1 >= num));
		}
	}

	WHEN("<=")
	{
		CRational num1(1, 3);
		CRational num2(1, 2);
		THEN("num1 <= num2")
		{
			REQUIRE(num1 <= num2);
		}

		CRational num3(1, 2);
		CRational num4(1, 2);
		THEN("num3 <= num4")
		{
			REQUIRE(num3 <= num4);
		}

		CRational num5(1, 2);
		CRational num6(1, 3);
		THEN("num5 <= num6 - false")
		{
			REQUIRE(!(num5 <= num6));
		}
	}

	WHEN("int <=")
	{
		CRational num(4, 2);
		THEN("1 <= num")
		{
			REQUIRE(1 <= num);
		}
		THEN("2 <= num")
		{
			REQUIRE(2 <= num);
		}
		THEN("3 <= num - false")
		{
			REQUIRE(!(3 <= num));
		}
	}

	WHEN(">")
	{
		CRational num1(1, 2);
		CRational num2(1, 3);
		THEN("num1 > num2")
		{
			REQUIRE(num1 > num2);
		}

		CRational num3(1, 2);
		CRational num4(1, 2);
		THEN("num3 > num4")
		{
			REQUIRE(!(num3 > num4));
		}

		CRational num5(1, 3);
		CRational num6(1, 2);
		THEN("num5 > num6 - false")
		{
			REQUIRE(!(num5 >= num6));
		}
	}

	WHEN("<")
	{
		CRational num1(1, 3);
		CRational num2(1, 2);
		THEN("num1 < num2")
		{
			REQUIRE(num1 < num2);
		}

		CRational num3(1, 2);
		CRational num4(1, 2);
		THEN("num3 < num4")
		{
			REQUIRE(!(num3 < num4));
		}

		CRational num5(1, 2);
		CRational num6(1, 3);
		THEN("num5 < num6 - false")
		{
			REQUIRE(!(num5 < num6));
		}
	}
}

TEST_CASE("<< >>")
{
	WHEN("<<")
	{
		CRational number(-7, 15);
		std::ostringstream output("");
		output << number;
		THEN("in output will be -7/15")
		{
			output.str() = "-7/15";
		}
	}

	WHEN(">>")
	{
		CRational number;
		std::istringstream input("7/15");
		input >> number;
		THEN("in number will numerator = 7, denominator = 15")
		{
			REQUIRE(number.GetNumerator() == 7);
			REQUIRE(number.GetDenominator() == 15);
		}
	}
}

TEST_CASE("Compound Fraction")
{
	WHEN("positive number")
	{
		CRational number(4, 3);
		std::pair<int, CRational> result = number.ToCompoundFraction();
		THEN("integer part is 1, fraction part is 1/3")
		{
			REQUIRE(result.first == 1);
			REQUIRE(result.second.GetNumerator() == 1);
			REQUIRE(result.second.GetDenominator() == 3);
		}
	}

	WHEN("Negative number")
	{
		CRational number(-9, 4);
		std::pair<int, CRational> result = number.ToCompoundFraction();
		THEN("integer part is -2, fraction part is -1/4")
		{
			REQUIRE(result.first == -2);
			REQUIRE(result.second.GetNumerator() == -1);
			REQUIRE(result.second.GetDenominator() == 4);
		}
	}

	WHEN("Whole part is not exists")
	{
		CRational number(3, 4);
		std::pair<int, CRational> result = number.ToCompoundFraction();
		THEN("integer part is 0, fraction part is 3/4")
		{
			REQUIRE(result.first == 0);
			REQUIRE(result.second.GetNumerator() == 3);
			REQUIRE(result.second.GetDenominator() == 4);
		}
	}
}