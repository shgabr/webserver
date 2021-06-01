#ifndef BINARYHEAP_CPP_
#define BINARYHEAP_CPP_

#include "BinaryHeap.h"

template <class ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::incCurrentSize () {//this method is to increase the size of the heap

  if ( currentSize == (maxSize - 1)) {
      maxSize *= 2;
      items = (ITEM *) realloc(items, maxSize*sizeof(ITEM));//reallocating the array in which the array is stored
    }

    currentSize ++;
}

template <class ITEM,int initial_size>
bool BinaryHeap<ITEM,initial_size>::isEmpty () {//checking if the heap is empty

  if ( currentSize > 0) return false;
  else return true;
}

template <class ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::percolateDown(int hole) {//this method is for pushing a node down the heap until
                                                              //the root of each subtree is the minimum node in the heap

  int child;
  ITEM tmp = std::move(items[hole]);
  for (;hole *2 <= currentSize ;hole=child) {
    child = hole * 2;     // a node's children is at the index*2 or index*2 +1 thus we are looking for the minumum child of the two children
    if ( child != currentSize && items[child+1] < items[child])
      child++;
    if (items[child] < tmp){//checking if the child is less than the node at the hole, i.e. the node to be inserted
      int temp = items[child]->getIndex();
      items[child]->setIndex(hole);
      items[hole] = std::move(items[child]);
  //    items[hole]->setIndex(hole);
    }
    else break;
  }
  items[hole] = std::move(tmp);
  items[hole]->setIndex(hole);

}

template <class ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::buildHeap ()
{//this is for initializing the heap
  for ( int i = currentSize/2;i > 0 ; i--)
    percolateDown(i);
}

template <class ITEM,int initial_size>
BinaryHeap<ITEM,initial_size>::BinaryHeap ()
{//the non-parametrized constructor of the heap where the array in which the data is stored is initialized 
  maxSize = initial_size+1;
  currentSize = 0;
  items = (ITEM *) calloc(maxSize,sizeof(ITEM));
}

template <class ITEM,int initial_size>
BinaryHeap<ITEM,initial_size>::BinaryHeap(ITEM * p_items,int p_size)
{//the parametrized constructor of the heap where an array of items is passed as a parameter
  maxSize = initial_size+1;
  if ( maxSize < p_size+1)
    maxSize = p_size+1;

  currentSize = 0;
  items = (ITEM *) calloc(maxSize,sizeof(ITEM));
  for ( int i = 0 ; i < p_size ; i ++)
    items[++currentSize] = p_items[i];
  buildHeap();

}

template <class ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::insert(const ITEM & p_item)
{//insert a new item at the root of the heap
  //incCurrentSize();
  int hole = currentSize;
  items[0] = std::move(p_item);
  for (; p_item < items[hole/2]; hole /=2){
    items[hole/2]->setIndex(hole);
    items[hole] = std::move(items[hole/2]);
  }
  items[hole] = std::move(items[0]);
  items[hole]->setIndex(hole);
}

template <class ITEM,int initial_size>
string BinaryHeap<ITEM,initial_size>::replace(ITEM p_item)
{//replacing the item at the root of the heap by another item passed as a parameter
  string file_name = items[1]->getFileName();
  ITEM temp = std::move(items[1]);
  items[1] = std::move(p_item);
  return file_name;
}


template <class ITEM,int initial_size>
bool BinaryHeap<ITEM,initial_size>::deleteMin(ITEM & p_item) {
//remove the minimum item in the heap which is the root of the heap then percolating down the hole generated in the place of the hole
  if ( isEmpty()) return false;

  p_item = std::move(items[1]);

  items[1] = std::move(items[currentSize -- ]);
  percolateDown(1);
  return true;
}

template <class ITEM,int initial_size>
void BinaryHeap<ITEM,initial_size>::print() {
//print all the file names of the items in the heap
  int j = 0 ;
  int l = 1;
  for ( int i = 0 ; i < currentSize ; i ++) {
    cout << items[i+1]->getFileName() << "\t" ;
    if (i == j ) {
      cout << endl;
      j += l * 2;
      l *= 2;
    }
  }
}

template <class ITEM,int initial_size>
BinaryHeap<ITEM,initial_size>::~BinaryHeap ()
{//destructor of the heap
  free (items);
}

#endif
