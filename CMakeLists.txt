cmake_minimum_required(VERSION 3.16)

# 设置新策略解决 BOOST_ROOT 警告
cmake_policy(SET CMP0144 NEW)

# 设置vcpkg工具链
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(YumeChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost 配置
set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS ON)
set(BOOST_ROOT "D:/boost_1_88_0")
set(BOOST_INCLUDEDIR "D:/boost_1_88_0")
set(BOOST_LIBRARYDIR "D:/boost_1_88_0/lib64-msvc-14.3")  # 根据实际路径调整

find_package(Boost 1.88.0 REQUIRED COMPONENTS filesystem system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost NOT found at ${BOOST_ROOT}. Check the path and library directory.")
endif()

# Qt 配置
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Network Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Widgets)

# jsoncpp 配置
set(jsoncpp_DIR "D:/vcpkg/installed/x64-windows/share/jsoncpp")
find_package(jsoncpp CONFIG REQUIRED)

if(NOT jsoncpp_FOUND)
    message(FATAL_ERROR "jsoncpp NOT found. Ensure it's installed via vcpkg.")
endif()

# 源文件列表
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
        src/ui/login/login_dialog.cpp src/ui/login/login_dialog.h src/ui/login/login_dialog.ui
        src/ui/Register/registerdialog.cpp src/ui/Register/registerdialog.h src/ui/Register/registerdialog.ui
        temple/Singleton/Singleton.cpp temple/Singleton/Singleton.h
        src/logic/HttpMgr/HttpMgr.cpp src/logic/HttpMgr/HttpMgr.h
        src/logic/Global/global.h
)

# 创建目标
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(YumeChat MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(YumeChat ${PROJECT_SOURCES})
endif()

# 包含目录
target_include_directories(YumeChat PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/temple
)

# 链接库
target_link_libraries(YumeChat PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        ${Boost_LIBRARIES}
        jsoncpp_lib
)