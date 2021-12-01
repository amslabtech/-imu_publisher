//
//	ImuPublisher
//
//	... Y.Kuroda
//
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "mosquitto.hpp"		// c++ wrapper for mosquitto
#include "imu_structure.hpp"	// imu data types
#include "RTIMULib.h"			// imu library
using namespace imu;

int main()
{
	Mosquitto imu_publisher;

	const char* ip_addr  = "localhost";
	const char* username = "imu";
	struct timeval ts;


	RTIMUSettings* settings = new RTIMUSettings("RTIMULib");
	RTIMU* imu = RTIMU::createIMU(settings);
	if( (imu==NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
		std::cout << "No IMU found¥n";
		exit(1);
	}

	imu->IMUInit();
	imu->setSlerpPower(0.02);
	imu->setGyroEnable(true);
	imu->setAccelEnable(true);
	imu->setCompassEnable(true);


	imu_publisher.set_username_password(username,password);
	imu_publisher.connect(ip_addr);
	imu_publisher.subscribe(topic);

	std::cout << "\ndatasize = " << sizeof(ImuStructure) << " bytes\n";

	ImuStructure data;

	int i=0;
	while(1) {

		usleep(imu->IMUGetPollInterval() * 1000);

		while(imu->IMURead()) {
			RTIMU_DATA imudata = imu->getIMUData();

			gettimeofday(&ts, NULL);
			data = {
				i,
				ts.tv_sec,
				ts.tv_usec,
				imudata.fusionPose.x(),
				imudata.fusionPose.y(),
				imudata.fusionPose.z(),
				imudata.gyro.x(),
				imudata.gyro.y(),
				imudata.gyro.z(),
				imudata.accel.x(),
				imudata.accel.y(),
				imudata.accel.z(),
				imudata.compass.x(),
				imudata.compass.y(),
				imudata.compass.z(),
                imudata.fusionQPose.x(),
                imudata.fusionQPose.y(),
                imudata.fusionQPose.z(),
                imudata.fusionQPose.scalar(),
			};

#if 0
			std::cout	<< imudata.fusionPose.x() << ", "
						<< imudata.fusionPose.y() << ", "
						<< imudata.fusionPose.y() << ", "
						<< std::endl;
#endif

//			std::cout << RTMath::displayDegrees("", imudata.gyro) << std::endl;

			imu_publisher.publish(topic,(void*)&data,sizeof(data));
			//data.print3();
			i++;
		}
	}
	sleep(1);

	imu_publisher.cleanup_library();
}


