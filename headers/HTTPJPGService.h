#include "HTTPService.h"
class HTTPJPGService: public HTTPService
{
    private:
    public:
        HTTPJPGService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPJPGService();
};
