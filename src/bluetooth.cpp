#include <BluetoothSerial.h>
#include "bluetooth.h"
#include "imudata.h"
#include "universalinclude.h"

//instantiates the bluetooth serial
BluetoothSerial SerialBT;

//function to begin bluetooth serial
void bluetooth_create(){
    //begins the serial and names it 
    SerialBT.begin("ESP32_IMU");
}

void bluetooth_send(DataStruct imu_data){
    //sending the imu data through bluetooth serial to the laptop (ground station)
    SerialBT.print("IMU :");
    SerialBT.print(",");
    SerialBT.print(imu_data.x);
    SerialBT.print(",");
    SerialBT.print(imu_data.y);
    SerialBT.print(",");
    SerialBT.println(imu_data.z);
}



