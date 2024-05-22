#pragma once
#include <string>
#include <regex>
#include "CUrlParsingError.h"

const std::string HTTP = "http";
const std::string HTTPS = "https";
const unsigned short HTTP_PORT = 80;
const unsigned short HTTPS_PORT = 443;
const unsigned short PORT_MIN = 1;
const unsigned short PORT_MAX = 65535;

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    // ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
    // ����������� ���������� CUrlParsingError, ���������� ��������� �������� ������
    CHttpUrl(std::string const& url);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
    // ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
    // �� ������ ����������
    std::string GetURL() const;

    // ���������� �������� ���
    std::string GetDomain() const;

    /*
        ���������� ��� ���������. �������:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument() const;

    // ���������� ��� ���������
    Protocol GetProtocol() const;

    // ���������� ����� �����
    unsigned short GetPort() const;

    std::string GetProtocolString() const;

private:
    Protocol m_protocol;
    std::string m_domain;
    unsigned short m_port;
    std::string m_document;    

    bool IsValidProtocol(const std::string& protocolStr);
    bool IsValidDomain(const std::string& domainStr);
    bool ParsePort(const std::string& portStr);
    bool IsValidPort(const std::string& portStr);
};