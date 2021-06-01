#include "HTTPService.h"
class HTTPTIFFService: public HTTPService
{
    private:
    public:
        HTTPTIFFService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPTIFFService();
};
