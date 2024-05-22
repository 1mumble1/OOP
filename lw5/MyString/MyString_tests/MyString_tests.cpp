// MyString_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../MyString/CMyString.h"
#include "../../../catch.hpp"

TEST_CASE("Create string")
{
	WHEN("default constructor")
	{
		CMyString str;
		THEN("length = 0, string is empty")
		{
			REQUIRE(str.GetLength() == 0);
			REQUIRE(std::string(str.GetStringData()).empty());
		}
	}

	WHEN("constructor with char*")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		THEN("str will has \0 end-symbol and length = text.length")
		{
			REQUIRE(strcmp(str.GetStringData(), chs) == 0);
			REQUIRE(str.GetLength() == strlen(chs));
		}
	}

	WHEN("constructor with char* and \0 in the middle")
	{
		const char* chs = "hello \0world";
		CMyString str = CMyString(chs);
		THEN("str will has \0 end-symbol and length = text.length")
		{
			REQUIRE(strcmp(str.GetStringData(), chs) == 0);
			REQUIRE(str.GetLength() == strlen(chs));
		}
	}

	WHEN("constructor with char* and length")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs, strlen(chs));
		THEN("str will has \0 end-symbol and length = text.length")
		{
			REQUIRE(strcmp(str.GetStringData(), chs) == 0);
			REQUIRE(str.GetLength() == strlen(chs));
		}
	}

	WHEN("copy constructor")
	{
		const char* chs = "hello world";
		CMyString str1 = CMyString(chs);
		CMyString str2 = CMyString(str1);
		THEN("str2 equal str1")
		{
			REQUIRE(str1.GetLength() == str2.GetLength());
			REQUIRE(strcmp(str1.GetStringData(), str2.GetStringData()) == 0);
		}
	}

	WHEN("move constructor")
	{
		const char* chs = "hello world";
		CMyString str1(chs);
		CMyString str2 = std::move(str1);
		THEN("str2 equal mystr1, but str1 is empty")
		{
			REQUIRE(str1.GetLength() == 0);
			REQUIRE(strcmp(str1.GetStringData(), "") == 0);
			REQUIRE(strcmp(str2.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("constructor with STL string")
	{
		std::string text = "hello world";
		CMyString str(text);
		THEN("str equal STL text")
		{
			REQUIRE(str.GetLength() == text.size());
			REQUIRE(strcmp(str.GetStringData(), text.c_str()) == 0);
		}
	}

	WHEN("constructor with STL string with \0 in the middle")
	{
		std::string text = "hello\0 world";
		CMyString str(text);
		THEN("str equal STL text")
		{
			REQUIRE(str.GetLength() == text.size());
			REQUIRE(strcmp(str.GetStringData(), text.c_str()) == 0);
		}
	}
}

TEST_CASE("Get substr")
{
	WHEN("get substr success")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		CMyString substr = str.SubString(6, 5);
		THEN("substr is correct")
		{
			REQUIRE(strcmp(substr.GetStringData(), "world") == 0);
		}
	}

	WHEN("start pos > length of str")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		THEN("will be thrown an exception")
		{
			REQUIRE_THROWS_WITH(str.SubString(15, 5), "Invalid value of start position: it is out of range.");
		}
	}

	WHEN("start pos is negative")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		THEN("will be thrown an exception")
		{
			REQUIRE_THROWS_WITH(str.SubString(-6, 5), "Invalid value of start position: it is out of range.");
		}
	}

	WHEN("length of substr > length of str - start")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		CMyString substr = str.SubString(6, 10);
		THEN("substr contains symbols to the end of str")
		{
			REQUIRE(strcmp(substr.GetStringData(), "world") == 0);
		}
	}

	WHEN("length of substr < 0")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		CMyString substr = str.SubString(6, -10);
		THEN("substr contains symbols to the end of str")
		{
			REQUIRE(strcmp(substr.GetStringData(), "world") == 0);
		}
	}
}

