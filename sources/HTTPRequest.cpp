#include "HTTPRequest.h"
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void HTTPRequest::addToHeaderMap(string header_item)//adds the key and value as a pair into the headers map
{
    stringstream iss(header_item);//stringstream to divide the key and value
    string key="";
    string value = "";
    getline(iss,key,':');
    getline(iss,value,'\r');
    trim(value);
    header[key] = value;
}

HTTPRequest::HTTPRequest(TCPSocket * p_tcpSocket)//constructor
{
    tcpSocket = p_tcpSocket;//initialize the data member
}


void HTTPRequest::readAndParse(string initial_header)//read the header until "\r\n\r\n" and then parse it
{
    char buffer[1024];
    memset (buffer,1024,0);
    string http_stream=initial_header;
    for ( ;http_stream.find("\r\n\r\n") ==std::string::npos; )
    {
        tcpSocket->readFromSocket(buffer,1023);
        http_stream +=buffer;
        memset (buffer,0,1024);
    }
    stringstream iss(http_stream);
    getline(iss,method,' ');
    getline(iss,resource,' ');
    getline(iss,protocol,'\n');
    protocol.pop_back();

    string line = " ";
    for (;!line.empty();)
    {
        getline(iss,line,'\n');
        line.pop_back();
        if ( !line.empty()) addToHeaderMap(line);
    }
    getline(iss,line,'\n');
    body = line;

}
string HTTPRequest::getResource ()//getter for resource
{
    return resource;
}

string HTTPRequest::getHeaderValue(string header_item_name)//getter for the value of a certain header key
{
    return header[header_item_name];
}

string & HTTPRequest::getBody()//getter for body
{
    return body;
}
HTTPRequest::~HTTPRequest(){}//destructor
