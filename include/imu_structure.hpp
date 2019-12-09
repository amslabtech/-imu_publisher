//
//	imu_structure.hpp
//
#ifndef _IMU_STRUCTURE_HPP_
#define _IMU_STRUCTURE_HPP_

#include <iostream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>

struct ImuStructure {
	int32_t id;
	int32_t sec;
	int32_t usec;
	float  fusion [3];	// orientation (roll, pitch, yaw)
	float  gyro   [3];	// gyros
	float  accel  [3];	// accelarations
	float  compass[3];	// magnetometers

	void print9() {
		std::cout
		<< std::setw( 6) << id
//		<< std::setw(12) << ts.tv_sec
//		<< std::setw(10) << ts.tv_usec
		<< std::setw(12) << fusion [0]
		<< std::setw(12) << fusion [1]
		<< std::setw(12) << fusion [2]
		<< std::setw(12) << gyro   [0]
		<< std::setw(12) << gyro   [1]
		<< std::setw(12) << gyro   [2]
		<< std::setw(12) << accel  [0]
		<< std::setw(12) << accel  [1]
		<< std::setw(12) << accel  [2]
		<< std::endl;
	}

	void print3() {
		std::cout
		<< std::setw( 6) << id
		<< std::setw(16) << fusion [0]
		<< std::setw(16) << fusion [1]
		<< std::setw(16) << fusion [2]
		<< std::endl;
	}

	void diff_time(struct timeval ts) {
		double t1 =  sec+ usec/1000000.0;
		double t2 = ts.tv_sec+ts.tv_usec/1000000.0;
		std::cout << t2 - t1;
	}
};

namespace imu {
	const char* topic    = "imu";
	const char* password = "mqtt";
};




#endif	// _IMU_STRUCTURE_HPP_
