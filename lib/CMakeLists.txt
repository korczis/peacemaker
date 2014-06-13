cmake_minimum_required (VERSION 2.6)
project (peacemaker)

# The version number.
set(Peacemaker_VERSION_MAJOR 0)
set(Peacemaker_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../cmake/modules/")

set(${PROJECTNAME}_SOURCES
    Application/Application.cpp

    Engine/Capture.cpp
    Engine/Device.cpp
    Engine/Engine.cpp

    Helpers/Helpers.cpp

    Logger/Logger.cpp

    # peacemaker/main.cpp
)

add_definitions(
    -std=c++11
)

# add the executable
add_library(peacemaker SHARED ${${PROJECTNAME}_SOURCES})

# See http://gnuradio.org/redmine/projects/gnuradio/repository/revisions/71c0f14a46f85027b95f2f5f6d3d219cc9e3783e/diff/cmake/Modules/GrBoost.cmake
set(Boost_USE_STATIC_LIBS ${USE_STATIC_BOOST})
set(Boost_USE_MULTITHREADED ON)
unset(Boost_INCLUDE_DIR CACHE)
unset(Boost_LIBRARY_DIRS CACHE)

find_package(Boost COMPONENTS date_time log program_options signals system thread REQUIRED)

if(USE_STATIC_BOOST)
	message(STATUS "Linking against boost static libraries")
else(USE_STATIC_BOOST)
	message(STATUS "Linking against boost dynamic libraries")
	add_definitions(-DBOOST_ALL_DYN_LINK)
endif(USE_STATIC_BOOST)

target_link_libraries(peacemaker 
	${Boost_DATE_TIME_LIBRARY}
	${Boost_LOG_LIBRARY}
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	${Boost_SIGNALS_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_THREAD_LIBRARY}
)

# See https://github.com/bro/cmake
find_package(PCAP)

target_link_libraries(peacemaker
	${PCAP_LIBRARY}
)