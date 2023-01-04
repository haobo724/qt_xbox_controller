find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(test_lib STATIC test.h test.cpp)
target_link_libraries(test_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
