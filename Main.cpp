#include "Contact_With_DB/Data_Base_contact.cpp"
#include "destination_functions/Coordinates_Calculations.cpp"
#include "Drawing_Map/Map_Draw.cpp"

int main()
{

std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
std::vector<std::pair<int, int>> firstStation = GetOneStationCoords("Gdańsk", allStations);
std::vector<std::pair<int, int>> secondStation = GetOneStationCoords("Zakopane", allStations);
/*
for (const auto &elem : getPointsBetweenTwoStations(firstStation, secondStation))
{
    std::cout << elem.first << ", " << elem.second << "\n";
}

std::cout << "------\n";*/
// Add for all stations i know the drill
//std::vector<std::pair<int, int>> WholePath;
//WholePath = addMoreValues(WholePath, getPointsBetweenTwoStations(firstStation, secondStation));

//get all stations between two stations stations
/*
for (const auto& element : GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation))) {
        std::cout << element.first << " "<< element.second <<"\n";
}*/
/*
std::vector<std::pair<int, int>> WholePath = GetPathBetweenMultipleStations(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation)));
for (const auto &elem : WholePath)
{
    std::cout << elem.first << ", " << elem.second << "\n";
}
*/
//Drawing map
DrawMap(allStations, GetPathBetweenMultipleStations(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation))));
//DrawMap(allStations, getPointsBetweenTwoStations(firstStation, secondStation));

return 0;
}