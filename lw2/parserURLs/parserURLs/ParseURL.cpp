#include "ParseURL.h"

const std::string URL_REGULAR = R"(^([A-z]*):\/\/([^\/:]+\.[^\/:]+)(?::(\d+))?([\/](.*))?$)";
const int PORT_MIN = 1;
const int PORT_MAX = 65535;
const std::string HTTP = "http";
const std::string HTTPS = "https";
const std::string FTP = "ftp";


bool ParseProtocol(const std::string& protocolStr, Protocol& protocol)
{
    std::string protocolLowerCase = protocolStr;
    std::transform(protocolLowerCase.begin(), protocolLowerCase.end(), protocolLowerCase.begin(),
        [](unsigned char ch) { return std::tolower(ch); });

    if (protocolLowerCase == HTTP)
    {
        protocol = Protocol::HTTP;
        return true;
    }
    else if (protocolLowerCase == HTTPS)
    {
        protocol = Protocol::HTTPS;
        return true;
    }
    else if (protocolLowerCase == FTP)
    {
        protocol = Protocol::FTP;
        return true;
    }

    return false;
}

bool ParseHost(const std::string& hostStr, std::string& host)
{
    if (hostStr.empty())
    {
        return false;
    }

    host = hostStr;
    return true;
}

bool IsValidPort(const std::string& portStr, int& port)
{
    try
    {
        port = std::stoi(portStr);
        if (port < PORT_MIN || port > PORT_MAX)
        {
            return false;
        }

        return true;
    }
    catch (std::invalid_argument &error)
    {
        return false;
    }
}

bool ParsePort(const std::string& portStr, Protocol& protocol, int& port)
{
    if (portStr.empty())
    {
        if (protocol == Protocol::HTTP)
        {
            port = HTTP_PORT;
            return true;
        }
        else if (protocol == Protocol::HTTPS)
        {
            port = HTTPS_PORT;
            return true;
        }
        else if (protocol == Protocol::FTP)
        {
            port = FTP_PORT;
            return true;
        }
    }

    return IsValidPort(portStr, port);
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
    std::regex pattern(URL_REGULAR);
    std::smatch matches;

    if (std::regex_match(url, matches, pattern))
    {
        bool isProtocolParsed = ParseProtocol(matches[1], protocol);
        bool isHostParsed = ParseHost(matches[2], host);
        bool isPortParsed = ParsePort(matches[3], protocol, port);
        document = matches[5];
        return isProtocolParsed && isHostParsed && isPortParsed;
    }
    return false;
}

void PrintURLParts(int port, const std::string& host, const std::string& document)
{
    std::cout << "HOST: " << host << std::endl;
    std::cout << "PORT: " << port << std::endl;
    std::cout << "DOC: " << document << std::endl;
}