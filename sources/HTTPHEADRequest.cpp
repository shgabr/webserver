#include "HTTPHEADRequest.h"
#include "TCPSocket.h"

HTTPHEADRequest::HTTPHEADRequest(TCPSocket * p_tcpSocket): HTTPRequest(p_tcpSocket)
{//constructor
}
HTTPRequest * HTTPHEADRequest::clone (TCPSocket * p_tcpSocket)
{//returns an object of the same type
    return new HTTPHEADRequest(p_tcpSocket);
}
HTTPHEADRequest::~HTTPHEADRequest()
{//destructor
}
