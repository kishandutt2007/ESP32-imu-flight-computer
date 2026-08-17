#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "universalinclude.h"

//function to begin the bluetooth serial
void bluetooth_create();
//function to send data using bluetooth serial
void bluetooth_send(DataStruct imu_data);

#endif
