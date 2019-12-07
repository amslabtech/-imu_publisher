# imu_publisher - IMUのデータをpublishする（RPI専用）

※このプログラムは，RPI SenseHAT を搭載したRPIでのみ動作します．

送信されるデータパケットは，imu_structure.hpp で規定されます．

```
//
//
//
#ifndef _DATA_STRUCTURE_HPP_
#define _DATA_STRUCTURE_HPP_

#include <iostream>
#include <iomanip>
#include <time.h>
#include <sys/time.h>

struct ImuStructure {
	int32_t id;
	struct timeval ts;
	float  x [3];	// orientation (roll, pitch, yaw)
	float  gx[3];	// gyros
	float  ax[3];	// accelarations
	float  mx[3];	// magnetometers

	void print() {
		std::cout
		<< std::setw( 6) << id
		<< std::setw(12) << ts.tv_sec
		<< std::setw( 7) << ts.tv_usec
		<< std::setw( 7) << x [0]
		<< std::setw( 7) << x [1]
		<< std::setw( 7) << x [2]
		<< std::setw( 7) << gx[0]
		<< std::setw( 7) << gx[1]
		<< std::setw( 7) << gx[2]
		<< std::setw( 7) << ax[0]
		<< std::setw( 7) << ax[1]
		<< std::setw( 7) << ax[2]
		<< std::endl;
	}
};


namespace imu {

	const char* topic		= "imu";
	const char* password	= "ccv";

};

#endif	// _DATA_STRUCTURE_HPP_
```
