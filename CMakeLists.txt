cmake_minimum_required(VERSION 3.5)
include(C:/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(qt_xbox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets
)

find_package(ITK REQUIRED)
find_package(OpenCV CONFIG REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        icons.qrc
)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_subdirectory(test_lib)
add_subdirectory(qtest)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt_xbox
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt_xbox APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt_xbox SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt_xbox
            ${PROJECT_SOURCES}
        )
    endif()
endif()


set_target_properties(qt_xbox PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS qt_xbox
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt_xbox)
endif()
#--------------------ADD Library-----------------------------------
add_library(gamepad STATIC gamepad_thread.h gamepad_thread.cpp)
target_link_libraries(gamepad PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(gamepad PUBLIC Xinput.lib Xinput9_1_0.lib)

add_library(camera STATIC
videostream.h
videostream.cpp)
target_link_libraries(camera PUBLIC Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)


add_library(mainwindow STATIC mainwindow.cpp
mainwindow.h
mainwindow.ui
icons.qrc)
target_include_directories(mainwindow PUBLIC icons)
target_link_libraries(mainwindow PUBLIC ITKFFT ITKVTK ITKznz itksys)
target_link_libraries(mainwindow PUBLIC gamepad)
target_link_libraries(mainwindow PUBLIC camera)
target_link_libraries(mainwindow PUBLIC Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

add_library(record_lib STATIC record.h record.cpp)
target_include_directories(record_lib PUBLIC test_lib)
target_link_libraries(record_lib PUBLIC test_lib)
target_link_libraries(record_lib PUBLIC Qt${QT_VERSION_MAJOR}::Core)

#--------------------Link Library-----------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC mainwindow)
target_link_libraries(${PROJECT_NAME} PUBLIC test_lib)
target_link_libraries(${PROJECT_NAME} PUBLIC record_lib)
target_link_libraries(${PROJECT_NAME} PUBLIC camera)
target_link_libraries(${PROJECT_NAME} PUBLIC gamepad)
