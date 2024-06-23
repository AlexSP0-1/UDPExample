find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(HEADERS
    commandlineparser/commandlineoptions.h
    commandlineparser/commandlineparser.h

    udpclientexample.h
)

set(SOURCES
    main.cpp
    udpclientexample.cpp

    commandlineparser/commandlineparser.cpp
)

add_udp_example_executable(udp_ex_client ${SOURCES} ${HEADERS})

target_link_libraries(udp_ex_client Qt::Core Qt::Network udpexamplemess)
