// parserURLs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "ParseURL.h"

const std::string EXIT = "...";
const std::string INVALID_URL = "Invalid URL";

int main()
{
    std::string url;
    Protocol protocol;
    int port;
    std::string host;
    std::string document;
    while (std::getline(std::cin, url))
    {
        if (url.empty())
        {
            continue;
        }
        if (url == EXIT)
        {
            return 0;
        }
        if (ParseURL(url, protocol, port, host, document))
        {
            PrintURLParts(port, host, document);
        }
        else
        {
            std::cout << INVALID_URL << std::endl;
        }
    }
    return 0;
}