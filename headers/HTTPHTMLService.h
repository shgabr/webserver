#ifndef HTTPHTMLSERVICE_H
#define HTTPHTMLSERVICE_H
#include "HTTPService.h"
class HTTPHTMLService: public HTTPService
{
    private:
    public:
        HTTPHTMLService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPHTMLService();
};

#endif 
