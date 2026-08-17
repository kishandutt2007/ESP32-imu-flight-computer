#ifndef DATAFILTERING_H
#define DATAFILTERING_H

#include "universalinclude.h"

//function to setup the filter with the initial data
void filter_setup(DataStruct first_data);
//function to filter raw data
DataStruct filter_data(DataStruct new_data);



#endif