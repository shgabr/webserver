#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include "includes.h"
#include "FileCache.h"


template <class ITEM,int initial_size>
class BinaryHeap
{
protected:
  ITEM * items;
  int maxSize,currentSize;
  void incCurrentSize ();
  bool isEmpty ();
  void buildHeap();
public:
  BinaryHeap ();
  BinaryHeap (ITEM * p_items, int p_size);
  void insert (const ITEM & p_item );
  string replace (ITEM p_item);
  bool deleteMin(ITEM & p_item);
  void percolateDown(int hole);
  void print ();
  virtual ~BinaryHeap();
};

#endif
