#include "HTTPService.h"
class HTTPMP3Service: public HTTPService
{
    private:
    public:
        HTTPMP3Service(FileCache * p_fileCache,bool p_clean_cache = true);
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone ();
        ~HTTPMP3Service();
};
