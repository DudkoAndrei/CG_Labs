cmake_minimum_required(VERSION 3.21)
project(Color_Converter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Color_Converter
        src/main.cpp
        src/ColorModels/cmyk.cpp
        src/ColorModels/hsv.cpp
        src/ColorModels/rgb.cpp
        src/ColorModels/converter.cpp
        src/MainWindow/main_window.cpp
        src/ValueSelectorWidget/value_selector_widget.cpp
)

target_link_libraries(Color_Converter
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
