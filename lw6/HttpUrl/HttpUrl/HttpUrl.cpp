// HttpUrl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CUrlParsingError.h"
#include "CHttpUrl.h"

int main()
{
	std::string url;
	while (std::getline(std::cin, url))
	{
		try
		{

			if (url.empty())
			{
				continue;
			}
			CHttpUrl parsedUrl(url);
			std::cout << parsedUrl.GetURL() << std::endl;
			std::cout << "PROTOCOL: " << parsedUrl.GetProtocolString() << std::endl;
			std::cout << "DOMAIN: " << parsedUrl.GetDomain() << std::endl;
			std::cout << "PORT: " << parsedUrl.GetPort() << std::endl;
			std::cout << "DOC: " << parsedUrl.GetDocument() << std::endl;
		}
		catch (CUrlParsingError const& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	return 0;
}