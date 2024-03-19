// HtmlDecode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../HtmlDecode/HtmlDecode.h"

SCENARIO("Decode empty string gives empty string")
{
	REQUIRE(HtmlDecode("").empty());
}

SCENARIO("Decode string without html-tags gives same string")
{
	std::string str = "abcde";
	REQUIRE(HtmlDecode(str) == str);
}

SCENARIO("Decode string with html-tags gives new string")
{
	std::string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string newStr = "Cat <says> \"Meow\". M&M\'s";
	REQUIRE(HtmlDecode(str) == newStr);
}

SCENARIO("Decode string with non-html-tags gives new string")
{
	std::string str = "&quot;Meow&quot";
	std::string newStr = "\"Meow&quot";
	REQUIRE(HtmlDecode(str) == newStr);
}

SCENARIO("Decode string with many ampersands and html-tags gives new string with many ampersands")
{
	std::string str = "&&&&&&amp;";
	std::string newStr = "&&&&&&";
	REQUIRE(HtmlDecode(str) == newStr);
}