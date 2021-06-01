#include "HTTPNotFoundExceptionHandler.h"
#include "HTTPResponseHeader.h"
// Constructor
HTTPNotFoundExceptionHandler::HTTPNotFoundExceptionHandler(){}//constructor

void HTTPNotFoundExceptionHandler::handle (TCPSocket * p_tcpSocket)//handle 404 exception
{
   //    you need to add your code here to handle 404 HTTP Errors
   string response = "<H1>404: Not Found</H1>";
   HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"Not Found",404,"HTTP/1.1");
   httpResponseHeader->setHeader("Content-Type","text/html");
   httpResponseHeader->setHeader("Content-Length",to_string(response.length()));
   httpResponseHeader->respond();
   p_tcpSocket->writeToSocket(response.c_str(),response.length());
   delete (httpResponseHeader);
}

HTTPNotFoundExceptionHandler::~HTTPNotFoundExceptionHandler(){}//destructor
