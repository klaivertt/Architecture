// Template.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Template.h"
#include "Common.h"
int main()
{
    int a = 1;
    int b = 2;

    swap<int>(a, b);

    std::cout << "A : " << a << " B : " << b << std::endl;

    Pair<int, int> pair(-1, 3);

    std::cout << "Value 1 : " << pair.GetFirst() << " value2 : " << pair.GetSecond() << std::endl;

    Array<int> array(10);

    for (size_t i = 0; i < array.size(); ++i)
    {
        array[i] = Rand();
        std::cout << "index " << i << " value " << array[i] << std::endl;
    }



    system("pause");
    return EXIT_SUCCESS;
}