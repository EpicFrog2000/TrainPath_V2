#include <iostream>
#include <mysql/mysql.h>
#include <vector>

MYSQL* connect() // Establish the database connection
{
    MYSQL* connection = mysql_init(NULL);
    if (connection == NULL)
    {
        std::cout << "Failed to initialize MySQL connection." << std::endl;
        return NULL;
    }
    
    connection = mysql_real_connect(connection, "localhost", "norbert", "", "pociag_v3", 0, NULL, 0);
    
    if (connection == NULL)
    {
        std::cout << "Failed to connect to the database." << std::endl;
        return NULL;
    }
    
    return connection;
}

MYSQL_RES* queryForConnAndQText(MYSQL* connection, const std::string& QueryText)
{
    const char* query = QueryText.c_str();
    if (mysql_query(connection, query) != 0)
    {
        std::cout << "Failed to execute query: " << mysql_error(connection) << std::endl;
        return NULL;
    }
    
    return mysql_store_result(connection);
}

std::vector<std::pair<std::string, std::pair<int, int>>> GetAllStations()
{
    std::vector<std::pair<std::string, std::pair<int, int>>> allstations;
    MYSQL* connection = connect(); 
    
    if (connection != nullptr)
    {
        const std::string zapytanie = "SELECT `Nazwa_stacji`, `Poz_x`, `Poz_y` FROM stacje;";
        MYSQL_RES* res = queryForConnAndQText(connection, zapytanie); // Execute the query
        
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != NULL) // Fetch rows and print values
            {
                std::string name(row[0]);
                std::string x(row[1]);
                std::string y(row[2]); 
                int tempx = std::stoi(x);
                int tempy = std::stoi(y);
                allstations.emplace_back(name, std::make_pair(tempx, tempy)); 
            }
            
            mysql_free_result(res); // Free the result set
        }
        else
        {
            std::cout << "Failed to execute query." << std::endl;
        }
        
        mysql_close(connection); // Close the database connection
    }
    else
    {
        std::cout << "Failed to connect to the database." << std::endl;
    }
    
    return allstations;
}

std::vector<std::pair<int, int>> GetOneStationCoords(const std::string& stationName, const std::vector<std::pair<std::string, std::pair<int, int>>>& allstations)
{
    std::vector<std::pair<int, int>> stations;
    for (const auto& station : allstations)
    {
        if (station.first == stationName)
        {
            stations.emplace_back(station.second.first, station.second.second);
            break;
        }
    }
    
    return stations;
}
