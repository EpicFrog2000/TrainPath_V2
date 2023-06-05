#include "Coordinates_Calculations.h"
#include <cmath>
#include <algorithm>
std::vector<std::pair<int, int>> getPointsBetweenTwoStations(const std::vector<std::pair<int, int>> &firstStation, const std::vector<std::pair<int, int>> &secondStation)
{
    int startX = firstStation[0].first;
    int startY = firstStation[0].second;
    int endX = secondStation[0].first;
    int endY = secondStation[0].second;

    // Calculate the differences and absolute values
    int dx = std::abs(endX - startX);
    int dy = std::abs(endY - startY);

    // Calculate the increments
    int incrementX = (startX < endX) ? 1 : -1;
    int incrementY = (startY < endY) ? 1 : -1;

    int x = startX;
    int y = startY;

    // Determine the dominant axis
    bool isXDominant = dx > dy;

    // Calculate the error
    int error = (isXDominant ? dx : dy) / 2;

    std::vector<std::pair<int, int>> points;
    points.emplace_back(x, y);

    while (x != endX || y != endY)
    {
        if (isXDominant)
        {
            x += incrementX;
            error -= dy;
            if (error < 0)
            {
                y += incrementY;
                error += dx;
            }
        }
        else
        {
            y += incrementY;
            error -= dx;
            if (error < 0)
            {
                x += incrementX;
                error += dy;
            }
        }

        points.emplace_back(x, y);
    }

    return points;
}

std::vector<std::pair<int, int>> addMoreValues(const std::vector<std::pair<int, int>> &vec1, const std::vector<std::pair<int, int>> &vec2)
{
    std::vector<std::pair<int, int>> result = vec1;

    // Add the values from vec2 to result vector
    result.insert(result.end(), vec2.begin(), vec2.end());

    return result;
}

double DistanceToLineSegment(int x, int y, int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    if (dx == 0 && dy == 0)
    {
        // The segment is actually a point
        dx = x - x1;
        dy = y - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

    double t = ((x - x1) * dx + (y - y1) * dy) / (dx * dx + dy * dy);

    if (t < 0)
    {
        // Closest point is beyond the 'x1' end of the segment
        dx = x - x1;
        dy = y - y1;
    }
    else if (t > 1)
    {
        // Closest point is beyond the 'x2' end of the segment
        dx = x - x2;
        dy = y - y2;
    }
    else
    {
        // Closest point is within the segment
        double closestX = x1 + t * dx;
        double closestY = y1 + t * dy;
        dx = x - closestX;
        dy = y - closestY;
    }

    return std::sqrt(dx * dx + dy * dy);
}

std::set<std::pair<int, int>> GetStationsFromArea(const std::vector<std::pair<std::string, std::pair<int, int>>> &allStations, const std::vector<std::pair<int, int>> &pathBetweenStations, const int &ODCHYLENIE)
{
    std::set<std::pair<int, int>> SetOfStationsOnPath;

    if (pathBetweenStations.size() < 2)
    {
        return SetOfStationsOnPath; // Return empty set if there are not enough points in the path
    }

    for (const auto &station : allStations)
    {
        const std::pair<int, int> &stationCoords = station.second;
        int stationX = stationCoords.first;
        int stationY = stationCoords.second;

        bool withinDistance = false;

        // Check the distance between the station and each segment of the path
        for (size_t i = 0; i < pathBetweenStations.size() - 1; i++)
        {
            const std::pair<int, int> &pointA = pathBetweenStations[i];
            const std::pair<int, int> &pointB = pathBetweenStations[i + 1];

            // Calculate the distance from the station to the line segment defined by pointA and pointB
            double distance = DistanceToLineSegment(stationX, stationY, pointA.first, pointA.second, pointB.first, pointB.second);

            if (distance <= ODCHYLENIE)
            {
                withinDistance = true;
                break; // No need to check other segments
            }
        }

        if (withinDistance)
        {
            SetOfStationsOnPath.insert(stationCoords);
        }
    }

    return SetOfStationsOnPath;
}

std::set<std::pair<int, int>> SortStationsByDistance(std::set<std::pair<int, int>> Stations, const std::vector<std::pair<int, int>> firstStation, const std::vector<std::pair<int, int>> lastStation)
{
    // Calculate the distance of each station from the first and last stations
    std::vector<std::pair<int, std::pair<int, int>>> distances;
    for (const auto &station : Stations)
    {
        int distanceFromFirst = (station.first - firstStation[0].first) * (station.first - firstStation[0].first) +
                                (station.second - firstStation[0].second) * (station.second - firstStation[0].second);
        int distanceFromLast = (station.first - lastStation[0].first) * (station.first - lastStation[0].first) +
                               (station.second - lastStation[0].second) * (station.second - lastStation[0].second);
        distances.push_back(std::make_pair(distanceFromFirst, station));
        distances.push_back(std::make_pair(distanceFromLast, station));
    }

    // Sort the stations based on their distances from the first and last stations
    std::sort(distances.begin(), distances.end());

    // Create a new set to store the sorted stations
    std::set<std::pair<int, int>> sortedStations;

    // Add the sorted stations to the set
    for (const auto &distance : distances)
    {
        sortedStations.insert(distance.second);
    }

    return sortedStations;
}

std::vector<std::pair<int, int>> GetPathBetweenMultipleStations(const std::set<std::pair<int, int>> &stations)
{
    std::vector<std::pair<int, int>> WholePath;

    std::pair<int, int> prevStation; // Previous station coordinates

    for (const auto &station : stations)
    {
        if (prevStation != std::pair<int, int>())
        {
            std::vector<std::pair<int, int>> pathBetweenStations = getPointsBetweenTwoStations({prevStation}, {station});
            WholePath.insert(WholePath.end(), pathBetweenStations.begin(), pathBetweenStations.end());
        }

        prevStation = station;
    }

    return WholePath;
}