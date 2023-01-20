find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)
set(CMAKE_AUTOMOC ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories("../")
add_executable(tutorial1
    testqstring.h
    testqstring.cpp
)
set_target_properties(tutorial1 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(tutorial1 PUBLIC
    record_lib
    gamepad
    mainwindow
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Widgets
)

