#include "HTTPService.h"
class HTTPPNGService: public HTTPService
{
    private:
    public:
        HTTPPNGService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPPNGService();
};
