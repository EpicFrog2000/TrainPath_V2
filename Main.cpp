#include "Contact_With_DB/Data_Base_contact.cpp"
#include "destination_functions/Coordinates_Calculations.cpp"

int main()
{
std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
std::vector<std::pair<int, int>> firstStation = GetOneStationCoords("Kraków", allStations);
std::vector<std::pair<int, int>> secondStation = GetOneStationCoords("Gdańsk", allStations);
getPointsBetweenTwoStations(firstStation, secondStation);
//for (const auto &elem : getPointsBetweenTwoStations(firstStation, secondStation))
//{
//    std::cout << elem.first << ", " << elem.second << "\n";
//}
//Drawing map
return 0;
}