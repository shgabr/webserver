#ifndef HTTPGETREQUEST_H
#define HTTPGETREQUEST_H
#include "HTTPRequest.h"

class HTTPGETRequest : public HTTPRequest
{
    private:
    public:
        HTTPGETRequest(TCPSocket * p_tcpSocket);
        void readAndParse(string initial_header);
        virtual HTTPRequest * clone (TCPSocket * p_tcpSocket);
        ~HTTPGETRequest();
};

#endif
