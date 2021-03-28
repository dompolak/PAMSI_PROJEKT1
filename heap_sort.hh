#ifndef _HEAP_SORT_HH
#define _HEAP_SORT_HH

#include "quick_sort.hh"

class HeapSort
{

protected:
    template<class T>
    void heapify(T *tab, long heap_size, long i)
    {
        long largest = i;
        long left_child = 2*i+1;
        long right_child = 2*i+2;

        if(heap_size > left_child && tab[left_child] > tab[largest])
            { largest = left_child; }

        if(heap_size > right_child && tab[right_child] > tab[largest])
            { largest = right_child; }
        
        if(largest != i)
        {
            std::swap(tab[largest], tab[i]);
            heapify(tab, heap_size, largest);
        }
    }

public:
    template<class T>
    void heap_sort(T *tab, long low_index, long high_index)
    {
        long size = high_index - low_index+1;
        
        //Build heap
        for(long i((size-1)/2); i >= 0; i--)
            { heapify(tab, size, i); }
        
        //One by one extract the items from heap
        for(long i(size-1); i>= 0; i--)
        {
            std::swap(tab[0], tab[i]);
            heapify(tab, i, 0);
        }
    }
};

#endif