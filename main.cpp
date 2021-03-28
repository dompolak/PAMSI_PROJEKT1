#include "efficiency_test.hh"

using std::endl;
using std::cout;
using std::cin;

int main()
{   
    std::srand(time(NULL));
    EfficiencyTest test;

    auto start = std::chrono::steady_clock::now();
    test.test_all_random_elements();
    test.test_part_sort_elements();
    test.test_sort_elements_other_dire();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << elapsed_seconds.count() << endl;
    cout << endl << "KONIEC!!!" << endl;

    return EXIT_SUCCESS;
}