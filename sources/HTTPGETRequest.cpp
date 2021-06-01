#include "HTTPGETRequest.h"
#include "TCPSocket.h"

HTTPGETRequest::HTTPGETRequest(TCPSocket * p_tcpSocket): HTTPRequest(p_tcpSocket)//construtor
{
}
void HTTPGETRequest::readAndParse(string initial_header)//read and parse the recieved header
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
HTTPRequest * HTTPGETRequest::clone (TCPSocket * p_tcpSocket)//clone an object of the same type and return it
{
    return new HTTPGETRequest(p_tcpSocket);
}
HTTPGETRequest::~HTTPGETRequest()//destructor
{
}
