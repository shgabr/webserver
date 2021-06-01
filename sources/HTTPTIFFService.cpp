#include "HTTPTIFFService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"

HTTPTIFFService::HTTPTIFFService(FileCache * p_fileCache,bool p_clean_cache )
        :HTTPService(p_fileCache,p_clean_cache) {}//constructor
bool HTTPTIFFService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)
{//sets the headers of the response header to their appropriate values
    try {
        string resource = p_httpRequest->getResource();
        FileCacheItem * fileCacheItem = fileCache->getFile(resource);
        fileCacheItem = fileCacheItem->fetchContent();
        struct tm tm;
        string s = p_httpRequest->getHeaderValue("If-Modified-Since");
        HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
        httpResponseHeader->setHeader("Content-Type","image/tiff");//specifies the type of the resource
        httpResponseHeader->setHeader("Last-Modified",fileCacheItem->getLastUpdateTime());
        httpResponseHeader->setHeader("Connection","close");
        if(p_httpRequest->getHeaderValue("method")!="HEAD")//if the method used is head , no body will be sent, thus the length of the body is zero
          httpResponseHeader->setHeader("Content-Length",to_string(fileCacheItem->getSize()));
        else
          httpResponseHeader->setHeader("Content-Length", "0");

        httpResponseHeader->respond();

        if(p_httpRequest->getHeaderValue("method")!="HEAD")//does not write the body to the socket if the method used is head
            p_tcpSocket->writeToSocket(fileCacheItem->getStream(),fileCacheItem->getSize());
            
        delete (httpResponseHeader);
        delete (fileCacheItem);
        return true;
    }
    catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)//exception handling
    {
        httpNotFoundExceptionHandler.handle(p_tcpSocket);
        return false;
    }
}
HTTPService * HTTPTIFFService::clone ()
{//returns an object of the same type
    return new HTTPTIFFService(fileCache,false);
}
HTTPTIFFService::~HTTPTIFFService()//destructor
{
}
