// StringList_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../StringList/CStringList.h"
#include "../../../catch.hpp"

TEST_CASE("Constructors")
{
	WHEN("default constructor")
	{
		CStringList list;
		THEN("list is empty, size = 0")
		{
			REQUIRE(list.Empty());
			REQUIRE(list.GetSize() == 0);
		}
	}

	WHEN("copy constructor")
	{
		CStringList list;
		list.PushBack("1");
		CStringList newList(list);

		THEN("list = newList, list not empty")
		{
			REQUIRE(!list.Empty());
			REQUIRE(!newList.Empty());
			auto iter1 = list.begin();
			auto iter2 = newList.begin();
			REQUIRE(*iter1 == *iter2);
		}
	}

	WHEN("move constructor")
	{
		CStringList list;
		list.PushBack("1");
		CStringList newList(std::move(list));

		THEN("list = newList, list not empty")
		{
			REQUIRE(list.Empty());
			REQUIRE(!newList.Empty());
			auto iter2 = newList.begin();
			REQUIRE(*iter2 == "1");
		}
	}
}

TEST_CASE("=")
{
	WHEN("copy =")
	{
		CStringList list;
		list.PushBack("1");
		CStringList newList = list;

		THEN("list = newList, list not empty")
		{
			REQUIRE(!list.Empty());
			REQUIRE(!newList.Empty());
			auto iter1 = list.begin();
			auto iter2 = newList.begin();
			REQUIRE(*iter1 == *iter2);
		}
	}

	WHEN("move =")
	{
		CStringList list;
		list.PushBack("1");
		CStringList newList = std::move(list);

		THEN("list = newList, list not empty")
		{
			REQUIRE(list.Empty());
			REQUIRE(!newList.Empty());
			auto iter2 = newList.begin();
			REQUIRE(*iter2 == "1");
		}
	}
}

TEST_CASE("Get iterator to begin and rbegin")
{
	WHEN("begin()")
	{
		CStringList list;
		list.PushFront("str2");
		list.PushFront("str1");

		auto iter = list.begin();
		THEN("str of iter = str1")
		{
			REQUIRE(*iter == "str1");
		}
	}

	WHEN("rbegin()")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");

		auto iter = list.rbegin();
		THEN("str of iter = str2")
		{
			REQUIRE(*iter == "str2");
		}
	}
}

TEST_CASE("Iterator")
{
	WHEN("iterator > size")
	{
		CStringList list;
		list.PushBack("str1");
		THEN("thrown exception")
		{
			auto iter = list.begin();
			iter++;
			REQUIRE_THROWS(iter++);
		}
	}
}

TEST_CASE("Insert str in pos by iter")
{
	WHEN("pos < size")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str3");

		auto iter = list.begin();
		iter++;
		list.Insert(iter, "str2");

		THEN("str2 between str1 and str3")
		{
			iter = list.begin();
			REQUIRE(*iter == "str1");
			iter++;
			REQUIRE(*iter == "str2");
			iter++;
			REQUIRE(*iter == "str3");
			iter++;

			REQUIRE(list.GetSize() == 3);
		}
	}

	WHEN("pos = size")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");

		auto pos = list.end();
		list.Insert(pos, "str");
		THEN("str is in the end")
		{
			auto iter = list.rbegin();
			REQUIRE(*iter == "str");
		}
	}
}

TEST_CASE("Erase str in pos by iter")
{
	WHEN("pos < size")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");
		list.PushBack("str3");

		auto pos = list.begin();
		pos++;
		list.Erase(pos);
		THEN("str2 erased")
		{
			auto iter = list.begin();
			REQUIRE(*iter == "str1");
			iter++;
			REQUIRE(*iter == "str3");
			REQUIRE(list.GetSize() == 2);
		}
	}

	WHEN("pos = size")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");
		list.PushBack("str3");
		THEN("thrown exception")
		{
			auto iter = list.end();
			REQUIRE_THROWS_AS(list.Erase(iter), CStringListOutOfRangeException);
		}
	}

	WHEN("erase first")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");
		list.PushBack("str3");
		list.Erase(list.begin());
		THEN("first element is str2")
		{
			REQUIRE(*list.begin() == "str2");
		}
	}
}

TEST_CASE("Clear")
{
	WHEN("list empty")
	{
		CStringList list;
		list.Clear();
		THEN("it is ok")
		{
			REQUIRE(list.Empty());
		}
	}

	WHEN("list not empty")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");
		list.Clear();
		THEN("it is ok")
		{
			REQUIRE(list.Empty());
		}
	}
}

TEST_CASE("Range-based for")
{
	WHEN("Get all strings and add to one string")
	{
		std::string str1 = "str1";
		std::string str2 = "str2";
		std::string str3 = "str3";
		std::string str4 = "str4";
		CStringList list;
		list.PushBack(str1);
		list.PushBack(str2);
		list.PushBack(str3);
		list.PushBack(str4);
		std::string sum = str1 + str2 + str3 + str4;
		std::string result;
		for (auto iter = list.begin(); iter != list.end(); iter++)
		{
			result += *iter;
		}
		THEN("sum == result")
		{
			REQUIRE(sum == result);
		}
	}

	WHEN("Get all strings reversed and add to one string ")
	{
		std::string str1 = "str1";
		std::string str2 = "str2";
		std::string str3 = "str3";
		std::string str4 = "str4";
		CStringList list;
		list.PushBack(str1);
		list.PushBack(str2);
		list.PushBack(str3);
		list.PushBack(str4);
		std::string sum = str4 + str3 + str2 + str1;
		std::string result;
		for (auto iter = list.rbegin(); iter != list.rend(); iter++)
		{
			result += *iter;
		}
		THEN("sum == result")
		{
			REQUIRE(sum == result);
		}
	}
}

TEST_CASE("Change element by iterator")
{
	WHEN("set new str by iterator")
	{
		CStringList list;
		list.PushBack("str1");
		list.PushBack("str2");
		auto iter = list.begin();
		++iter;
		THEN("str2 will changed")
		{
			REQUIRE(*iter == "str2");
			*iter = "new str";
			REQUIRE(*iter == "new str");
		}
	}
}