find_package(Qt5 REQUIRED COMPONENTS Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set (HEADERS
    udpexamplemessage.h
    udpexamplemessageparserinterface.h
    udpexamplesimplemessageparser.h
    udpexamplemessagecreator.h
)

set (SOURCES
    udpexamplesimplemessageparser.cpp
    udpexamplemessagecreator.cpp
)

ADD_LIBRARY(udpexamplemess STATIC ${SOURCES} ${HEADERS})
target_link_libraries(udpexamplemess PRIVATE Qt::Core)
