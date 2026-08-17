#import statements for serial communication and graphing 
import serial 
import csv
import pyqtgraph as pq
from PyQt6.QtCore import QTimer
from PyQt6.QtWidgets import QApplication
import sys

#creating the csv file
data_file = open(
    "flight_data.csv", #name of the csv file created
    "w",               #opening the file in write mode 
    newline=""         #to remove extra blank spaces 
)

#to write to the data file 
csv_writer = csv.writer(data_file)
#writing the column headers
csv_writer.writerow(["filt ax", "filt ay", "filt az"])

#setting up global variables
baud_rate = 115200
com_port = "COM4"

#setting up bluetooth serial for data transfer
esp_bluetooth = serial.Serial(
    port = com_port,
    baudrate = baud_rate,
    timeout = 0.01,
)

#setting up graph
app = QApplication(sys.argv)
graph = pq.plot()

#setting titles and labels
graph.setWindowTitle("IMU DATA")
graph.setLabel("left", "acceleration")
graph.setLabel("bottom", "samples")
graph.addLegend()
graph.showGrid(x = True, y = True)

#plotting the individual lines and assigning the data arrays
ax_line = graph.plot(name = "Ax")
ax_data = []
ay_line = graph.plot(name = "Ay")
ay_data = []
az_line = graph.plot(name = "Az")
az_data = []

#function to save the filtered data from the bluetooth serial into the csv file
def save_data(ax, ay, az):
    #writing the data row by row
    csv_writer.writerow([ax, ay, az])
    #funciton to pish th edata from memory to the file
    data_file.flush()

#function to read the new imu data, break it down and return the data split into
#individual accelerations
def read_data():

    print("checking for data...")              # Confirms that QTimer is calling this function
 
    data = esp_bluetooth.readline()            # Read one line from Bluetooth

    print("raw data:", data)                   # Shows exactly what COM5 is receiving

    data = data.decode(
        "utf-8",
        errors="ignore"
    ).strip()

    if data == "":
        return None

    values = data.split(",")

    if len(values) != 4:
        print("bad packet:", values)
        return None

    if values[0] != "IMU :":
        return None

    ax = float(values[1])
    ay = float(values[2])
    az = float(values[3])

    return ax, ay, az

#function to take in new imu accelrations and update the graph
def update_graph():
    #reading new data into variablels
    imu_data = read_data()

    if imu_data is None:
        return None
    
    ax, ay, az = imu_data

    #saving data to csv file 
    save_data(ax, ay, az)

    #updating data arrays and graph lines
    ax_data.append(ax)
    ax_line.setData(ax_data)
    ay_data.append(ay)
    ay_line.setData(ay_data)
    az_data.append(az)
    az_line.setData(az_data)

#main code
timer = QTimer()
timer.timeout.connect(update_graph)
timer.start(20)
app.exec()
