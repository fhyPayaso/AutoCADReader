cmake_minimum_required(VERSION 3.17)
project(AutoCADReader)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME AutoCADReader)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#####################  配置QT #####################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

include_directories(D:/3rdlib/libdxfrw-0.6.3/src)
link_directories(D:/3rdlib/libdxfrw-0.6.3/vs2013/x64/Debug)

add_executable(AutoCADReader main.cpp MainWindow.cpp MainWindow.h ui_mainwindow.h
        libdxfrw/dx_data.h
        libdxfrw/dx_iface.h
        libdxfrw/dx_iface.cpp

        OpenGLWidget.cpp OpenGLWidget.h DwgObject.cpp DwgObject.h)

#####################  添加静态库 #####################
target_link_libraries(${PROJECT_NAME} Qt5::Core opengl32)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} libdxfrw)