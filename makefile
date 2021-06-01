S = ./sources
O = ./oblects
B = ./bin
I = ./headers
O_F = -o
INC = -I $(I)
INC += -I $(S)
STD = -std=c++11
TH = $(STD) -pthread
GCC = /usr/bin/g++

$(B)/webServer: $(S)/FileCache.cpp $(S)/FileCacheItem.cpp $(S)/GarbageCollector.cpp $(S)/HTTPExceptionHandler.cpp $(S)/HTTPFormService.cpp $(S)/HTTPGETRequest.cpp $(S)/HTTPHTMLService.cpp $(S)/HTTPMethodNotAllowedExceptionHandler.cpp $(S)/HTTPNotAcceptableExceptionHandler.cpp $(S)/HTTPNotFoundExceptionHandler.cpp $(S)/HTTPPOSTRequest.cpp $(S)/HTTPRequest.cpp $(S)/HTTPRequestManager.cpp $(S)/HTTPResponseHeader.cpp $(S)/HTTPService.cpp $(S)/HTTPServiceManager.cpp $(S)/HTTPTransaction.cpp $(S)/TCPServerSocket.cpp $(S)/TCPSocket.cpp $(S)/WebCache.cpp $(S)/HTTPJPGService.cpp $(S)/HTTPPNGService.cpp $(S)/HTTPPDFService.cpp $(S)/HTTPXMLService.cpp $(S)/HTTPHEADRequest.cpp $(S)/HTTPGIFService.cpp $(S)/HTTPTXTService.cpp $(S)/HTTPMP4Service.cpp $(S)/HTTPMP3Service.cpp $(S)/HTTPTIFFService.cpp $(S)/HTTPWAVService.cpp $(S)/BinaryHeap.cpp
	$(GCC) -g $(INC) $(S)/FileCache.cpp $(S)/FileCacheItem.cpp $(S)/GarbageCollector.cpp $(S)/HTTPExceptionHandler.cpp $(S)/HTTPFormService.cpp $(S)/HTTPGETRequest.cpp $(S)/HTTPHTMLService.cpp $(S)/HTTPMethodNotAllowedExceptionHandler.cpp $(S)/HTTPNotAcceptableExceptionHandler.cpp $(S)/HTTPNotFoundExceptionHandler.cpp $(S)/HTTPPOSTRequest.cpp $(S)/HTTPRequest.cpp $(S)/HTTPRequestManager.cpp $(S)/HTTPResponseHeader.cpp $(S)/HTTPService.cpp $(S)/HTTPServiceManager.cpp $(S)/HTTPTransaction.cpp $(S)/TCPServerSocket.cpp $(S)/TCPSocket.cpp $(S)/WebCache.cpp $(S)/HTTPJPGService.cpp $(S)/HTTPPNGService.cpp $(S)/HTTPPDFService.cpp $(S)/HTTPXMLService.cpp $(S)/HTTPHEADRequest.cpp $(S)/HTTPGIFService.cpp $(S)/HTTPTXTService.cpp $(S)/HTTPMP4Service.cpp $(S)/HTTPMP3Service.cpp $(S)/HTTPTIFFService.cpp $(S)/HTTPWAVService.cpp $(S)/BinaryHeap.cpp -o $(B)/webServer $(TH)
