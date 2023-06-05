#include "Contact_With_DB/Data_Base_contact.cpp"
#include "destination_functions/Coordinates_Calculations.cpp"
#include "Drawing_Map/Map_Draw.cpp"

int main()
{

    std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
    std::vector<std::pair<int, int>> firstStation = GetOneStationCoords("Ostrów Wielkopolski", allStations);
    std::vector<std::pair<int, int>> secondStation = GetOneStationCoords("Mońki", allStations);
    const int ODCHYLENIE = 2; // --- Change if Path is to wonky maybe will find better way later to do this
    std::set<std::pair<int, int>> sortedStations = SortStationsByDistance(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation),ODCHYLENIE), firstStation, secondStation);
    DrawMap(allStations, GetPathBetweenMultipleStations(sortedStations));
    // TODO:
    // sort stations so that path is more logical maybe or something so it looks more natural - done
    // maybe do so that next station cannot me equeal or less distance to endstation - idk
    // change sp that stations cannot go aboxe, below or behind end stations 
    // check for more edge cases and bugs

    return 0;
}