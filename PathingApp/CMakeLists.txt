cmake_minimum_required(VERSION 3.0)

project(PathingApp_v2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0084 NEW)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "PathingApp")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/PathingApp_v2")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets Widgets)
set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        glwidget.cpp
        glwidget.h
        SimpleFragmentShader.fragmentshader
        SimpleVertexShader.vertexshader
)

add_subdirectory(Drawing_Map)
add_subdirectory(destination_functions)
add_subdirectory(Contact_With_DB)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    add_executable(PathingApp_v2
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PathingApp_v1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PathingApp_v2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PathingApp_v2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PathingApp_v2 PRIVATE Qt6::Widgets)

set_target_properties(PathingApp_v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PathingApp_v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_link_libraries(PathingApp_v2 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Widgets
)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PathingApp_v1)
endif()



install(TARGETS PathingApp_v2
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)


# Pobierz flagi kompilacji i biblioteki z mysql_config
execute_process(COMMAND mysql_config --cflags OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

# Dodaj flagi kompilacji
add_compile_options(${MYSQL_CFLAGS})

# Podłącz biblioteki
target_link_libraries(PathingApp_v2 PRIVATE ${MYSQL_LIBS})

target_link_libraries(PathingApp_v2 PRIVATE DrawFunctions ContactDB DestinationFunctions)

