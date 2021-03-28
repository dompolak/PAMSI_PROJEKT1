#include "efficiency_test.hh"

void EfficiencyTest::allocate_memory(int **&tab, int size)
{
    tab = new int *[this->size1];

    for(int i(0); i < size1; i++)
        { tab[i] = new int[size]; }
}

void EfficiencyTest::delete_array(int **&tab, int size)
{
    for(int j(0); j < size1; j++)
        { delete [] tab[j]; }
    delete [] tab;     
    tab = NULL;
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
            
        quick_sort(tab[i], 0, part-1);
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

void EfficiencyTest::is_sorted(int **&tab, int size)
{   
    for(int i(0); i < 100; i++)
    {
        if(!is_sort_ascending(tab[i], size))
        { 
            std::cerr << "Nie udalo sie przeprowadzic testow" << std::endl;
            exit(0);
        }
    }
}  

void EfficiencyTest::copy_array(int **&tab, int **&pom, int size)
{
    for(int i(0); i < 100; i++){
        for(int j(0); j < size; j++){
            pom[i][j] = tab[i][j];
        }
    }

}

double EfficiencyTest::introspective_sort_test(int **&tab, int size)
{   
    auto start = std::chrono::steady_clock::now();
    for(int i(0); i < 100; i++)
    {   
        introspective_sort(tab[i], 0, size-1);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return  elapsed_seconds.count();
}

double EfficiencyTest::quick_sort_test(int **&tab, int size)
{   
    auto start = std::chrono::steady_clock::now();
    for(int i(0); i < 100; i++)
    {   
        quick_sort(tab[i], 0, size-1);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return  elapsed_seconds.count();
}


double EfficiencyTest::merge_sort_test(int **&tab, int size)
{   
    auto start = std::chrono::steady_clock::now();
    for(int i(0); i < 100; i++)
    {   
        merge_sort(tab[i], 0, size-1);
    }
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
        int **pom;
        allocate_memory(tab, size2[i]);
        allocate_memory(pom, size2[i]);
        generate_array(tab, size2[i]);
        
        copy_array(tab, pom, size2[i]);
        double time = introspective_sort_test(pom, size2[i]);
        is_sorted(pom, size2[i]);
        name_file = "introspective_sort_" + sizes[i];
        save_result(name_file, time, test1);

        copy_array(tab, pom, size2[i]);
        time = quick_sort_test(pom, size2[i]);
        is_sorted(pom, size2[i]);
        name_file = "quick_sort_" + sizes[i];
        save_result(name_file, time, test1);

        copy_array(tab, pom, size2[i]);
        time = merge_sort_test(pom, size2[i]);
        is_sorted(pom, size2[i]);
        name_file = "merge_sort_" + sizes[i];
        save_result(name_file, time, test1);

        delete_array(pom, size2[i]);
        delete_array(tab, size2[i]);
    }       
}

void EfficiencyTest::test_part_sort_elements()
{
    std::string part_pom[6] = {"25", "50", "75", "95", "99", "997"};
    std::string name_file;

    for(int i(0); i < 5; i++)
    {   
        int **tab;
        int **pom;
        allocate_memory(tab, size2[i]);
        allocate_memory(pom, size2[i]);

        for(int k(0); k < 6; k++)
        {   
            generate_array(tab, size2[i], part_sorted[k]);
            
            copy_array(tab, pom, size2[i]);
            double time = introspective_sort_test(pom, size2[i]);
            is_sorted(pom, size2[i]);
            name_file = "introspective_sort_" + sizes[i]+ "_" + part_pom[k];
            save_result(name_file, time, test2);

            copy_array(tab, pom, size2[i]);
            time = quick_sort_test(pom, size2[i]);
            is_sorted(pom, size2[i]);
            name_file = "quick_sort_" + sizes[i]+ "_" + part_pom[k];
            save_result(name_file, time, test2);

            copy_array(tab, pom, size2[i]);
            time = merge_sort_test(pom, size2[i]);
            is_sorted(pom, size2[i]);
            name_file = "merge_sort_" + sizes[i]+ "_" + part_pom[k];
            save_result(name_file, time, test2);
            
        }
        delete_array(pom, size2[i]);
        delete_array(tab, size2[i]);
    }
}

void EfficiencyTest::test_sort_elements_other_dire()
{  
    std::string name_file;

    for(int i(0); i < 5; i++)
    {
        int **tab;
        int **pom;
        allocate_memory(tab, size2[i]);
        allocate_memory(pom, size2[i]);
        generate_array(tab, size2[i], lower);

        copy_array(tab, pom, size2[i]);
        double time = introspective_sort_test(pom, size2[i]);
        is_sorted(pom, size2[i]);
        name_file = "introspective_sort_" + sizes[i] + "dire";
        save_result(name_file, time, test3);

        copy_array(tab, pom, size2[i]);
        time = quick_sort_test(pom, size2[i]);
        is_sorted(pom, size2[i]);
        name_file = "quick_sort_" + sizes[i] + "dire";
        save_result(name_file, time, test3);

        copy_array(tab, pom, size2[i]);
        time = merge_sort_test(pom, size2[i]);
        is_sorted(pom, size2[i]);
        name_file = "merge_sort_" + sizes[i] + "dire";
        save_result(name_file, time, test3);

        delete_array(pom, size2[i]);
        delete_array(tab, size2[i]);
    }
}