cmake_minimum_required(VERSION 3.21) #cmake最低版本
project(QtProject-Monopoly) #工程名
set(CMAKE_CXX_STANDARD 17) #C++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# 查找QT的模块
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
# 添加源文件
add_executable(QtProject-Monopoly
        sources/eventwatcher.cpp
        sources/gameinitial.cpp
        sources/main.cpp
        sources/mainwindow.cpp
        sources/startmenu.cpp
        sources/stylizedbutton.cpp
        #
        headers/eventwatcher.h
        headers/gameinitial.h
        headers/mainwindow.h
        headers/startmenu.h
        headers/stylizedbutton.h
        #
        images.qrc
        sources/playersymbol.cpp
        headers/playersymbol.h
        sources/stylizedspinbox.cpp
        headers/stylizedspinbox.h
        sources/player.cpp
        headers/player.h
        sources/mainloop.cpp
        headers/mainloop.h
        headers/block.h
        sources/block.cpp
        headers/map.h
        sources/map.cpp
        )
# 添加模块
target_link_libraries(QtProject-Monopoly PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )
