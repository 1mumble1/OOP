#include "CHttpUrl.h"

const std::string URL_REGULAR = R"(^([A-z]*):\/\/([^\/:]+\.[^\/:]+)(?::(\d+))?([\/].*)?$)";

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex pattern(URL_REGULAR);
	std::smatch matches;

	if (!std::regex_match(url, matches, pattern))
	{
		throw CUrlParsingError("Invalis URL. Usage: protocol://host[:port][/document]");
	}

	std::string protocol = matches[1];
	std::transform(protocol.begin(), protocol.end(), protocol.begin(),
		[](unsigned char ch) { return std::tolower(ch); });
	std::string domain = matches[2];
	std::string port = matches[3];
	std::string document = matches[4];

	if (!IsValidProtocol(protocol))
	{
		throw CUrlParsingError("Invalid protocol.");
	}

	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError("Invalid domain.");
	}

	if (!ParsePort(port))
	{
		throw CUrlParsingError("Invalid port.");
	}

	m_document = document.empty() ? "/" : document;
}

bool CHttpUrl::IsValidProtocol(const std::string& protocolStr)
{
	std::string protocolLowerCase = protocolStr;
	std::transform(protocolLowerCase.begin(), protocolLowerCase.end(), protocolLowerCase.begin(),
		[](unsigned char ch) { return std::tolower(ch); });

	if (protocolLowerCase == HTTP)
	{
		m_protocol = Protocol::HTTP;
		return true;
	}
	else if (protocolLowerCase == HTTPS)
	{
		m_protocol = Protocol::HTTPS;
		return true;
	}

	return false;
}

bool CHttpUrl::IsValidDomain(const std::string& domainStr)
{
	if (domainStr.empty())
	{
		return false;
	}

	m_domain = domainStr;
	return true;
}

bool CHttpUrl::ParsePort(const std::string& portStr)
{
	if (portStr.empty())
	{
		if (m_protocol == Protocol::HTTP)
		{
			m_port = HTTP_PORT;
			return true;
		}
		else if (m_protocol == Protocol::HTTPS)
		{
			m_port = HTTPS_PORT;
			return true;
		}
	}

	return IsValidPort(portStr);
}

bool CHttpUrl::IsValidPort(const std::string& portStr)
{
	try
	{
		m_port = std::stoi(portStr);
		if (m_port < PORT_MIN || m_port > PORT_MAX)
		{
			return false;
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol)
{
	if (!IsValidDomain(domain))
	{
		throw std::invalid_argument("Invalid domain.");
	}

	m_protocol = protocol;
	m_document += (document[0] == '/' ? document : '/' + document);
	m_port = protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT;
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
{
	if (!IsValidDomain(domain))
	{
		throw std::invalid_argument("Invalid domain.");
	}

	if (port < PORT_MIN || port > PORT_MAX)
	{
		throw std::invalid_argument("Invalid port.");
	}

	m_protocol = protocol;
	m_document = (document[0] == '/' ? document : '/' + document);
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string port = "0";
	if ((m_protocol == Protocol::HTTP && m_port != HTTP_PORT) ||
		(m_protocol == Protocol::HTTPS && m_port != HTTPS_PORT))
	{
		port = std::to_string(m_port);
	}

	return GetProtocolString() + "://" + m_domain + (port == "0" ? "" : ":" + port) + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetProtocolString() const
{
	return m_protocol == Protocol::HTTP ? HTTP : HTTPS;
}
