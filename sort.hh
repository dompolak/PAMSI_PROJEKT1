#ifndef _SORT_HH
#define _SORT_HH

#include "introspective_sort.hh"

class Sort : public MergeSort, public IntrospectiveSort
{



public:

    template<class T>
    bool is_sort_ascending(T *tab, long size)
    {
        for(long i(0); i < size-1; i++)
        {
            if(tab[i] > tab[i+1])
                { return false; }
        }

        return true;
    }

    template<class T>
    bool is_sort_descending(T *tab, long size)
    {
        for(long i(0); i < size-1; i++)
        {
            if(tab[i] < tab[i+1])
                { return false; }
        }
        
        return true;
    }

    template<class T>
    bool is_sort(T *tab, long size)
    {
        if(is_sort_ascending(tab, size) && !is_sort_descending(tab, size))
            { return true;}
        
        if(!is_sort_ascending(tab, size) && is_sort_descending(tab, size))
            { return true;}

        return false;

    }
};

#endif