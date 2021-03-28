#include "efficiency_test.hh"

void EfficiencyTest::allocate_memory(int **&tab, int size)
{
    tab = new int *[this->size1];

    for(int i(0); i < size1; i++)
        { tab[i] = new int[size]; }
}

void EfficiencyTest::generate_array(int **&tab, int size)
{   
    for(int i(0); i < size1; i++)
    {
        for(int j(0); j < size; j++ )
        { tab[i][j] = std::rand() % max_value; }
    }
} 

void EfficiencyTest::generate_array(int **&tab, int size, double part_sorted)
{
    int part = part_sorted*size/100;
    int max = part_sorted*max_value/100;

    for (int i(0); i < size1; i++)
    {
        for(int j(0); j < size; j++)
        {
            if(j < part)
                { tab[i][j] = std::rand() % max; }
            else
                { tab[i][j] = std::rand() % max_value + max; }
        }
            
        introspective_sort(tab[i], 0, part-1);
    }

}

void EfficiencyTest::generate_array(int **&tab, int size, sort_direction direction)
{           
    for(int i(0); i < size1; i++)
    {
        for(int j(0); j < size; j++ )
        { tab[i][j] = std::rand() % max_value; }

        quick_sort(tab[i], 0, size-1, direction);
    }
} 

void EfficiencyTest::save_result(std::string &name, double &data, dir location)
{   
    std::string source;
    switch(location)
    {
        case test1:
            source =".\\dane\\test1\\" + name + ".txt";
            break;
        case test2:
            source =".\\dane\\test2\\" + name + ".txt";
            break;
        case test3:
            source =".\\dane\\test3\\" + name + ".txt";
            break;
        default:
            std::cerr << "Nie udalo sie zapisac" << std::endl;
            return;
    }
    
    std::ofstream file;
    file.open(source, std::ios::app);

    if(file.fail())
    {
        std::cerr << "Nie udalo sie zapisac" << std::endl;
        return;
    }

    file << data << std::endl;
    file.close();
}

void EfficiencyTest::is_sorted(int *tab, int size)
{
    if(!is_sort_ascending(tab, size))
        { 
            std::cerr << "Nie udalo sie przeprowadzic testow" << std::endl;
            exit(1);
        }
}  

double EfficiencyTest::introspective_sort_test(int *&tab, int size)
{
    auto start = std::chrono::steady_clock::now();
    introspective_sort(tab, 0, size-1);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    return  elapsed_seconds.count();
}

double EfficiencyTest::quick_sort_test(int *&tab, int size)
{
    auto start = std::chrono::steady_clock::now();
    quick_sort(tab, 0, size-1);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    return  elapsed_seconds.count();
}


double EfficiencyTest::merge_sort_test(int *&tab, int size)
{
    auto start = std::chrono::steady_clock::now();
    merge_sort(tab, 0, size-1);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    return  elapsed_seconds.count();
}

void EfficiencyTest::test_all_random_elements()
{  
    std::string name_file;

    for(int i(0); i < 5; i++)
    {
        int **tab;
        allocate_memory(tab, size2[i]);
        generate_array(tab, size2[i]);

        for(int j(0); j < 100; j++)
        {
            double time = introspective_sort_test(tab[j], size2[i]);
            is_sorted(tab[j], size2[i]);
            name_file = "introspective_sort_" + sizes[i];
            save_result(name_file, time, test1);
        }

        generate_array(tab, size2[i]);

        for(int j(0); j < 100; j++)
        {
            double time = quick_sort_test(tab[j], size2[i]);
            is_sorted(tab[j], size2[i]);
            name_file = "quick_sort_" + sizes[i];
            save_result(name_file, time, test1);
        }

        generate_array(tab, size2[i]);

        for(int j(0); j < 100; j++)
        {
            double time = merge_sort_test(tab[j], size2[i]);
            is_sorted(tab[j], size2[i]);
            name_file = "merge_sort_" + sizes[i];
            save_result(name_file, time, test1);
        }

        delete []*tab;

    }
        
}

void EfficiencyTest::test_part_sort_elements()
{
    std::string part_pom[6] = {"25", "50", "75", "95", "99", "997"};
    std::string name_file;

    for(int i(0); i < 5; i++)
    {   
        int **tab;
        allocate_memory(tab, size2[i]);
        for(int k(0); k < 6; k++)
        {
            generate_array(tab, size2[i], part_sorted[k]);

            for(int j(0); j < 100; j++)
            {
                double time = introspective_sort_test(tab[j], size2[i]);
                is_sorted(tab[j], size2[i]);
                name_file = "introspective_sort_" + sizes[i]+ "_" + part_pom[k];
                save_result(name_file, time, test2);
            }

            generate_array(tab, size2[i], part_sorted[k]);

            for(int j(0); j < 100; j++)
            {
                double time =quick_sort_test(tab[j], size2[i]);
                is_sorted(tab[j], size2[i]);
                name_file = "quick_sort_" + sizes[i]+ "_" + part_pom[k];
                save_result(name_file, time, test2);
            }

            generate_array(tab, size2[i], part_sorted[k]);

            for(int j(0); j < 100; j++)
            {   
                double time = merge_sort_test(tab[j], size2[i]);
                is_sorted(tab[j], size2[i]);
                name_file = "merge_sort_" + sizes[i]+ "_" + part_pom[k];
                save_result(name_file, time, test2);
            }
            
        }

        delete []*tab;
    }
}

void EfficiencyTest::test_sort_elements_other_dire()
{  
    std::string name_file;

    for(int i(0); i < 5; i++)
    {
        int **tab;
        allocate_memory(tab, size2[i]);
        generate_array(tab, size2[i], lower);

        for(int j(0); j < 100; j++)
        {
            double time = introspective_sort_test(tab[j], size2[i]);
            is_sorted(tab[j], size2[i]);
            name_file = "introspective_sort_" + sizes[i] + "dire";
            save_result(name_file, time, test3);
        }

        generate_array(tab, size2[i], lower);

        for(int j(0); j < 100; j++)
        {
            double time = quick_sort_test(tab[j], size2[i]);
            is_sorted(tab[j], size2[i]);
            name_file = "quick_sort_" + sizes[i] + "dire";
            save_result(name_file, time, test3);
        }

        generate_array(tab, size2[i], lower);

        for(int j(0); j < 100; j++)
        {
            double time = merge_sort_test(tab[j], size2[i]);
            is_sorted(tab[j], size2[i]);
            name_file = "merge_sort_" + sizes[i] + "dire";
            save_result(name_file, time, test3);
        }

        delete []*tab;

    }
        
}