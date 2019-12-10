cmake_minimum_required(VERSION 2.8)
project(imu_publisher)

set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall")
set(MOSQUITTO_DIR "/home/pi/dev/MqttClass")

add_executable(imu_publisher src/imu_publisher.cpp)

target_include_directories(imu_publisher   
	PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	PUBLIC $<BUILD_INTERFACE:${MOSQUITTO_DIR}/include>
)

target_link_libraries(imu_publisher mosquitto RTIMULib)

INSTALL(
	TARGETS imu_publisher
	RUNTIME DESTINATION /usr/local/bin/
)

INSTALL(
	FILES include/imu_structure.hpp
	DESTINATION /usr/local/include/
)

