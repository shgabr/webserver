/*
 * File:   main.cpp
 * Author: kmsobh
 *
 * Created on October 21, 2016, 12:20 PM
 */

#include "TCPServerSocket.h"
#include "HTTPTransaction.h"
#include "GarbageCollector.h"
#include "HTTPRequestManager.h"

using namespace std;

int main(int argc, char** argv) {

    
    GarbageCollector * garbageCollector = new GarbageCollector();
    HTTPServiceManager * httpServiceManager = new HTTPServiceManager();
    HTTPRequestManager * httpRequestManager = new HTTPRequestManager();
    TCPServerSocket * tcpServerSocket = new TCPServerSocket("127.0.0.1",9999,100);

    tcpServerSocket->initializeSocket();
    for ( ;; ) // Loop forever
    {
      // Wait for connection and return a TCPSocket object upon one
      TCPSocket * tcpSocket = tcpServerSocket->getConnection(0,0,-1,-1);
      if (tcpSocket == NULL) break;  // if tcpSocket is NULL then error occured and we break the loop
      garbageCollector->cleanup(); // Invoke the garbage collector cleaner in case of expired connections
      HTTPTransaction * transaction = new HTTPTransaction (tcpSocket,httpServiceManager,httpRequestManager); // Instantiate a new Connection object and pass the returned TCP socket to it
      std::thread * t = new std::thread (HTTPTransaction::startHTTPTransaction,transaction); // Start the connection thread to communicate with the client
      transaction->setThread(t);
      garbageCollector->addHTTPTransaction(transaction); // Add the connection to the garbage collector to be cleaned up when expired
    }

   delete(garbageCollector); // Delete the garbage collector
	 delete (tcpServerSocket); // Terminate and delete the TCP server socket
   delete (httpServiceManager); // Delete the HTTPServiceManager
   delete (httpRequestManager); // Delete the HTTPRequestManager

    return 0;
}
