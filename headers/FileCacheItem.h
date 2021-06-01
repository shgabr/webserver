#ifndef FILECACHEITEM_H
#define FILECACHEITEM_H

#include "includes.h"
class FileCacheItem
{
    private:
        string file_name;
        char * cache_item_stream;
        long cache_item_size;
        struct stat cache_item_stat;
        char time_string[100];
        int frequency;
        int index;
        void load ();
        mutex fetch_mutex;
        mutex assign_mutex;
    public:
        FileCacheItem();
        FileCacheItem(string p_file_name);
        FileCacheItem * fetchContent();
        char * getLastUpdateTime ();
        char * getStream();
        long getSize();

        void incFrequency ();  
        int getFrequency ();
        void setIndex (int val);
        int getIndex ();
        string getFileName ();
        bool operator > (FileCacheItem * p_fileCacheItem);
        bool operator < (FileCacheItem * p_fileCacheItem);
        bool operator == (FileCacheItem * p_fileCacheItem);

        void operator=(const FileCacheItem & p_fileCacheItem);
        ~FileCacheItem();
};

#endif
