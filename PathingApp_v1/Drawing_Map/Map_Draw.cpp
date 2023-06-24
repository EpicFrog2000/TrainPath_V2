#include "Map_Draw.hpp"

void DrawMap(const std::vector<std::pair<std::string, std::pair<int, int>>>& allStations, std::vector<std::pair<int, int>> path)
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
                    bool drawn = false;
                    for (const auto& station : allStations)
                    {
                        if (station.second.first == j && station.second.second == i)
                        {
                            std::cout << "_S_";
                            drawn = true;
                            break;
                        }
                    }
                    if (!drawn)
                    {
                        bool pathFound = false;
                        for (const auto& wholePath : path)
                        {
                            if (wholePath.first == j && wholePath.second == i)
                            {
                                std::cout << " * ";
                                pathFound = true;
                                break;
                            }
                        }
                        if (!pathFound)
                        {
                            std::cout << "   ";
                        }
                    }
                }
            }
        }
        std::cout << "\n";
    }
}
