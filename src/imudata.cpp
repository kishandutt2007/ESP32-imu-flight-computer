#include "imudata.h"
#include "universalinclude.h"
#include <MPU9250_asukiaaa.h>
#include <Wire.h>

MPU9250_asukiaaa imu;

int sda_pin = 21;
int scl_pin = 22;

//function used to setup the pins and serial communication with the imu
void imu_setup(){
    //setting the sda and scl pin for I2C communication
    Wire.begin(sda_pin, scl_pin);
    //starting serial communication and setting baud rate (9600)
    Serial.begin(9600);
    //starting wire for I2C communication
    imu.setWire(&Wire);
    //starting the acceleration readings on the imu
    imu.beginAccel();
    
    Serial.println("The IMU has been set up succesfully");
}

//function to updaate the accelerometer readings, store them into variables and print them into- 
//serial monitor
void imu_accel_print(){
    //to update the acceleration values from the imu
    imu.accelUpdate();

    //taking new accelerometer readings in x,y and z from imu
    float ax = imu.accelX();
    float ay = imu.accelY();
    float az = imu.accelZ();

    //printing the accelerometer values into serial monitor
    Serial.print("ax:");
    Serial.print(ax);
    Serial.print("ay:");
    Serial.print(ay);
    Serial.print("az:");
    Serial.println(az);
}

DataStruct imu_accel_read(){
    //making an instance of the struct
    DataStruct new_data;

    //updating the struct with the new acceleration values
    new_data.x = imu.accelX();
    new_data.y = imu.accelY();
    new_data.z = imu.accelZ();

    return new_data;
}