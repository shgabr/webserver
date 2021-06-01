#include "HTTPXMLService.h"
#include "HTTPResponseHeader.h"
#include "HTTPNotFoundExceptionHandler.h"

string HTTPXMLService::urldecode(string & urlencoded)
{//this method is decode a string from hexadecimal to normal text, however, the formatting<br/> is still provided
    string urldecoded="";
    for ( int i = 0 ;i < urlencoded.length();)
    {
        char c = urlencoded[i];
        if (i < urlencoded.length() - 2 && c == '%') {
            char c1 = urlencoded[i + 1];
            char c2 = urlencoded[i + 2];
            c1 = tolower(c1);
            c2 = tolower(c2);
            if (isxdigit(c1) && isxdigit(c2)) {
                if (c1 <= '9') c1 = c1 - '0';
                else c1 = c1 - 'a' + 10;
                if (c2 <= '9') c2 = c2 - '0';
                else c2 = c2 - 'a' + 10;
                c = (char) ((16 * c1) + c2);
                if ( c == '\n') urldecoded += "<br/>";
                urldecoded+=c;
                i += 3;
            } else {
                urldecoded+= c;
                i++;
            }
        } else {
            if (c == '+') c = ' ';
            urldecoded+= c;
            i++;
        }
    }
    return urldecoded;
}
void HTTPXMLService::add_to_form_data(string & form_field)
{

    // this parses the input string, adds a key and a value to both the raw_form_data and the form_data maps
    string key, value;
    stringstream ss (form_field);
    getline(ss,key,'=');
    getline(ss,value,'&');
    raw_form_data [key] = value;
    form_data [urldecode(key)] = urldecode(value);

}

void HTTPXMLService::parse_data (HTTPRequest * p_httpRequest)
{//this get the body, parses the body and adds each string to the map through the add_to_form_data
    string data  = p_httpRequest->getBody();
    stringstream iss(data);
    string field = "";
    for (;!iss.eof();)
    {
        getline(iss,field,'&');
        field += "&";
        add_to_form_data(field);
    }
}

string HTTPXMLService::compose_reply()
{//this composes the HTML reply 
    string reply = "<?xml version=\"1.0\"?>";
    reply += "<table width='100%' border='1'>";

    for_each (raw_form_data.begin(),raw_form_data.end(),[&reply](const std::pair<string,string>& it) -> bool {
            reply += "<tr><td>";
            reply += std::get<0>(it);
            reply += "</td><td>";
            reply += std::get<1>(it);
            reply += "</td></tr>";
            return true;
    });

    for_each (form_data.begin(),form_data.end(),[&reply](const std::pair<string,string>& it) -> bool {
            reply += "<tr><td>";
            reply += std::get<0>(it);
            reply += "</td><td>";
            reply += std::get<1>(it);
            reply += "</td></tr>";
            return true;
    });
    reply += "</table>";
  //  reply += "</body></html>";
    return reply;

}
HTTPXMLService::HTTPXMLService( )//constructor
        :HTTPService(NULL,false) {}

bool HTTPXMLService::execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket)
{//setting the headers of the response header to be sent
  parse_data(p_httpRequest);
  string reply = compose_reply();

    try {
        string resource = p_httpRequest->getResource();
        struct tm tm;
        string s = p_httpRequest->getHeaderValue("If-Modified-Since");
        HTTPResponseHeader * httpResponseHeader = new HTTPResponseHeader(p_tcpSocket,"OK",200,"HTTP/1.1");
        httpResponseHeader->setHeader("Content-Type","application/xml");//type of resource
    //    httpResponseHeader->setHeader("Last-Modified",fileCacheItem->getLastUpdateTime());
        httpResponseHeader->setHeader("Connection","close");
        httpResponseHeader->setHeader("Content-Length",to_string(reply.length()));
        httpResponseHeader->respond();
        p_tcpSocket->writeToSocket(reply.c_str(),reply.length());
        delete (httpResponseHeader);
        return true;
    }
    catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)//exception handling
    {
        httpNotFoundExceptionHandler.handle(p_tcpSocket);
        return false;
    }
}
HTTPService * HTTPXMLService::clone ()
{//returns an object of the same type
    return new HTTPXMLService();
}
HTTPXMLService::~HTTPXMLService()
{//destructor
}
