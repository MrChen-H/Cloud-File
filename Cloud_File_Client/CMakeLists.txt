cmake_minimum_required(VERSION 3.16)

project(Cloud_File_Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)
set(CMAKE_CXX_STANDARD 20)


qt_add_executable(appCloud_File_Client
    main.cpp
)

qt_add_qml_module(appCloud_File_Client
    URI Cloud_File_Client
    VERSION 1.0
    QML_FILES AppMainWindow.qml
    QML_FILES Main.qml
    QML_FILES Page/AccountPage.qml
    QML_FILES global/ItemsFooter.qml
    QML_FILES global/qmldir
    QML_FILES global/ItemsOriginal.qml
    QML_FILES Page/MyFile.qml
    QML_FILES Page/DownLoadStatePage.qml
    QML_FILES global/MyFileItems.qml
    QML_FILES Page/VideoPage.qml
    QML_FILES global/TransportItems.qml
    QML_FILES Page/AllFilePage.qml
    QML_FILES Page/PictureFilePage.qml
    QML_FILES Page/MusicFilePage.qml
    QML_FILES Page/HomePage.qml
    QML_FILES Page/TransportPage.qml
    QML_FILES
    SOURCES Model/downloadstatemodel.h Model/downloadstatemodel.cpp
    RESOURCES font.qrc
    SOURCES Net_Work/threadloop.h Net_Work/threadloop.cpp
    SOURCES Model/allfilemodel.h Model/allfilemodel.cpp
    SOURCES Net_Work/networkoperation.h Net_Work/networkoperation.cpp
    SOURCES Work_Thread/downloadthread.h Work_Thread/downloadthread.cpp
    SOURCES global/globalstatus.h global/globalstatus.cpp
    SOURCES
    SOURCES Model/uploadfileinfomode.h Model/uploadfileinfomode.cpp
    QML_FILES Page/UpLoadStatusPage.qml
    SOURCES
    SOURCES SERVER_CONFIG/SERVER_URLS.h
    SOURCES SERVER_CONFIG/SERVER_CONFIG.h
    SOURCES Device/updatedevice.h Device/updatedevice.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCloud_File_Client PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCloud_File_Client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCloud_File_Client
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS appCloud_File_Client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

