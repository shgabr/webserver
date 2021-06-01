#include "HTTPPOSTRequest.h"

HTTPPOSTRequest::HTTPPOSTRequest(TCPSocket * p_tcpSocket): HTTPRequest(p_tcpSocket) {}//constructor

void HTTPPOSTRequest::readAndParse(string initial_header)//read and parse the recieved header in the HTTP request
{
    HTTPRequest::readAndParse(initial_header);
    long stdin_size = atol(header["content-length"].c_str());

    for ( ;body.length() < stdin_size; )
    {
        char buffer[1024];
        memset ( buffer,0,1024);
        tcpSocket->readFromSocket(buffer,1023);
        body +=buffer;
    }
}
HTTPRequest * HTTPPOSTRequest::clone (TCPSocket * p_tcpSocket)//create an item of the same type and return it
{
    return new HTTPPOSTRequest(p_tcpSocket);
}
HTTPPOSTRequest::~HTTPPOSTRequest()//destructor
{
}
