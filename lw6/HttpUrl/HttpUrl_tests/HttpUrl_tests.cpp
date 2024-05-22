// HttpUrl_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../HttpUrl/CHttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"

TEST_CASE("Create CHttpUrl by Protocol, domain, port and document")
{
	WHEN("all fields ok")
	{
		CHttpUrl url("domain.com", "/doc", Protocol::HTTP, 300);
		THEN("it creates class and fields")
		{
			CHECK(url.GetURL() == "http://domain.com:300/doc");
			CHECK(url.GetDomain() == "domain.com");
			CHECK(url.GetDocument() == "/doc");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetPort() == 300);
		}
	}

	WHEN("doc without /")
	{
		CHttpUrl url("domain.com", "doc", Protocol::HTTP, 300);
		THEN("it creates class and fields")
		{
			REQUIRE(url.GetURL() == "http://domain.com:300/doc");
			REQUIRE(url.GetDocument() == "/doc");
		}
	}

	WHEN("doc is empty")
	{
		CHttpUrl url("domain.com", "", Protocol::HTTP, 300);
		THEN("it creates class and fields")
		{
			REQUIRE(url.GetURL() == "http://domain.com:300/");
			REQUIRE(url.GetDocument() == "/");
		}
	}

	WHEN("port < min port")
	{
		THEN("throws exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("domain.com", "doc", Protocol::HTTP, 0), std::invalid_argument);
		}
	}
}

TEST_CASE("Create CHttpUrl by Protocol, domain and document")
{
	WHEN("protocol https")
	{
		CHttpUrl url("domain.com", "/doc", Protocol::HTTPS);
		THEN("port is 443")
		{
			REQUIRE(url.GetURL() == "https://domain.com/doc");
			REQUIRE(url.GetPort() == 443);
		}
	}

	WHEN("protocol http")
	{
		CHttpUrl url("domain.com", "/doc", Protocol::HTTP);
		THEN("port is 80")
		{
			REQUIRE(url.GetURL() == "http://domain.com/doc");
			REQUIRE(url.GetPort() == 80);
		}
	}
}

TEST_CASE("Create CHttpUrl by url")
{
	WHEN("url ok with http protocol")
	{
		CHttpUrl url("http://domain.com:300/doc");
		THEN("it is ok")
		{
			REQUIRE(url.GetURL() == "http://domain.com:300/doc");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "domain.com");
			REQUIRE(url.GetPort() == 300);
			REQUIRE(url.GetDocument() == "/doc");
		}
	}

	WHEN("url ok with https protocol")
	{
		CHttpUrl url("https://domain.com:300/doc");
		THEN("it is ok")
		{
			REQUIRE(url.GetURL() == "https://domain.com:300/doc");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "domain.com");
			REQUIRE(url.GetPort() == 300);
			REQUIRE(url.GetDocument() == "/doc");
		}
	}

	WHEN("url ok with https protocol in not in lower case")
	{
		CHttpUrl url("hTtPs://domain.com:300/doc");
		THEN("it is ok")
		{
			REQUIRE(url.GetURL() == "https://domain.com:300/doc");
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	WHEN("url ok with http protocol in not in lower case")
	{
		CHttpUrl url("hTtP://domain.com:300/doc");
		THEN("it is ok")
		{
			REQUIRE(url.GetURL() == "http://domain.com:300/doc");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
	}

	WHEN("url without port")
	{
		CHttpUrl url("http://domain.com/doc");
		THEN("it is ok, port is default")
		{
			REQUIRE(url.GetURL() == "http://domain.com/doc");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "domain.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/doc");
		}
	}

	WHEN("url without doc")
	{
		CHttpUrl url("http://domain.com:300");
		THEN("all is ok, doc = /")
		{
			REQUIRE(url.GetURL() == "http://domain.com:300/");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "domain.com");
			REQUIRE(url.GetPort() == 300);
			REQUIRE(url.GetDocument() == "/");
		}
	}

	WHEN("url without doc and port")
	{
		CHttpUrl url("http://domain.com");
		THEN("all is ok, port is default, document = /")
		{
			REQUIRE(url.GetURL() == "http://domain.com/");
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetDomain() == "domain.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/");
		}
	}

	WHEN("not url")
	{
		THEN("thrown CUrlParsingError exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("url"), CUrlParsingError);
		}
	}

	WHEN("url has invalid symbols between protocol and domain")
	{
		THEN("thrown CUrlParsingError exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http:/sas/domain:300/doc"), CUrlParsingError);
		}
	}

	WHEN("protocol is invalid")
	{
		THEN("thrown CUrlParsingError exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("ftp://domain:300/doc"), CUrlParsingError);
		}
	}

	WHEN("domain is invalid")
	{
		THEN("thrown CUrlParsingError exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://domain:300/doc"), CUrlParsingError);
		}
	}

	WHEN("port < min port")
	{
		THEN("thrown CUrlParsingError exception")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://domain.com:0/doc"), CUrlParsingError);
		}
	}
}