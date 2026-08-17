#include "imudata.h"
#include "sdcard.h"
#include "bluetooth.h"
#include "datafiltering.h"
#include "universalinclude.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

void setup() {
  //function to initialize the imu
  imu_setup();
  //function to initialize the sd card
  sd_setup();
  //function to setup the filter function with initial data
  DataStruct first_data = imu_accel_read();
  filter_setup(first_data);
  //function to initiate bluetooth
  bluetooth_create();
}


void loop() {
  //function to print imu data to serial monitor
  imu_accel_print();
  // tome reading for sd card csv file 
  unsigned long time_ms = millis();
  //reading imu data and storing to a struct
  DataStruct new_data = imu_accel_read();
  //function to filter the raw acceleration data
  DataStruct filtered_data = filter_data(new_data);
  //function to set data in format for sd append function
  SDData sd_data = sd_data_create(new_data, filtered_data, time_ms);
  //function to append the imu data from struct to the sd card
  sd_append(sd_data);
  //function to send the data using bluetooth serial
  bluetooth_send(filtered_data);

  delay(20);
}
