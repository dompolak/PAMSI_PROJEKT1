#ifndef _QUICK_SORT_HH
#define _QUICK_SORT_HH

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include <chrono>
#include<fstream>

enum sort_direction {lower, higher};

class QuickSort
{

protected:
    template<class T>
    void partition(T *tab, long &i, long &j, T &pivot)
    {
        
        while(1)
        {   
            while(pivot>tab[++i]); 
            while(pivot<tab[--j]);

            if(i<=j)
                std::swap(tab[i], tab[j]);
            else
                break;
        
        }
    }

    template<class T>
    void partition(T *tab, long &i, long &j, T &pivot, sort_direction direction)
    {
        
        while(1)
        {   
            if(direction == lower)
            {
                while(pivot<tab[++i]); 
                while(pivot>tab[--j]);
            }
            if(direction == higher)
            {
                while(pivot>tab[++i]); 
                while(pivot<tab[--j]);
            }

            if(i<=j)
                std::swap(tab[i], tab[j]);
            else
                break;
        
        }
    }
    
public:
    template<class T>
    void quick_sort(T *tab, long low_index, long high_index)
    {   
        if(high_index <= low_index)
            { return; }

        long i = low_index-1;
        long j = high_index+1;
        T pivot = tab[(low_index+high_index)/2];

        partition(tab, i, j, pivot);

        if(j>low_index)
            { quick_sort(tab, low_index, j); }
        if(i<high_index)
            { quick_sort(tab, i, high_index); }

    }

    template<class T>
    void quick_sort(T *tab, long low_index, long high_index, sort_direction direction)
    {      
        if(direction != lower && direction != higher)
        { 
            std::cerr << "Zly kierunek sortowania" << std::endl;
            return; 
        }

        if(high_index <= low_index)
            { return; }

        long i = low_index-1;
        long j = high_index+1;
        T pivot = tab[(low_index+high_index)/2];

        partition(tab, i, j, pivot, direction);

        if(j>low_index)
            { quick_sort(tab, low_index, j, direction); }
        if(i<high_index)
            { quick_sort(tab, i, high_index, direction); }

    }
};

#endif