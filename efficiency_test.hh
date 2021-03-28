#ifndef _EFFICIENCY_TEST_HH
#define _EFFICIENCY_TEST_HH

#include "sort.hh"

enum dir {test1, test2, test3};

class EfficiencyTest : public Sort
{   
    int size1 = 100;
    int size2[5] = {10000, 50000, 100000, 500000, 1000000};
    std::string sizes[5] = {"10000", "50000", "100000", "500000", "1000000"};
    double part_sorted[6] = {25, 50, 75, 95, 99, 99.7};
    int max_value = 100;

public:
    void generate_array(int **&tab, int size);
    void generate_array(int **&tab, int size, double part_sorted);
    void generate_array(int **&ab, int size, sort_direction direction);
    void allocate_memory(int **&tab, int size);
    void delete_array(int **&tab, int size);
    void save_result(std::string &name, double &dane, dir location);
    void is_sorted(int **&tab, int size);
    void copy_array(int **&tab, int **&pom, int size);
    double introspective_sort_test(int **&tab, int size);
    double quick_sort_test(int **&tab, int size);
    double merge_sort_test(int **&tab, int size);
    void test_all_random_elements();
    void test_part_sort_elements();
    void test_sort_elements_other_dire();

};

#endif