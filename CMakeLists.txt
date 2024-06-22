cmake_minimum_required(VERSION 3.14)

project(UDPExample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_subdirectory(src)

#target_link_libraries(UDPExample Qt${QT_VERSION_MAJOR}::Core)

#install(TARGETS UDPExample
 #   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
