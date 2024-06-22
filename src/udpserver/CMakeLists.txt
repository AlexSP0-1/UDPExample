find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(HEADERS

)

set(SOURCES
    main.cpp
)

add_udp_example_executable(udp_ex_server ${SOURCES} ${HEADERS})

target_link_libraries(udp_ex_server Qt5::Core)
