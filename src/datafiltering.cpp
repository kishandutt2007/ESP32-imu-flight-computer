#include "datafiltering.h"
#include "universalinclude.h"

//struct instant that stores the filtered data
DataStruct filtered_data;
// filter coefficient
float alpha = 0.2;
// outlier cutoff value 
float max_change = 3.0;

//function to initialize the filter with the starting data
void filter_setup(DataStruct first_data){
    filtered_data = first_data;
}

//function to filter raw data
DataStruct filter_data(DataStruct new_data){
    //first checks whether the new data is an outlier
    if (abs(new_data.x - filtered_data.x) < max_change){
        // if not an outlier performs the EWMA filter
        filtered_data.x = (1 - alpha)*filtered_data.x + alpha*new_data.x;
    }

    if (abs(new_data.y - filtered_data.y) < max_change){
        filtered_data.y = (1 - alpha)*filtered_data.y + alpha*new_data.y;
    }

    if (abs(new_data.z - filtered_data.z) < max_change){
        filtered_data.z = (1 - alpha)*filtered_data.z + alpha*new_data.z;
    }

    // returns the filtered data in a struct
    return filtered_data;
}