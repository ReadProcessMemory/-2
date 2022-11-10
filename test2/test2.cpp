#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <time.h>




/*
1. Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, на которые указывают эти указатели (нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).
2. Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей и сортирует указатели по значениям, на которые они указывают.
3. Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:

○ count_if и find
○ count_if и цикл for
○ цикл for и find
○ 2 цикла for
Замерьте время каждого способа подсчета и сделайте выводы.
Справка:
count_if - это алгоритмическая функция из STL, которая принимает 3 параметра: итератор на начало, итератор на конец и унарный предикат (функцию, принимающую один параметр и возвращающую тип bool).
find - это метод класса string, который возвращает позицию символа (строки), переданного в качестве параметра, в исходной строке. Если символ не найден, то метод возвращает string::npos.
*/


//№1
template <typename type>
void swap_data(type*& arg_1, type*& arg_2) { //&
    type* swap = arg_1;
    arg_1 = arg_2;
    arg_2 = swap;
}

void num_1()
{
    int* to_test_swap = new int{ 1337 };
    int* to_test_swap1 = new int{ 0xDEAD };

    std::cout << std::hex << to_test_swap << std::endl;
    std::cout << std::hex << to_test_swap1 << std::endl << std::endl;

    swap_data<int>(to_test_swap, to_test_swap1);

    std::cout << std::hex << to_test_swap << std::endl;
    std::cout << std::hex << to_test_swap1 << std::endl << std::endl;
}


//№2
template <typename type>
void sort_pointers(std::vector<type*>& vector)
{
    bool bis_swapped;
    do
    {
        bis_swapped = false;
        typename std::vector<type*>::iterator this_vec;
        for (this_vec = vector.begin(); this_vec < vector.end() - 1; ++this_vec)
        {
            if (*(this_vec + 1) < *this_vec)
            {
                swap_data<type>((*(this_vec + 1)), *this_vec);
                bis_swapped = true;
            }
        }
    } while (bis_swapped);
}


void num_2()
{
    std::vector<int*> test_vector;

    long ltime = time(0);
    int stime = (unsigned int)ltime / 2;
    srand(stime);

    for (size_t i = 0; i < 5; i++)
    {
        int* test = new int;
        *test = rand() % 1000;
        test_vector.push_back(test);
    }

    int i = 0;
    for (int* real_time_vector : test_vector)
    {
        i++;
        std::cout << "vec: " << i << " | " << real_time_vector << " | " << *real_time_vector << std::endl;
    }
    sort_pointers<int>(test_vector);
    std::cout << "sorted pointers: " << std::endl;

    i = 0;
    for (int* real_time_vector : test_vector)
    {
        i++;
        std::cout << "vec: " << i << " | " << real_time_vector << " | " << *real_time_vector << std::endl;
    }

}

//№3
void num_3(int type)
{
    int vowels = 0;
    std::vector<char> book;
    std::ifstream book_file("book.txt");
    std::vector<char> vowel_letters{ 'a', 'e', 'i', 'y', 'u', 'o', 'A', 'E', 'I', 'Y', 'U', 'O' }; //https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.grammar-monster.com%2Fglossary%2Fvowels.htm&psig=AOvVaw0q6rGAixqp5xa6IQaCKzSB&ust=1668185863471000&source=images&cd=vfe&ved=0CA0QjRxqFwoTCPiwoa2KpPsCFQAAAAAdAAAAABAD
    if (book_file)
    {
        char letters;
        while (!book_file.eof())
        {
            book_file.get(letters);
            book.push_back(letters);
        }

        if (type == 1) //count_if и find (№1)  //works
        {
            vowels = count_if(book.begin(), book.end(), [&](char letters)
            {
                if (std::find(vowel_letters.begin(), vowel_letters.end(), letters) != vowel_letters.end())
                {
                    return true;
                }
                return false;
            });
        }

        if (type == 2) //count_if и цикл for (№2)
        {
            vowels = count_if(book.begin(), book.end(), [&](char letters)
            {
                for (char vowel : vowel_letters)
                {
                    if (letters == vowel)
                    {
                        return true;
                    }
                }
                return false;
            });
        }

        if (type == 3) //цикл for и find (№3)
        {
            for (char letter : book)
            {
                if (std::find(vowel_letters.begin(), vowel_letters.end(), letters) != vowel_letters.end())
                {
                    ++vowels;
                }
            }
        }

        if (type == 4) //2 цикла for (№4)
        {
            for (char letter : book)
            {
                for (char vowel : vowel_letters)
                {
                    if (letter == vowel)
                    {
                        ++vowels;
                    }
                }
            }
        }

        std::cout << "vowels: " << vowels << std::endl;
    }
}

int main()
{
    ////№1
    num_1();

    std::cout << std::endl;
    std::cout << std::endl;

    ////№2
    num_2();

    std::cout << std::endl;
    std::cout << std::endl;

    //№3
    num_3(4);

    std::cout << "Hello EFI World!\n";

}
