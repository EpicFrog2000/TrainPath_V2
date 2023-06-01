#include "Coordinates_Calculations.h"

std::vector<std::pair<int, int>> getPointsBetweenTwoStations(const std::vector<std::pair<int, int>>& firstStation, const std::vector<std::pair<int, int>>& secondStation) {
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

        points.emplace_back(x, y);

    return points;
}
