cmake_minimum_required(VERSION 2.8.4)
project(client CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${PROJECT_SOURCE_DIR}
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

add_executable(test-client
	opcode.cpp
	tcpconnection.cpp
	main.cpp
	game.cpp
	../test/packet.cpp
)

target_link_libraries(test-client ${Boost_LIBRARIES})
