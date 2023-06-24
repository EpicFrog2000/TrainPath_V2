cmake_minimum_required(VERSION 3.26)
project(TrainPath VERSION 1.0.0)

add_subdirectory(Drawing_Map)
add_subdirectory(destination_functions)
add_subdirectory(Contact_With_DB)
add_executable(Program Main.cpp)

# Pobierz flagi kompilacji i biblioteki z mysql_config
execute_process(COMMAND mysql_config --cflags OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

# Dodaj flagi kompilacji
add_compile_options(${MYSQL_CFLAGS})

# Podłącz biblioteki
target_link_libraries(Program PRIVATE ${MYSQL_LIBS})

target_link_libraries(Program PRIVATE DrawFunctions ContactDB DestinationFunctions)

