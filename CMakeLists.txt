cmake_minimum_required(VERSION 3.20)
project(alppad)

#Qt and C++ standard setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable automatic processing of Qt files
set(CMAKE_AUTOMOC ON) # Q_OBJECT macros
set(CMAKE_AUTORCC ON) # resources.qrc
set(CMAKE_AUTOUIC ON) # .ui files

# required Qt components
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# all files
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        note.h
        notemanager.cpp
        notemanager.h
        noteslistwidget.cpp
        noteslistwidget.h
        noteslistwidget.ui
        notewidget.cpp
        notewidget.h
        renamedialog.cpp
        renamedialog.h
        renamedialog.ui
        resources.qrc
)

# tell the compiler to look for headers as well
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# exe
add_executable(alppad ${PROJECT_SOURCES})

# link the Qt widgets
target_link_libraries(alppad PRIVATE Qt6::Widgets)