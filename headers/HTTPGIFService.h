#include "HTTPService.h"
class HTTPGIFService: public HTTPService
{
    private:
    public:
        HTTPGIFService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPGIFService();
};
