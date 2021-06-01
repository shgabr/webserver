#include "HTTPGIFService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"

HTTPGIFService::HTTPGIFService(FileCache * p_fileCache,bool p_clean_cache )//constructor
        :HTTPService(p_fileCache,p_clean_cache) {}
bool HTTPGIFService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)
{//first the resoruce is fetched, then the header values of the response header are set 
    try {
        string resource = p_httpRequest->getResource();
        FileCacheItem * fileCacheItem = fileCache->getFile(resource);
        fileCacheItem = fileCacheItem->fetchContent();
        struct tm tm;
        string s = p_httpRequest->getHeaderValue("If-Modified-Since");
        HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
        httpResponseHeader->setHeader("Content-Type","image/gif");//specifies the type of resource
        httpResponseHeader->setHeader("Last-Modified",fileCacheItem->getLastUpdateTime());
        httpResponseHeader->setHeader("Connection","close");
        if(p_httpRequest->getHeaderValue("method")!="HEAD")//to stop sending the body if the HEAD method is used so the content length is set to zero
          httpResponseHeader->setHeader("Content-Length",to_string(fileCacheItem->getSize()));
        else
          httpResponseHeader->setHeader("Content-Length", "0");

        httpResponseHeader->respond();

        if(p_httpRequest->getHeaderValue("method")!="HEAD")
            p_tcpSocket->writeToSocket(fileCacheItem->getStream(),fileCacheItem->getSize());

        delete (httpResponseHeader);
        delete (fileCacheItem);
        return true;
    }
    catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)
    {
        httpNotFoundExceptionHandler.handle(p_tcpSocket);
        return false;
    }
}
HTTPService * HTTPGIFService::clone ()
{//returns and object of the same type
    return new HTTPGIFService(fileCache,false);
}
HTTPGIFService::~HTTPGIFService()
{//desctructor
}
