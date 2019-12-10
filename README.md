# imu_publisher - IMUのデータをpublishする（RPI専用）

※このプログラムは，RPI SenseHAT / Navio+ / Navio2 等 を搭載したRPIでのみ動作する．


## データパケットの送信速度（頻度）

IMUからデータが得られる速度（頻度）でPublishする．
速度はセンサおよびバスラインの速度によって異なり，

|  Board | BUS  |  Samplings/s  |    
|---  |---   |---    |
|  SenseHAT  | I2C |   80 packets/s 程度*  |    
|   Navio+   | SPI |  200 packets/s 以上出せる  |    

*この速度は RPI の計算能力に依るものではなく，SenseHATとの通信が I2C であることによる．



## Fusion

IMUのセンサ生値だけではなく，フィルタによるストラップダウン計算値も出力する．



## 送信されるデータパケットの内容

送信されるデータパケットは，以下の通り imu_structure.hpp で規定されます．
~~現状，RPIのカーネルが32bitであるため，struct timeval の互換性が保てない．
このため，RPIのカーネルが64bitになるまで timeval をデータパケットに含めないことにする．~~

```
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
	const char* ccv2_imu_addr = "192.168.0.172";
	const char* topic    = "imu";
	const char* password = "mqtt";
};
```


## 現状はpublishのみ

本来はsubscriberの口を設けていろいろな設定ができるようにしたい．
現状は，ハードコーディング．

