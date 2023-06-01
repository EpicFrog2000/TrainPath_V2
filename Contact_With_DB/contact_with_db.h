#ifndef MYHEADER_H
#define MYHEADER_H
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <iostream>


MYSQL* connect();
MYSQL_RES* queryForConnAndQText(MYSQL* connection, const std::string QueryText);
std::vector<std::pair<std::string, std::pair<int, int>>>& allstationsGetAllStations();
std::vector<std::pair<int, int>> GetOneStationCoords(const std::string& stationName, const std::vector<std::pair<std::string, std::pair<int, int>>>& allstations);

#endif