#include "FileCache.h"
FileCache::FileCache(string p_root, int size)//parametrized default constructor
{
  root = p_root;//initialize data members
  cache_size = size;
  current = 0;
  heap = new BinaryHeap <FileCacheItem*,11>;
}

FileCacheItem * FileCache::getFile(string p_file_name)//function takes the name of the file and returns it
{
  cout<<"File name: "<<p_file_name<<endl;
    string file_name = root+p_file_name;
    if ( cache[file_name] == NULL) {//if it doesn't exist in the cache
        FileCacheItem * fileCacheItem = new FileCacheItem(file_name);//create new item

        if (cache_size == current){//if the cache is full,remove the min element and insert this one
          cout<<"Cache Full\n";
          FileCacheItem * temp;
          heap->deleteMin(temp);
       //   cache.erase(root+heap.replace(fileCacheItem));
          heap->insert(fileCacheItem);
          cache.erase(temp->getFileName());
          cache[file_name] = fileCacheItem;
           cout<<"deleting minimum and creating a new file\n";
        } else {//if it's not full
          cache[file_name] = fileCacheItem;
          heap->insert (fileCacheItem);

          current ++;
        }
        return fileCacheItem;//return the item
    }
    cache[file_name]->incFrequency();
    heap->percolateDown(cache[file_name]->getIndex());
    heap->print();
    return cache[file_name];//return the item
}

FileCache::~FileCache () { // Destructor
    for_each (cache.begin(),cache.end(),[](const std::pair<string,FileCacheItem *>& it) -> bool {
            FileCacheItem * fileCacheItem = std::get<1>(it);
            delete(fileCacheItem);
            return true;
       });
}
