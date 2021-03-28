#ifndef _INTRO_ROSPECTIVE_SORT_HH
#define _INTRO_ROSPECTIVE_SORT_HH

#include "merge_sort.hh"
#include "heap_sort.hh"

class IntrospectiveSort : public HeapSort, public QuickSort
{

protected:
    template<class T>
    T median_of_three(T *tab, long low_index, long high_index)
    {
        long middle_index = (low_index+high_index)/2;

        if(tab[high_index]< tab[low_index])
            { std::swap(tab[low_index], tab[high_index]); }
        if(tab[middle_index] < tab[low_index])
            { std::swap(tab[middle_index], tab[low_index]); }
        if(tab[high_index] < tab[middle_index])
            { std::swap(tab[high_index], tab[middle_index]); }

        return tab[middle_index];
    }
    
    template<class T>
    void insertion_sort(T *tab, long low_index, long high_index)
    {   
        long size = high_index - low_index+1;
        long j;
        T tmp;
        
        for(long i(1); i<size; i++)
        {
            tmp = tab[i];
            j = i-1;

            while(j>=0 && tab[j]>tmp)
            {
                tab[j+1] = tab[j];
                --j;
            }
            tab[j+1] = tmp;
        }
    }

    template<class T>
    void intro_sort(T *tab, long low_index, long high_index, long depth_limit)
    {   
        if(depth_limit == 0)
        {   
            heap_sort(tab, low_index, high_index);
            return;
        }

        long i = low_index-1;
        long j = high_index+1;
        T pivot = median_of_three(tab, low_index, high_index);
        
        partition(tab, i, j, pivot);
        if(j>low_index)
            { intro_sort(tab, low_index, j, --depth_limit); }
        if(i<high_index)
            { intro_sort(tab, i, high_index, --depth_limit); }
    }

public:
    template<class T>
    void introspective_sort(T *tab, long low_index, long high_index)
    {   
        long depth_limit = 2*log(high_index - low_index);
        intro_sort(tab, low_index, high_index, depth_limit);
        insertion_sort(tab, low_index, high_index);
    }
};

#endif