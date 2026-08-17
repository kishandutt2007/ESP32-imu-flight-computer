#ifndef IMUDATA_H
#define IMUDATA_H

#include "Arduino.h"
#include "universalinclude.h"

//function used to setup the imu
void imu_setup();
//function used to take in accel data and print to serial monitor
void imu_accel_print();
//function used to update the struct with acceleration readings 
DataStruct imu_accel_read();

#endif