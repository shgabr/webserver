#include "HTTPRequestManager.h"
#include "HTTPMethodNotAllowedExceptionHandler.h"
HTTPRequestManager::HTTPRequestManager()//constructor
{
    methods ["GET"] = new HTTPGETRequest(NULL);//create stakeholders for each request type to be cloned later
    methods ["POST"] = new HTTPPOSTRequest (NULL);
    methods ["HEAD"] = new HTTPHEADRequest (NULL);
}
HTTPRequest * HTTPRequestManager::getService (TCPSocket * p_tcpSocket,string p_method)//clones one of the supported request methods
{
    if ( methods[p_method]==NULL) throw (HTTPMethodNotAllowedExceptionHandler());
    return methods[p_method]->clone(p_tcpSocket); // else clone and return the object
}
// Destructor
HTTPRequestManager::~HTTPRequestManager()//destructor
{
    for_each (methods.begin(),methods.end(),[](const std::pair<string,HTTPRequest *>& it) -> bool {
        HTTPRequest * httpRequest = std::get<1>(it);
        delete(httpRequest);
        return true;
   });

}
