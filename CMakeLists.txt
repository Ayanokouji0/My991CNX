cmake_minimum_required(VERSION 3.5)

project(My991CNX VERSION 0.1 LANGUAGES CXX)
file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QRC_SOURCE_FILES resources.qrc)

set(CMAKE_PREFIX_PATH "D:/Qt/6.5.1/msvc2019_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network SvgWidgets WebEngineWidgets Gui)

qt6_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        TexSvg.cpp
        MJaxAdaptor.cpp
        exptree.cpp
        dialog_intro.cpp
        #EvalPopUpWidget.cpp
        mainwindow.h
        TexSvg.h
        MJaxAdaptor.h
        exptree.h
        dialog_intro.h
        #EvalPopUpWidget.h
        mainwindow.ui
        dialog_intro.ui
        #EvalPopUpWidget.ui
        ${QRC_SOURCE_FILES}
        ${QRC_FILES}
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(My991CNX
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET My991CNX APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(My991CNX SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(My991CNX
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(My991CNX PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(My991CNX PRIVATE Qt6::Network Qt6::SvgWidgets Qt6::WebEngineWidgets Qt6::Gui)

set_target_properties(My991CNX PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS My991CNX
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(My991CNX)
endif()
