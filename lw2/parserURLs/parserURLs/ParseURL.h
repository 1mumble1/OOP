#pragma once
#include <string>
#include <iostream>
#include <regex>

const int HTTP_PORT = 80;
const int HTTPS_PORT = 443;
const int FTP_PORT = 21;

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintURLParts(int port, const std::string& host, const std::string& document);