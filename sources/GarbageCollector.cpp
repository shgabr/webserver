#include "GarbageCollector.h"

GarbageCollector::GarbageCollector(){ }//constructor

void GarbageCollector::addHTTPTransaction(HTTPTransaction * p_httpTransaction) {
    http_transaction_store.push_back(p_httpTransaction);//method to push the transaction in the vector of transactions
}
void GarbageCollector::cleanup() {//this method deletes all HTTPtransactions after for them to finish running them pops them out of the vector
    for (int i = 0 ; i < http_transaction_store.size(); )
    {
        if ( !http_transaction_store[i]->isRunning()) 
        {
            http_transaction_store[i]->waitForRunToFinish();
            HTTPTransaction * httpTransaction = http_transaction_store[i]; 
            delete (httpTransaction); 
            http_transaction_store.erase(http_transaction_store.begin()+i);
        }
        else i++; 
    }
}
void GarbageCollector::terminate() {//method to delete all HTTPtransactions even without checking if they are running
    for ( ; http_transaction_store.size() > 0; )
    {
            http_transaction_store[0]->waitForRunToFinish();
            HTTPTransaction * httpTransaction = http_transaction_store[0]; 
            delete (httpTransaction);
            http_transaction_store.erase(http_transaction_store.begin()); 
    }
}
GarbageCollector::~GarbageCollector()
{
    terminate(); 
}

