#include "Contact_With_DB/Data_Base_contact.cpp"
#include "destination_functions/Coordinates_Calculations.cpp"
#include "Drawing_Map/Map_Draw.cpp"

int main()
{

std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
std::vector<std::pair<int, int>> firstStation = GetOneStationCoords("Staszów", allStations);
std::vector<std::pair<int, int>> secondStation = GetOneStationCoords("Przemyśl", allStations);
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

//TODO:
//sort stations so that path is more logical maybe or something so it looks more natural
//change sp that stations cannot go aboxe, below or behind end stations
//check for more edge cases and bugs

return 0;
}