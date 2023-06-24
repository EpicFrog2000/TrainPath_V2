cmake_minimum_required(VERSION 3.12)
project(TrainPathOpenGl VERSION 1.1.0)

add_subdirectory(Drawing_Map)
add_subdirectory(destination_functions)
add_subdirectory(Contact_With_DB)
add_executable(Program draw.cpp SimpleVertexShader.vertexshader SimpleFragmentShader.fragmentshader)

# Add the required libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(GLUT REQUIRED)


# Pobierz flagi kompilacji i biblioteki z mysql_config
execute_process(COMMAND mysql_config --cflags OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/SimpleVertexShader.vertexshader
    ${PROJECT_BINARY_DIR}/SimpleVertexShader.vertexshader
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/SimpleFragmentShader.fragmentshader
    ${PROJECT_BINARY_DIR}/SimpleFragmentShader.fragmentshader
    COMMENT "Copying resources into binary directory")

add_dependencies(Program copy_resources)

# Dodaj flagi kompilacji
add_compile_options(${MYSQL_CFLAGS})

# Podłącz biblioteki
target_link_libraries(Program PRIVATE ${MYSQL_LIBS})

target_link_libraries(Program PRIVATE DrawFunctions ContactDB DestinationFunctions)

target_link_libraries(Program PRIVATE -lglfw -lGL -lGLEW)
target_link_libraries(Program PRIVATE glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

target_sources(Program PRIVATE SimpleVertexShader.vertexshader SimpleFragmentShader.fragmentshader)
target_link_libraries(Program ${ALL_LIBS})
