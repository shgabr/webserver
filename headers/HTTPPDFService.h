#include "HTTPService.h"
class HTTPPDFService: public HTTPService
{
    private:
    public:
        HTTPPDFService(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPPDFService();
};
