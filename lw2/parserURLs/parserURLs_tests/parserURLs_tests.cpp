#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../parserURLs/ParseURL.h"

SCENARIO("Parse empty URL gives false-result")
{
	std::string url = "";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	REQUIRE(!ParseURL(url, protocol, port, host, doc));
}

SCENARIO("Parse not URL gives false-result")
{
	std::string url = "abcd";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	REQUIRE(!ParseURL(url, protocol, port, host, doc));
}

SCENARIO("Parse URL with another protocol gives false-result")
{
	std::string url = "htp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	REQUIRE(!ParseURL(url, protocol, port, host, doc));
}

SCENARIO("Parse URL with protocol in enum gives true-result")
{
	std::string url = "https://www.mysite.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;
	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isProtocol = (protocol == Protocol::HTTPS);
	REQUIRE(parsed);
	REQUIRE(isProtocol);
}

SCENARIO("Parse URL with protocol in enum with CaMeL case gives true-result")
{
	std::string url = "HtTpS://www.mysite.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;
	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isProtocol = (protocol == Protocol::HTTPS);
	REQUIRE(parsed);
	REQUIRE(isProtocol);
}

SCENARIO("Parse URL without host gives false-result")
{
	std::string url = "http://";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	REQUIRE(!ParseURL(url, protocol, port, host, doc));
}

SCENARIO("Parse URL with host gives true-result")
{
	std::string url = "http://www.mysite.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isHost = (host == "www.mysite.com");
	REQUIRE(parsed);
	REQUIRE(isHost);
}

SCENARIO("Parse URL with non valid host gives true-result")
{
	std::string url = "http://mysite/";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	REQUIRE(!parsed);
}

SCENARIO("Parse URL with host and / gives true-result")
{
	std::string url = "http://www.mysite.com/";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isHost = (host == "www.mysite.com");
	REQUIRE(parsed);
	REQUIRE(isHost);
}

SCENARIO("Parse URL without port gives true-result and default port")
{
	std::string url = "http://www.mysite.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isPortDefault = (port == 80);
	REQUIRE(parsed);
	REQUIRE(isPortDefault);
}

SCENARIO("Parse URL with port gives true-result and not default port")
{
	std::string url = "http://www.mysite.com:3600";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isPortNotDefault = (port == 3600);
	REQUIRE(parsed);
	REQUIRE(isPortNotDefault);
}

SCENARIO("Parse URL with doc gives true-result and not empty doc")
{
	std::string url = "http://www.mysite.com/text.txt";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	bool isDoc = (doc == "text.txt");
	REQUIRE(parsed);
	REQUIRE(isDoc);
}

SCENARIO("Parse URL without doc gives true-result and empty doc")
{
	std::string url = "http://www.mysite.com";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	REQUIRE(parsed);
	REQUIRE(doc.empty());
}

SCENARIO("Parse URL without doc but with '/' gives true-result and empty doc")
{
	std::string url = "http://www.mysite.com/";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	REQUIRE(parsed);
	REQUIRE(doc.empty());
}

SCENARIO("Parse URL with 2 ports gives false-result")
{
	std::string url = "http://www.mysite.com:35:400";
	Protocol protocol;
	int port;
	std::string host;
	std::string doc;

	bool parsed = ParseURL(url, protocol, port, host, doc);
	REQUIRE(!parsed);
}
