#---------------------------------------------------------------------------
set(CMAKE_BUILD_TYPE Release
    CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel.")
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Normally the source dir")

#---------------------------------------------------------------------------
project(project)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_DEBUG_POSTFIX  "d")
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

#---------------------------------------------------------------------------
set(exec windowWithImage)

#---------------------------------------------------------------------------
option(QT_STATIC "Use the Static Qt lib" OFF)

#---------------------------------------------------------------------------
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
set(QT_LIBRARIES
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::WinMain
    )

if (QT_STATIC)
    include (qtstatic.cmake)
endif()

#---------------------------------------------------------------------------
# windows needs even more stuff
if(WIN32)
    set(QT_LIBRARIES
        ${QT_LIBRARIES}
        imm32
        winmm
        ws2_32
        )
endif(WIN32)

#---------------------------------------------------------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    )

#---------------------------------------------------------------------------
set(sources
    src/main.cpp
    src/mainWindow.cpp
    resources.qrc
    )

set (headers
    include/borderLess.h
    include/windowWithImage.h
    include/titleBarWindow.h
    include/image.h
    include/mainWindow.h
    )

#---------------------------------------------------------------------------
add_executable(${exec} ${sources} ${headers})

#---------------------------------------------------------------------------
target_link_libraries(${exec}
    ${QT_LIBRARIES}
    )

#---------------------------------------------------------------------------
install(TARGETS ${exec}
    RUNTIME DESTINATION bin
)

