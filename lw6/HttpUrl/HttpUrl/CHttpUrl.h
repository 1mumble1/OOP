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
    // выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
    // выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
    // не должен включатьс€
    std::string GetURL() const;

    // возвращает доменное им€
    std::string GetDomain() const;

    /*
        ¬озвращает им€ документа. ѕримеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument() const;

    // возвращает тип протокола
    Protocol GetProtocol() const;

    // возвращает номер порта
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