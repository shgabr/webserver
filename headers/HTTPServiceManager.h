#ifndef HTTPSERVICEMANAGER_H
#define HTTPSERVICEMANAGER_H
#include "HTTPHTMLService.h"
#include "HTTPPNGService.h"
#include "HTTPPDFService.h"
#include "HTTPJPGService.h"
#include "HTTPFormService.h"
#include "HTTPXMLService.h"
#include "HTTPGIFService.h"
#include "HTTPTXTService.h"
#include "HTTPTIFFService.h"
#include "HTTPMP4Service.h"
#include "HTTPMP3Service.h"
#include "HTTPWAVService.h"



class HTTPServiceManager
{
    private:
        std::map <string,HTTPService *> services;
    public:
        HTTPServiceManager();
        HTTPService * getService (string p_resource);
        ~HTTPServiceManager();
};


#endif
