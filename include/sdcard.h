#ifndef SDCARD_H
#define SDCARD_H


#include <SD.h>
#include <SPI.h>
#include "imudata.h"
#include "universalinclude.h"

struct SDData{
    unsigned long time_ms;
    float rawx;
    float rawy;
    float rawz;
    float filtx;
    float filty;
    float filtz;
};

//function used to setup the sd card intitially
void sd_setup();

//function to create the data struct to append to sd card
SDData sd_data_create(DataStruct raw_data, DataStruct filtered_data, unsigned long time_ms);

//function used to append the imu data into the csv file in the sd card
void sd_append(SDData new_data);


#endif 