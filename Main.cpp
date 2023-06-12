#include "Contact_With_DB/contact_with_db.hpp"
#include "destination_functions/Coordinates_Calculations.hpp"
#include "Drawing_Map/Map_Draw.hpp"
#include <vector>
#include <set>
int main()
{
    std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
    std::vector<std::pair<int, int>> firstStation = GetOneStationCoords("Gdańsk", allStations);
    std::vector<std::pair<int, int>> secondStation = GetOneStationCoords("Pabianice", allStations);
    // 2 is best for now i think
    const int ODCHYLENIE = 3; // --- Change if Path is to wonky maybe will find better way later to do this
    std::set<std::pair<int, int>> sortedStations = SortStationsByDistance(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation),ODCHYLENIE), firstStation, secondStation);
    DrawMap(allStations, GetPathBetweenMultipleStations(sortedStations));
    // TODO:
    // sort stations so that path is more logical maybe or something so it looks more natural - done
    // maybe do so that next station cannot me equeal or less distance to endstation - idk
    // change sp that stations cannot go aboxe, below or behind end stations 
    // add function that generates path between given stations in between first nad last station
    // check for more edge cases and bugsqt

    return 0;
}