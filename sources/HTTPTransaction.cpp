#include "HTTPTransaction.h"
#include "HTTPGETRequest.h"
#include "HTTPNotAcceptableExceptionHandler.h"
#include "HTTPMethodNotAllowedExceptionHandler.h"

HTTPTransaction::HTTPTransaction (TCPSocket * p_tcpSocket,HTTPServiceManager * p_httpServiceManager,HTTPRequestManager * p_httpRequestManager)
{//non-parametrized constructor
    httpServiceManager = p_httpServiceManager;
    tcpSocket = p_tcpSocket;
    httpRequestManager = p_httpRequestManager;
};

HTTPRequest * HTTPTransaction::fetchHTTPRequest ()
{//reading from the socket then parsing to find the method, then getting the appropriate request, then parsing the rest of the buffer read
    char buffer[100];
    memset (buffer,0,100);
    int read  = 0 ;
    for ( int i = 0 ; i < 10 && read == 0; i ++)
        read = tcpSocket->readFromSocket(buffer,99);
    if ( read == 0) return NULL;
    stringstream iss(buffer);
    string method="";
    getline(iss,method,' ');
   HTTPRequest * httpRequest = httpRequestManager->getService(tcpSocket,method);
    if (httpRequest != NULL ) httpRequest->readAndParse(buffer);
    return httpRequest;
}
void HTTPTransaction::process()
{//processing the trancsaction
    HTTPRequest * httpRequest;
    try{
        httpRequest= fetchHTTPRequest ();//fetching the httprequest
        if ( httpRequest != NULL)
        {
            HTTPService * s  =httpServiceManager->getService(httpRequest->getResource());//getting the resource, then getting the appropriate service according to that service
            s->execute(httpRequest,tcpSocket);//executing the service
            delete (httpRequest);
        }
        tcpSocket->shutDown();
    }
    catch (HTTPNotAcceptableExceptionHandler httpNotAcceptableExceptionHandler )//exception handling
    {
        httpNotAcceptableExceptionHandler.handle(tcpSocket);
        delete (httpRequest);
        tcpSocket->shutDown();
    }
    catch (HTTPMethodNotAllowedExceptionHandler httpMethodNotAllowedExceptionHandler )
    {
        httpMethodNotAllowedExceptionHandler.handle(tcpSocket);
        tcpSocket->shutDown();
    }

}
void HTTPTransaction::threadMainBody ()
{//calling the process method
    process();
}
void HTTPTransaction::startHTTPTransaction(HTTPTransaction * me)
{//callign the threadMainBody method
	me->threadMainBody();
}
void HTTPTransaction::setThread(std::thread * p_th)
{//to set the thread of the object to the thread passed as a parameter
	th = p_th;
	th->detach();
}
bool HTTPTransaction::isRunning()
{//to check if the thread is still running
	return !th->joinable();
}

void HTTPTransaction::waitForRunToFinish()
{//waiting for the thread to join
	th->join();
}
HTTPTransaction::~HTTPTransaction()
{//destructor
    delete (tcpSocket);
}
