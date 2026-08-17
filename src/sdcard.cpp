#include <SD.h>
#include <SPI.h>
#include "universalinclude.h"
#include "sdcard.h"

int sd_cs = 4;
bool sd_ready = false;

void sd_setup(){
    delay(500);
    SPI.begin(18, 19, 23, 4);
    //checking to see if the sd card has been initialized
    for (int attempt = 1; attempt <= 5; attempt++){
        Serial.print("SD mount attempt");
        Serial.println(attempt);

        if (SD.begin(4, SPI, 1000000)){
            Serial.println("SD card has been initialized");
            sd_ready = true;
            break;
        }
        Serial.println("SD mount failed");
        delay(500);
    }

    // to print fail message if mounting failed after loop 
    if (!sd_ready){
        Serial.println("SD card mounting failed after 5 attempts");
        sd_ready = false;
        return;
    }
    
    //to remove csv file if it exists
    if (SD.exists("/imudata.csv")){
        SD.remove("/imudata.csv");
    }

    //creating a new file in the sd card called "imudata.csv" for the imu data
    File myfile = SD.open("/imudata.csv", FILE_WRITE);

    //checking to see if the csv file has been initialized
    if (!myfile){
        Serial.println("The csv file has failed to initialize");
        return;
    }

    myfile.println("time_ms, raw_ax, raw_ay, raw_az, filt_ax, filt_ay, filt_az");

    myfile.flush();

    myfile.close();
}

//function to bring together the raw and filtered imu data to append into the sd card file
SDData sd_data_create(DataStruct raw_data, DataStruct filtered_data, unsigned long time_ms){
    //creating struct
    SDData sd_data;

    //assigning the values to the struct
    sd_data.time_ms = time_ms;
    sd_data.rawx = raw_data.x;
    sd_data.rawy = raw_data.y;
    sd_data.rawz = raw_data.z;
    sd_data.filtx = filtered_data.x;
    sd_data.filty = filtered_data.y;
    sd_data.filtz = filtered_data.z;

    return sd_data;
}   

void sd_append(SDData sd_data){
    //reading imu data from the struct
    unsigned long time_ms = sd_data.time_ms;
    float rawx = sd_data.rawx;
    float rawy = sd_data.rawy;
    float rawz = sd_data.rawz;
    float filtx = sd_data.filtx;
    float filty = sd_data.filty;
    float filtz = sd_data.filtz;

    //opening the csv file in append mode 
    File myfile = SD.open("/imudata.csv", FILE_APPEND);

    if (!myfile){
        Serial.println("the sd card has failed to open in read mode");
        return;
    }

    //adding the imu data from the struct to the csv file 
    myfile.print(time_ms);
    myfile.print(", ");
    myfile.print(rawx);
    myfile.print(", ");
    myfile.print(rawy);
    myfile.print(", ");
    myfile.print(rawz);
    myfile.print(", ");
    myfile.print(filtx);
    myfile.print(", ");
    myfile.print(filty);
    myfile.print(", ");
    myfile.println(filtz);

    //closing the file after writing to it
    myfile.close();

}