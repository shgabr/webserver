#include "HTTPHTMLService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"

HTTPHTMLService::HTTPHTMLService(FileCache * p_fileCache,bool p_clean_cache )//constructor
        :HTTPService(p_fileCache,p_clean_cache) {}
bool HTTPHTMLService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)//compose the header and body and send them
{
    try {
        string resource = p_httpRequest->getResource();
        FileCacheItem * fileCacheItem = fileCache->getFile(resource);
        fileCacheItem = fileCacheItem->fetchContent();
        struct tm tm;
        string s = p_httpRequest->getHeaderValue("If-Modified-Since");
        HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
        httpResponseHeader->setHeader("Content-Type","text/html");
        httpResponseHeader->setHeader("Last-Modified",fileCacheItem->getLastUpdateTime());
        httpResponseHeader->setHeader("Connection","close");
        if(p_httpRequest->getHeaderValue("method")!="HEAD")
          httpResponseHeader->setHeader("Content-Length",to_string(fileCacheItem->getSize()));
        else
          httpResponseHeader->setHeader("Content-Length", "0");

        httpResponseHeader->respond();//write header to socket

        if(p_httpRequest->getHeaderValue("method")!="HEAD")
            p_tcpSocket->writeToSocket(fileCacheItem->getStream(),fileCacheItem->getSize());//write body to socket

        delete (httpResponseHeader);
        delete (fileCacheItem);
        return true;
    }
    catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)//catch exception
    {
        httpNotFoundExceptionHandler.handle(p_tcpSocket);
        return false;
    }
}
HTTPService * HTTPHTMLService::clone ()//clones a copy of the same type and returns it
{
    return new HTTPHTMLService(fileCache,false);
}
HTTPHTMLService::~HTTPHTMLService()//destructor
{
}
