cmake_minimum_required(VERSION 3.28)
project(5chess)

set(VCPKG_ROOT "C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg") 
set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.2\\mingw_64")
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

set(CURL_DIR "C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg\\installed\\x64-mingw-dynamic\\share\\curl")
set(jsoncpp_DIR "C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg\\installed\\x64-mingw-dynamic\\share\\jsoncpp")
set(ZLIB_ROOT "C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg\\installed\\x64-mingw-dynamic\\")
set(cJSON_DIR "C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg\\installed\\x64-mingw-dynamic\\share\\cjson")
find_package(CURL CONFIG REQUIRED)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)
find_package(jsoncpp CONFIG REQUIRED)
find_package(cJSON CONFIG REQUIRED)

include_directories("C:\\Users\\likaijie\\.vcpkg-clion\\vcpkg\\installed\\x64-mingw-dynamic\\include")

add_executable(5chess main.cpp
        connectui.cpp
        board.cpp
        pvplocal.cpp
        resources.qrc
)
add_library(
        libcurl.dll
        Qt6Core.dll
        Qt6Gui.dll
        Qt6Widgets.dll
)


target_link_libraries(5chess
        Qt::Core
        Qt::Gui
        Qt::Widgets
        CURL::libcurl
        JsonCpp::JsonCpp
        cjson
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
