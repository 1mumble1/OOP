#include "HtmlDecode.h"

const char AMP = '&';
const std::string HTML_ENTITIES[] = { "&amp;", "&quot;", "&apos;", "&lt;", "&gt;" };
const std::string ENTITIES[] = { "&", "\"", "\'", "<", ">" };

std::string ReplaceHtmlString(size_t& pos, const std::string& subject)
{
    std::string result;
    //for (int i = 0; i < HTML_ENTITIES->length(); i++)
    //{
    //    if (subject.substr(pos, HTML_ENTITIES[i].length()) == HTML_ENTITIES[i])
    //    {
    //        pos += HTML_ENTITIES[i].length();
    //        result = ENTITIES[i];
    //        return result;
    //    }
    //}

    if (subject.substr(pos, HTML_ENTITIES[0].length()) == HTML_ENTITIES[0])
    {
        pos += HTML_ENTITIES[0].length();
        result = ENTITIES[0];
        return result;
    }
    if (subject.substr(pos, HTML_ENTITIES[1].length()) == HTML_ENTITIES[1])
    {
        pos += HTML_ENTITIES[1].length();
        result = ENTITIES[1];
        return result;
    }
    if (subject.substr(pos, HTML_ENTITIES[2].length()) == HTML_ENTITIES[2])
    {
        pos += HTML_ENTITIES[2].length();
        result = ENTITIES[2];
        return result;
    }
    if (subject.substr(pos, HTML_ENTITIES[3].length()) == HTML_ENTITIES[3])
    {
        pos += HTML_ENTITIES[3].length();
        result = ENTITIES[3];
        return result;
    }
    if (subject.substr(pos, HTML_ENTITIES[4].length()) == HTML_ENTITIES[4])
    {
        pos += HTML_ENTITIES[4].length();
        result = ENTITIES[4];
        return result;
    }

    result = AMP;
    pos += 1;
    return result;
}

std::string HtmlDecode(std::string const& html)
{
	size_t pos = 0;
    std::string result;

    while (pos < html.length())
    {
        size_t foundPos = html.find(AMP, pos);
        if (foundPos == std::string::npos)
        {
            return result.append(html, pos, html.length());
        }

        result.append(html, pos, foundPos - pos);
		pos = foundPos;
        std::string replacementString = ReplaceHtmlString(pos, html);
        result.append(replacementString);
    }
    return result;
}