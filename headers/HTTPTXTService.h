#include "HTTPService.h"
class HTTPTXTService: public HTTPService
{
    private:
    public:
        HTTPTXTService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPTXTService();
};
