cmake_minimum_required(VERSION 3.16)

# 设置新策略解决 BOOST_ROOT 警告
cmake_policy(SET CMP0144 NEW)

# 设置vcpkg工具链
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(YumeChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost 配置
set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS filesystem system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost NOT found at ${BOOST_ROOT}. Check the path and library directory.")
endif()

# Qt 配置 - 添加Sql组件
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Network Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network Widgets Sql)

# jsoncpp 配置
find_package(jsoncpp CONFIG REQUIRED)

if(NOT jsoncpp_FOUND)
    message(FATAL_ERROR "jsoncpp NOT found. Ensure it's installed via vcpkg.")
else()
    message(STATUS "Found jsoncpp: ${jsoncpp_VERSION}")
    message(STATUS "jsoncpp targets: ${jsoncpp_TARGETS}")
endif()

# Protobuf 配置
find_package(Protobuf REQUIRED)
if(NOT Protobuf_FOUND)
    message(FATAL_ERROR "Protobuf NOT found. Ensure it's installed via vcpkg.")
endif()

# 添加 Qt 资源系统支持
qt_add_resources(YumeChat_RESOURCES
        "Resource.qrc"
)

# 源文件列表 - 添加SQLite相关的源文件
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h
        src/ui/login/login_dialog.cpp src/ui/login/login_dialog.h
        src/ui/Register/registerdialog.cpp src/ui/Register/registerdialog.h
        temple/Singleton/Singleton.cpp temple/Singleton/Singleton.h
        src/logic/HttpMgr/HttpMgr.cpp src/logic/HttpMgr/HttpMgr.h
        src/logic/Global/global.h
        src/logic/TcpMgr/TcpMgr.cpp
        src/logic/TcpMgr/TcpMgr.h
        Message.pb.cc
        Message.pb.h
        src/ui/Custom/YumeLineEdit.cpp
        src/ui/Custom/YumeLineEdit.h
        src/ui/Custom/YumeButton.cpp
        src/ui/Custom/YumeButton.h
        src/ui/Custom/YumeLabel.cpp
        src/ui/Custom/YumeLabel.h
        src/logic/Global/global.cpp
        src/ui/Custom/YumeTitleBar.cpp
        src/ui/Custom/YumeTitleBar.h
        src/ui/login/ui_login.h
        framelessmainwindow.h
        framelessmainwindow.cpp
        yumewindow.cpp
        yumewindow.h
        src/ui/Widgets/toolwidget.cpp
        src/ui/Widgets/toolwidget.h
        src/ui/Widgets/messagewidget.h
        src/ui/Widgets/messagewidget.cpp
        src/ui/Widgets/messagelist.cpp
        src/ui/Widgets/messagelist.h
        src/ui/Custom/SmoothListWidget.cpp
        src/ui/Custom/SmoothListWidget.h
        src/ui/Custom/SmoothScrollBar.cpp
        src/ui/Custom/SmoothScrollBar.h
        src/ui/Register/yume_ui_reg.h
        src/ui/Custom/CircleAvatar.cpp
        src/ui/Custom/CircleAvatar.h
        src/ui/Custom/YumeBubble.cpp
        src/ui/Custom/YumeBubble.h
        src/ui/Widgets/MessageItem.cpp
        src/ui/Widgets/MessageItem.h
        src/ui/Widgets/ChatArea.cpp
        src/ui/Widgets/ChatArea.h
        src/ui/Widgets/MessagePage.cpp
        src/ui/Widgets/MessagePage.h
        src/ui/Custom/UnScrollTextEdit.cpp
        src/ui/Custom/UnScrollTextEdit.h
        src/ui/Widgets/ChatInput.cpp
        src/ui/Widgets/ChatInput.h
        src/ui/Widgets/FriendWidget.cpp
        src/ui/Widgets/FriendWidget.h
        src/ui/Widgets/FriendPage.cpp
        src/ui/Widgets/FriendPage.h
        src/ui/Widgets/FriendList.cpp
        src/ui/Widgets/FriendList.h
        src/logic/DatabaseMgr/DatabaseMgr.cpp
        src/logic/DatabaseMgr/DatabaseMgr.h
        src/ui/Widgets/ChatTop.cpp
        src/ui/Widgets/ChatTop.h

        src/ui/Widgets/SearchWidget.cpp
        src/ui/Widgets/SearchWidget.h

        src/logic/MessageMgr/MessageMgr.cpp
        src/logic/MessageMgr/MessageMgr.h

        src/ui/Widgets/ConversationWidget.cpp
        src/ui/Widgets/ConversationWidget.h
        src/logic/ListMgr/ListMgr.cpp
        src/logic/ListMgr/ListMgr.h
        src/ui/Add/SelectWindow.cpp
        src/ui/Add/SelectWindow.h
        src/ui/Add/SelectWindow.h
        src/ui/Widgets/SearchFriendWidget.cpp
        src/ui/Widgets/SearchFriendWidget.h
        framelesswidget.h
        framelesswidget.cpp
        framelessdialog.h
        framelessdialog.cpp
        framelesswidget.h
)

# 创建目标
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(YumeChat MANUAL_FINALIZATION ${PROJECT_SOURCES} ${YumeChat_RESOURCES})
else()
    add_executable(YumeChat ${PROJECT_SOURCES})
endif()

# 包含目录
target_include_directories(YumeChat PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/temple
        ${Protobuf_INCLUDE_DIRS}
)

# 链接库 - 添加Qt Sql模块
target_link_libraries(YumeChat PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Sql  # 添加这一行
        ${Boost_LIBRARIES}
        JsonCpp::JsonCpp
)

# Protobuf 链接
if(TARGET protobuf::libprotobuf)
    message(STATUS "Found protobuf::libprotobuf")
    target_link_libraries(YumeChat PRIVATE protobuf::libprotobuf)
elseif(TARGET protobuf::libprotobufd)
    message(STATUS "Found protobuf::libprotobufd")
    target_link_libraries(YumeChat PRIVATE protobuf::libprotobufd)
elseif(TARGET protobuf::protobuf)
    message(STATUS "Found protobuf::protobuf")
    target_link_libraries(YumeChat PRIVATE protobuf::protobuf)
else()
    message(STATUS "Using traditional protobuf linking")
    target_link_libraries(YumeChat PRIVATE ${Protobuf_LIBRARIES})
endif()

# 如果是 Qt6 需要手动完成最终化
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(YumeChat)
endif()