TEST_CASE("Clear string")
{
	WHEN("str is empty")
	{
		CMyString str;
		str.Clear();
		THEN("str is empty")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("str non empty")
	{
		const char* chs = "hello world";
		CMyString str = CMyString(chs);
		str.Clear();
		THEN("str will empty")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
			REQUIRE(str.GetLength() == 0);
		}
	}
}

TEST_CASE("Operator =")
{
	WHEN("str1 = with copy str2")
	{
		const char* chs = "hello world";
		CMyString str1;
		CMyString str2(chs);
		str1 = str2;
		THEN("str1 will contains symbols from str2")
		{
			REQUIRE(strcmp(str1.GetStringData(), "hello world") == 0);
			REQUIRE(strcmp(str2.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("str = self")
	{
		CMyString str("hello world");
		str = str;
		THEN("nothing")
		{
			REQUIRE(strcmp(str.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("str1 = with move str2")
	{
		const char* chs = "hello world";
		CMyString str1;
		CMyString str2(chs);
		str1 = std::move(str2);
		THEN("str2 equal str1, but str1 is empty")
		{
			REQUIRE(str2.GetLength() == 0);
			REQUIRE(strcmp(str2.GetStringData(), "") == 0);
			REQUIRE(strcmp(str1.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("str move self")
	{
		CMyString str = CMyString("hello world");
		str = std::move(str);
		THEN("nothing")
		{
			REQUIRE(strcmp(str.GetStringData(), "hello world") == 0);
		}
	}
}

TEST_CASE("Operator +")
{
	WHEN("str + str")
	{
		CMyString str1("hello ");
		CMyString str2("world");
		CMyString result = str1 + str2;
		THEN("result equal to concat (hello world)")
		{
			REQUIRE(strcmp(result.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("STL string + str")
	{
		std::string str1 = "hello ";
		CMyString str2("world");
		CMyString result = str1 + str2;
		THEN("result equal to concat (hello world)")
		{
			REQUIRE(strcmp(result.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("str + STL string")
	{
		std::string str1 = "world";
		CMyString str2("hello ");
		CMyString result = str2 + str1;
		THEN("result equal to concat (hello world)")
		{
			REQUIRE(strcmp(result.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("char* + str")
	{
		const char* chs = "hello ";
		CMyString str("world");
		CMyString result = chs + str;
		THEN("result equal to concat (hello world)")
		{
			REQUIRE(strcmp(result.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("str + char*")
	{
		const char* chs = "world";
		CMyString str("hello ");
		CMyString result = str + chs;
		THEN("result equal to concat (hello world)")
		{
			REQUIRE(strcmp(result.GetStringData(), "hello world") == 0);
		}
	}
}

TEST_CASE("Operator +=")
{
	WHEN("success concatination")
	{
		CMyString str1("hello ");
		CMyString str2("world");
		str1 += str2;
		THEN("str equal to concat (hello world)")
		{
			REQUIRE(strcmp(str1.GetStringData(), "hello world") == 0);
		}
	}

	WHEN("str += empty")
	{
		CMyString str1("hello ");
		CMyString str2;
		str1 += str2;
		THEN("str1 not change")
		{
			REQUIRE(strcmp(str1.GetStringData(), "hello ") == 0);
		}
	}

	WHEN("empty += str")
	{
		CMyString str1;
		CMyString str2("world");
		str1 += str2;
		THEN("str1 contain symbols from str2")
		{
			REQUIRE(strcmp(str1.GetStringData(), "world") == 0);
		}
	}

	WHEN("capacity < length of str2")
	{
		CMyString str1("h");
		CMyString str2("ello world");
		str1 += str2;
		THEN("capicity will raise")
		{
			REQUIRE(str1.GetCapacity() == 22);
			REQUIRE(strcmp(str1.GetStringData(), "hello world") == 0);
		}
	}
}

TEST_CASE("Operator ==")
{
	WHEN("str are equal")
	{
		CMyString str1("hell");
		CMyString str2("hell");
		THEN("returns true")
		{
			REQUIRE(str1 == str2);
		}
	}

	WHEN("str are different in lengths")
	{
		CMyString str1("hell");
		CMyString str2("hello");
		THEN("returns false")
		{
			REQUIRE(!(str1 == str2));
		}
	}

	WHEN("str are different in chars")
	{
		CMyString str1("hell");
		CMyString str2("worl");
		THEN("returns false")
		{
			REQUIRE(!(str1 == str2));
		}
	}
}

TEST_CASE("Operator !=")
{
	WHEN("str are equal")
	{
		CMyString str1("hell");
		CMyString str2("hell");
		THEN("returns false")
		{
			REQUIRE(!(str1 != str2));
		}
	}

	WHEN("str are different in lengths")
	{
		CMyString str1("hell");
		CMyString str2("hello");
		THEN("returns true")
		{
			REQUIRE(str1 != str2);
		}
	}

	WHEN("str are different in chars")
	{
		CMyString str1("hell");
		CMyString str2("worl");
		THEN("returns true")
		{
			REQUIRE(str1 != str2);
		}
	}
}

TEST_CASE("Operator <")
{
	WHEN("str1 < str2")
	{
		CMyString str1("abcd");
		CMyString str2("xyz");
		THEN("returns true")
		{
			REQUIRE(str1 < str2);
		}
	}

	WHEN("str1 > str2")
	{
		CMyString str1("xyz");
		CMyString str2("abcd");
		THEN("returns false")
		{
			REQUIRE(!(str1 < str2));
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("xyz");
		CMyString str2("xyz");
		THEN("returns false")
		{
			REQUIRE(!(str1 < str2));
		}
	}

	WHEN("substr1 = str2 and str1 length > str2 length")
	{
		CMyString str1("xyzz");
		CMyString str2("xyz");
		THEN("returns false")
		{
			REQUIRE(!(str1 < str2));
		}
	}

	WHEN("str1 = substr2 and str2 length > str1 length")
	{
		CMyString str1("xyz");
		CMyString str2("xyzz");
		THEN("returns true")
		{
			REQUIRE(str1 < str2);
		}
	}
}

TEST_CASE("Operator >")
{
	WHEN("str1 < str2")
	{
		CMyString str1("abcd");
		CMyString str2("xyz");
		THEN("returns false")
		{
			REQUIRE(!(str1 > str2));
		}
	}

	WHEN("str1 > str2")
	{
		CMyString str1("xyz");
		CMyString str2("abcd");
		THEN("returns true")
		{
			REQUIRE(str1 > str2);
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("xyz");
		CMyString str2("xyz");
		THEN("returns false")
		{
			REQUIRE(!(str1 > str2));
		}
	}

	WHEN("substr1 = str2 and str1 length > str2 length")
	{
		CMyString str1("xyzz");
		CMyString str2("xyz");
		THEN("returns true")
		{
			REQUIRE(str1 > str2);
		}
	}

	WHEN("str1 = substr2 and str2 length > str1 length")
	{
		CMyString str1("xyz");
		CMyString str2("xyzz");
		THEN("returns false")
		{
			REQUIRE(!(str1 > str2));
		}
	}
}

TEST_CASE("Operator <=")
{
	WHEN("str1 < str2")
	{
		CMyString str1("abcd");
		CMyString str2("xyz");
		THEN("returns true")
		{
			REQUIRE(str1 <= str2);
		}
	}

	WHEN("str1 > str2")
	{
		CMyString str1("xyz");
		CMyString str2("abcd");
		THEN("returns false")
		{
			REQUIRE(!(str1 <= str2));
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("xyz");
		CMyString str2("xyz");
		THEN("returns true")
		{
			REQUIRE(str1 <= str2);
		}
	}

	WHEN("substr1 = str2 and str1 length > str2 length")
	{
		CMyString str1("xyzz");
		CMyString str2("xyz");
		THEN("returns false")
		{
			REQUIRE(!(str1 <= str2));
		}
	}

	WHEN("str1 = substr2 and str2 length > str1 length")
	{
		CMyString str1("xyz");
		CMyString str2("xyzz");
		THEN("returns true")
		{
			REQUIRE(str1 <= str2);
		}
	}
}

TEST_CASE("Operator >=")
{
	WHEN("str1 < str2")
	{
		CMyString str1("abcd");
		CMyString str2("xyz");
		THEN("returns false")
		{
			REQUIRE(!(str1 >= str2));
		}
	}

	WHEN("str1 > str2")
	{
		CMyString str1("xyz");
		CMyString str2("abcd");
		THEN("returns true")
		{
			REQUIRE(str1 >= str2);
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("xyz");
		CMyString str2("xyz");
		THEN("returns true")
		{
			REQUIRE(str1 >= str2);
		}
	}

	WHEN("substr1 = str2 and str1 length > str2 length")
	{
		CMyString str1("xyzz");
		CMyString str2("xyz");
		THEN("returns true")
		{
			REQUIRE(str1 >= str2);
		}
	}

	WHEN("str1 = substr2 and str2 length > str1 length")
	{
		CMyString str1("xyz");
		CMyString str2("xyzz");
		THEN("returns false")
		{
			REQUIRE(!(str1 >= str2));
		}
	}
}

TEST_CASE("Operator []")
{
	WHEN("index in range")
	{
		CMyString str("hello world");
		THEN("can get char")
		{
			REQUIRE(str[1] == 'e');
		}
	}

	WHEN("index not in range")
	{
		CMyString str("hello world");
		THEN("will be thrown an exception")
		{
			REQUIRE_THROWS_WITH(str[20], "Invalid value of index: it is out of range.");
			REQUIRE_THROWS_WITH(str[-8], "Invalid value of index: it is out of range.");
		}
	}

	WHEN("set new value")
	{
		CMyString str("hello world");
		str[4] = '0';
		THEN("get changed char")
		{
			REQUIRE(strcmp(str.GetStringData(), "hell0 world") == 0);
		}
	}

	WHEN("set index not in range")
	{
		CMyString str("hello world");
		THEN("will be thrown an exception")
		{
			REQUIRE_THROWS_WITH((str[20] = '0'), "Invalid value of index: it is out of range.");
			REQUIRE_THROWS_WITH((str[-8] = '0'), "Invalid value of index: it is out of range.");
		}
	}
}

TEST_CASE("Operator >>")
{
	WHEN("read to space")
	{
		std::istringstream in("hello world");
		CMyString str;
		in >> str;
		THEN("str contains only chars before space")
		{
			REQUIRE(strcmp(str.GetStringData(), "hello") == 0);
		}
	}

	WHEN("read to end of line")
	{
		std::istringstream in("hello\n world");
		CMyString str;
		in >> str;
		THEN("str contains only chars before end of line")
		{
			REQUIRE(strcmp(str.GetStringData(), "hello") == 0);
		}
	}

	WHEN("read to eof")
	{
		std::istringstream in("helloworld");
		CMyString str;
		in >> str;
		THEN("str contains only chars before eof")
		{
			REQUIRE(strcmp(str.GetStringData(), "helloworld") == 0);
		}
	}
}

TEST_CASE("Operator <<")
{
	WHEN("succes writting")
	{
		std::ostringstream out;
		CMyString str("hello world");
		out << str;
		THEN("write symbols from str")
		{
			REQUIRE(out.str() == str.GetStringData());
		}
	}

	WHEN("str is empty")
	{
		std::ostringstream out;
		CMyString str;
		out << str;
		THEN("ostream not change")
		{
			REQUIRE(out.str().empty());
		}
	}

	WHEN("str has null symbol inside")
	{
		std::ostringstream out;
		CMyString str("hello\0 world");
		out << str;
		THEN("write symbols from str")
		{
			REQUIRE(out.str() == str.GetStringData());
		}
	}
}