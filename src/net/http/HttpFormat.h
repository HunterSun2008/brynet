#ifndef _HTTPREQUEST_H
#define _HTTPFORMAT_H

#include <string>
using namespace std;

class HttpFormat
{
public:
    enum HTTPREQUEST_PROTOCOL
    {
        HRP_NONE,
        HRP_GET,
        HRP_POST,
        HRP_RESPONSE,
        HRP_MAX
    };

    void        setProtocol(HTTPREQUEST_PROTOCOL protocol)
    {
        m_eProtocol = protocol;
        assert(m_eProtocol > HRP_NONE && m_eProtocol < HRP_MAX);
    }

    void        setHost(const char* host)
    {
        m_host = host;
    }

    void        setCookie(const char* v)
    {
        m_cookie = v;
    }

    void        setRequestUrl(const char* url)
    {
        m_url = url;
    }

    void        addParameter(const char* v)
    {
        m_parameter += v;
    }

    void        addParameter(const char* k, const char* v)
    {
        if(m_parameter.size() > 0)
        {
            m_parameter += "&";
        }

        m_parameter += k;
        m_parameter += "=";
        m_parameter += v;
    }

    string      getResult()
    {
        string ret;
        if(m_eProtocol == HRP_GET)
        {
            ret += "GET";
        }
        else if (m_eProtocol == HRP_POST)
        {
            ret += "POST";
        }

        ret += " ";
        ret += m_url;
        if (m_eProtocol == HRP_GET && !m_parameter.empty())
        {
            ret += "?";
            ret += m_parameter;
        }

        ret += " HTTP/1.1";
        ret += "\r\n";

        if (!m_host.empty())
        {
            ret += "Host: ";
            ret += m_host;
            ret += "\r\n";
        }

        if(!m_cookie.empty())
        {
            ret += "Cookie: ";
            ret += m_cookie;
            ret += "\r\n";
        }

        if (m_eProtocol != HRP_GET && !m_parameter.empty())
        {
            ret += "Content-Length: ";
            char temp[1024];
            sprintf(temp, "%d", m_parameter.size());
            ret += temp;
            ret += "\r\n";

            //ret += "Content-Type: application/x-www-form-urlencoded\r\n";
        }

        ret += "\r\n";

        if (m_eProtocol != HRP_GET && !m_parameter.empty())
        {
            ret += m_parameter;
            ret += "\r\n";
        }

        return ret;
    }
private:

    string                  m_host;
    string                  m_url;
    HTTPREQUEST_PROTOCOL    m_eProtocol;
    string                  m_parameter;
    string                  m_cookie;
};

#endif