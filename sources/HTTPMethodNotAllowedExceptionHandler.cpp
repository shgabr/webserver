#include "HTTPMethodNotAllowedExceptionHandler.h"
#include "HTTPResponseHeader.h"
// Constructor
HTTPMethodNotAllowedExceptionHandler::HTTPMethodNotAllowedExceptionHandler(){}//constructor

void HTTPMethodNotAllowedExceptionHandler::handle (TCPSocket * p_tcpSocket)//handling 405 exception
{
    string response = "<H1>405: Method Not Allowed</H1>";
    HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"Method Not Allowed",405,"HTTP/1.1");
    httpResponseHeader->setHeader("Content-Type","text/html");
    httpResponseHeader->setHeader("Content-Length",to_string(response.length()));
    httpResponseHeader->respond();
    p_tcpSocket->writeToSocket(response.c_str(),response.length());
    delete (httpResponseHeader);

}

HTTPMethodNotAllowedExceptionHandler::~HTTPMethodNotAllowedExceptionHandler(){}//destructor
