cmake_minimum_required(VERSION 3.31)
project(UDP_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Network
        REQUIRED)
qt5_wrap_cpp(MAIN_MOC main.cpp)
add_executable(UDP_test main.cpp  UdpClientWorker.h
        Receiver.h
        Sender.h
        Receiver.cpp
        Test.h)
target_link_libraries(UDP_test
        Qt5::Core
        Qt5::Network
)

