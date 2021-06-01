#include "FileCacheItem.h"
#include "HTTPNotFoundExceptionHandler.h"
#include <sys/stat.h>

// Load file content of the target file
void FileCacheItem::load ()
{
    FILE * f = fopen (file_name.c_str(),"r");//open the file
    if ( f ==NULL) throw(HTTPNotFoundExceptionHandler());//if file is not opened, throw an exception
    fseek(f,0,2);//seek until the end of the file
    cache_item_size = ftell(f);//get the size of the file
    fseek(f,0,0);//seek back to the start of the file
    if ( cache_item_stream != NULL) free (cache_item_stream);//if it's busy, free it
    cache_item_stream = (char *) calloc(cache_item_size,sizeof(char));//allocate size for this buffer
    fread (cache_item_stream,1,cache_item_size,f);//read the whole file into the buffer
    stat(file_name.c_str(), &cache_item_stat);
    fclose(f);//close the fstream
}
FileCacheItem::FileCacheItem()//Default Constructor
{
    file_name = "";//initialize data members
    cache_item_stream = NULL;
    frequency=1;
    index =1;
}
// Parameterized Constructor
FileCacheItem::FileCacheItem(string p_file_name)
{
    file_name = p_file_name;//initialize data members
    cache_item_stream = NULL;
    frequency=1;
    index =1;
    load();
}

void FileCacheItem::incFrequency ()
{
    frequency++;//increment frequency
}

int FileCacheItem::getFrequency (){

    return frequency;//getter for frequency
}
int FileCacheItem::getIndex (){

    return index;//getter for index
}
void FileCacheItem::setIndex (int p_index){//setter for index

    index = p_index;
}
string FileCacheItem::getFileName (){//getter for file_name

    return file_name;
}

bool FileCacheItem::operator > (FileCacheItem * p_FileCacheItem)//operator overloading to compare two FileCacheItems
{
    return ( getFrequency() > p_FileCacheItem->getFrequency());
}
bool FileCacheItem::operator < (FileCacheItem * p_FileCacheItem)//operator overloading to compare two FileCacheItems
{
    return ( getFrequency() < p_FileCacheItem->getFrequency());
}

bool FileCacheItem::operator == (FileCacheItem * p_FileCacheItem)//operator overloading to compare two FileCacheItems
{
    return ( getFrequency() == p_FileCacheItem->getFrequency());

}

FileCacheItem * FileCacheItem::fetchContent()//function to get an item's content
{
    fetch_mutex.lock();//lock the mutex
    try{
        struct stat attrib;
        if (stat(file_name.c_str(), &attrib) == -1)//if failed
        {
            fetch_mutex.unlock();//unlock the mutex
            throw(HTTPNotFoundExceptionHandler());//throw an exception
        }
        if ( attrib.st_mtime != cache_item_stat.st_mtime ) load();//check if modified since the last time it was loaded
        FileCacheItem * fileCacheItem = new FileCacheItem();//create a cache item
        *fileCacheItem = *this;//make it point to the current object
        fetch_mutex.unlock();//unlock mutex
        return fileCacheItem;//return the fetched item
    }catch (HTTPNotFoundExceptionHandler httpNotFoundExceptionHandler)//catch an exception
    {
            fetch_mutex.unlock();//unlock mutex
            throw(httpNotFoundExceptionHandler);//throw exception to the calling function
            return NULL;//return
    }
}

char * FileCacheItem::getLastUpdateTime ()//function to get the last update time
{
    memset (time_string,0,100);
    struct tm tm = *gmtime(((time_t *) &cache_item_stat.st_mtime));
    strftime(time_string, 100, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return time_string;
}
char * FileCacheItem::getStream()//getter for cache_item_stream
{
    return cache_item_stream;
}
long FileCacheItem::getSize()//getter for cache_item_size
{
    return cache_item_size;
}

void FileCacheItem::operator=(const FileCacheItem & p_fileCacheItem)//operator overloading for assigning one object to another
{
    assign_mutex.lock();//lock mutex
    if ( cache_item_stream != NULL) free (cache_item_stream);
    cache_item_stream = (char *) calloc(p_fileCacheItem.cache_item_size,sizeof(char));
    cache_item_size=p_fileCacheItem.cache_item_size;
    cache_item_stat = p_fileCacheItem.cache_item_stat;
    memcpy (cache_item_stream,p_fileCacheItem.cache_item_stream,cache_item_size);
    assign_mutex.unlock();//unlock mutex
}

FileCacheItem::~FileCacheItem()//destructor
{
    if ( cache_item_stream != NULL ) free (cache_item_stream);
}
