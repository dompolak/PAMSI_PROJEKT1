#ifndef _MERGE_SORT_HH
#define _MERGE_SORT_HH
#include "quick_sort.hh"

class MergeSort
{

protected:
    template<class T>
    void merge(T *tab, long low_index, long middle_index, long high_index)
    {
        int lsize = middle_index - low_index + 1;
	    int hsize = high_index - middle_index;

	    int* tabL = new int[lsize];
	    int* tabH = new int[hsize];
 
	    for (int i(0); i < lsize; i++)
		    tabL[i] = tab[low_index + i];
	    for (int i(0); i < hsize; i++)
		    tabH[i] = tab[middle_index + i + 1];
 
	    int i = 0, j = 0, currIndex = low_index;
 
	    while(i < lsize && j < hsize)
        {
		    if (tabL[i] <= tabH[j])
			    { tab[currIndex++] = tabL[i++]; }
		    else
			    { tab[currIndex++] = tabH[j++]; }
	    }
 
	    while (i < lsize)
		    { tab[currIndex++] = tabL[i++]; }
 
	    while (j < hsize)
		    { tab[currIndex++] = tabH[j++]; }
 
	    delete[] tabL;
	    delete[] tabH;
    }

public:

    template<class T>
    void merge_sort(T *tab, long low_index, long high_index)
    {   
        if(high_index <= low_index)
            { return; }
        
        long middle_index = (low_index+high_index)/2;

        merge_sort(tab, low_index, middle_index);
        merge_sort(tab, middle_index+1, high_index);

        merge(tab, low_index, middle_index, high_index);

    }
};

#endif