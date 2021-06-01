#ifndef FILECACHE_H
#define FILECACHE_H
#include "FileCacheItem.h"
#include "BinaryHeap.cpp"

template<class ITEM, int initial_size>
class BinaryHeap;

class FileCache
{
    private:
        std::map <string,FileCacheItem *> cache;
        BinaryHeap <FileCacheItem*,11> * heap;
        string root;
        int cache_size;
        int current;
    public:
        FileCache(string p_root, int size=5);
        FileCacheItem * getFile(string p_file_name);
        ~FileCache ();
};

#endif
