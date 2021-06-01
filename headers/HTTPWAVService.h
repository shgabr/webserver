#include "HTTPService.h"
class HTTPWAVService: public HTTPService
{
    private:
    public:
        HTTPWAVService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPWAVService();
};
