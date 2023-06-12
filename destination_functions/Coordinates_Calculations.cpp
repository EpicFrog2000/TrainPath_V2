#include "Coordinates_Calculations.hpp"
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

std::vector<std::pair<int, int>> addMoreValues(const std::vector<std::pair<int, int>>& vec1, const std::vector<std::pair<int, int>>& vec2)
{
    std::vector<std::pair<int, int>> result;
    result.reserve(vec1.size() + vec2.size()); // Reserve space for the result vector

    // Append the values from vec1
    result.insert(result.end(), vec1.begin(), vec1.end());

    // Append the values from vec2
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
        return std::hypot(dx, dy); // Use hypot function to calculate the Euclidean distance
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

    return std::hypot(dx, dy); // Use hypot function to calculate the Euclidean distance
}

std::set<std::pair<int, int>> GetStationsFromArea(const std::vector<std::pair<std::string, std::pair<int, int>>>& allStations, const std::vector<std::pair<int, int>>& pathBetweenStations, const int& ODCHYLENIE)
{
    std::set<std::pair<int, int>> SetOfStationsOnPath;

    if (pathBetweenStations.size() < 2)
    {
        return SetOfStationsOnPath; // Return empty set if there are not enough points in the path
    }

    for (const auto& station : allStations)
    {
        bool withinDistance = false;

        const int stationX = station.second.first;
        const int stationY = station.second.second;

        // Check the distance between the station and each segment of the path
        for (size_t i = 0; i < pathBetweenStations.size() - 1; i++)
        {
            const auto& pointA = pathBetweenStations[i];
            const auto& pointB = pathBetweenStations[i + 1];

            // Calculate the distance from the station to the line segment defined by pointA and pointB
            const double distance = DistanceToLineSegment(stationX, stationY, pointA.first, pointA.second, pointB.first, pointB.second);

            if (distance <= ODCHYLENIE)
            {
                withinDistance = true;
                break; // No need to check other segments
            }
        }

        if (withinDistance)
        {
            SetOfStationsOnPath.insert(station.second);
        }
    }

    return SetOfStationsOnPath;
}

std::set<std::pair<int, int>> SortStationsByDistance(std::set<std::pair<int, int>> Stations, const std::vector<std::pair<int, int>>& firstStation, const std::vector<std::pair<int, int>>& lastStation)
{
    // Create a lambda function for calculating the squared distance between two points
    auto distanceFunc = [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        int dx = p1.first - p2.first;
        int dy = p1.second - p2.second;
        return dx * dx + dy * dy;
    };

    // Calculate the distance of each station from the first and last stations
    std::vector<std::pair<int, std::pair<int, int>>> distances;
    for (const auto& station : Stations)
    {
        int distanceFromFirst = distanceFunc(station, firstStation[0]);
        int distanceFromLast = distanceFunc(station, lastStation[0]);
        distances.emplace_back(distanceFromFirst, station);
        distances.emplace_back(distanceFromLast, station);
    }

    // Sort the stations based on their distances from the first and last stations
    std::sort(distances.begin(), distances.end());

    // Create a new set to store the sorted stations
    std::set<std::pair<int, int>> sortedStations;

    // Add the sorted stations to the set
    for (const auto& distance : distances)
    {
        sortedStations.insert(distance.second);
    }

    return sortedStations;
}

std::vector<std::pair<int, int>> GetPathBetweenMultipleStations(const std::set<std::pair<int, int>>& stations)
{
    std::vector<std::pair<int, int>> WholePath;

    if (stations.empty())
    {
        return WholePath; // Return empty path if there are no stations
    }

    auto it = stations.begin();
    std::pair<int, int> prevStation = *it; // Initialize prevStation with the first station

    for (++it; it != stations.end(); ++it)
    {
        const auto& station = *it;
        std::vector<std::pair<int, int>> pathBetweenStations = getPointsBetweenTwoStations({ prevStation }, { station });
        WholePath.insert(WholePath.end(), pathBetweenStations.begin(), pathBetweenStations.end());
        prevStation = station;
    }

    return WholePath;
}