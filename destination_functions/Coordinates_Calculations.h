#ifndef MYHEADER_H
#define MYHEADER_H
#include <string>
#include <vector>
#include <set>
#include <iostream>

std::vector<std::pair<int, int>> getPointsBetweenTwoStations(const std::vector<std::pair<int, int>>& firstStation, const std::vector<std::pair<int, int>>& secondStation);
std::vector<std::pair<int, int>> addMoreValues(const std::vector<std::pair<int, int>>& vec1, const std::vector<std::pair<int, int>>& vec2);
std::set<std::pair<int, int>> GetStationsFromArea(const std::vector<std::pair<std::string, std::pair<int, int>>>& allStations, const std::vector<std::pair<int, int>>& pathBetweenStations);
std::vector<std::pair<int, int>> GetPathBetweenMultipleStations();

#endif 
