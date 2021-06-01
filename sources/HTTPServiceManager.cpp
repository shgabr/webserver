#include "HTTPServiceManager.h"
#include "HTTPNotAcceptableExceptionHandler.h"
#define WEB_CACHE_ROOT  "./www"
HTTPServiceManager::HTTPServiceManager()//constructor
{   FileCache * cache;
    cache = new FileCache (WEB_CACHE_ROOT);

    services ["html"] = new HTTPHTMLService(cache,true);//create a ample of each extension to be cloned later
    services ["pdf"] = new HTTPPDFService(cache,true);
    services ["jpg"] = new HTTPJPGService(cache,true);
    services ["jpeg"] = new HTTPJPGService(cache,true);
    services ["png"] = new HTTPPNGService(cache,true);
    services ["xml"] = new HTTPXMLService ();
    services ["form"] = new HTTPFORMService ();
    services ["gif"] = new HTTPGIFService(cache,true);
    services ["txt"] = new HTTPTXTService(cache,true);
    services ["tiff"] = new HTTPTIFFService(cache,true);
    services ["mp4"] = new HTTPMP4Service(cache,true);
    services ["mp3"] = new HTTPMP3Service(cache,true);
    services ["wav"] = new HTTPWAVService(cache,true);




}
HTTPService * HTTPServiceManager::getService (string p_resource)//returns a clone of a request of the requested type
{
    string ext = p_resource.substr(p_resource.find_last_of(".") + 1);
    if ( services[ext]==NULL)
    {
        string base_name = p_resource.substr(p_resource.find_last_of("/") + 1);
        if ( services[base_name]==NULL) throw (HTTPNotAcceptableExceptionHandler());
        else return services[base_name]->clone();
    }
    else return services[ext]->clone();
}

HTTPServiceManager::~HTTPServiceManager()//destructor
{
    for_each (services.begin(),services.end(),[](const std::pair<string,HTTPService *>& it) -> bool {
        HTTPService * httpService = std::get<1>(it);
        delete(httpService);
        return true;
   });
}
