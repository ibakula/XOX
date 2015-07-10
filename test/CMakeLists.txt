cmake_minimum_required(VERSION 2.8.4)
project(test CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${PROJCET_SOURCE_DIR}
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

add_executable(test-server
	opcode.cpp
	tcpconnection.cpp
	Test.cpp
	packet.cpp
	game.cpp
)

target_link_libraries(test-server ${Boost_LIBRARIES})
