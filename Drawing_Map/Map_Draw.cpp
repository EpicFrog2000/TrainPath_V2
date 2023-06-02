#include "Map_Draw.h"
#include "iostream"
void DrawPlainMap()
{
    for (int i = 0; i <= 100; i++)
    {
        if (i < 10)
        {
            std::cout << "_" << i << "_";
        }
        else if (i >= 10 && i < 100)
        {
            std::cout << i << "_";
        }
        else
        {
            std::cout << i;
        }

        for (int j = 1; j <= 100; j++)
        {
            if (i == 0)
            {
                if (j < 10)
                {
                    std::cout << "_" << j << "_";
                }
                else if (j >= 10 && j < 100)
                {
                    std::cout << j << "_";
                }
                else
                {
                    std::cout << j;
                }
            }
            else if (j == 100)
            {
                std::cout << " | ";
            }
            else
            {
                if (i == 100)
                {
                    std::cout << "___";
                }
                else
                {
                    std::cout << "   ";
                    
                }
            }
        }
        std::cout << "\n";
    }
}
