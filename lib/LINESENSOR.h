#ifndef LINESENSOR_H
#define LINESENSOR_H
#include "mbed.h"

class LineSensor {
private:
    AnalogIn sensor1;                    // Analog input for sensor 1
    AnalogIn sensor2;                    // Analog input for sensor 2
    AnalogIn sensor3;                    // Analog input for sensor 3
    AnalogIn sensor4;                    // Analog input for sensor 4
    DigitalOut enablePin1;               // Pin connected to Darlington array for sensor 1
    DigitalOut enablePin2;               // Pin connected to Darlington array for sensor 2
    Timer timer;                         // Timer for sampling sensor values

    int lastcounts;                      // Counter for internal use

    double sensor1_values[5];            // Array to store recent sensor 1 readings
    int sensor1_index;                   // Index to track the position in the sensor 1 array
    double sensor2_values[5];            // Array to store recent sensor 2 readings
    int sensor2_index;                   // Index to track the position in the sensor 2 array
    double sensor3_values[5];            // Array to store recent sensor 3 readings
    int sensor3_index;                   // Index to track the position in the sensor 3 array
    double sensor4_values[20];           // Array to store recent sensor 4 readings
    int sensor4_index;                   // Index to track the position in the sensor 4 array

    double averageSensorValue1;          // Average value of sensor 1 readings
    double averageSensorValue2;          // Average value of sensor 2 readings
    double averageSensorValue3;          // Average value of sensor 3 readings
    double averageSensorValue4;          // Average value of sensor 4 readings

    double maxSensorAverage1;            // Maximum value for average sensor 1 readings
    double maxSensorAverage2;            // Maximum value for average sensor 2 readings
    double maxSensorAverage3;            // Maximum value for average sensor 3 readings
    double maxSensorAverage4;            // Maximum value for average sensor 4 readings

    // Adjust values as needed in lab
    const double sensor1Max = 1.0;       // Maximum value for sensor 1
    const double sensor1Min = 0.0;       // Minimum value for sensor 1
    
    const double sensor2Max = 1.0;       // Maximum value for sensor 2
    const double sensor2Min = 0.0;       // Minimum value for sensor 2

    const double sensor3Max = 1.0;       // Maximum value for sensor 3
    const double sensor3Min = 0.0;       // Minimum value for sensor 3

    const double sensor4Max = 1.0;       // Maximum value for sensor 4
    const double sensor4Min = 0.0;       // Minimum value for sensor 4
};
     /* Function to ensure sensor reading is within range of 0 to 1.
     *
     * Called after each average sensor value for every 5 readings taken.
     *
     * @sensorNum => Integer representing Sensors 1, 2, 3 or 4.
     *
     * Returns: 0 if the callback is successfully added
     *          -1 if not 
     */
    double normalize(int sensorNum);

public:
    LineSensor(PinName enablePin1, PinName enablePin2,
               PinName pin1, PinName pin2, PinName pin3, PinName pin4);

    /* Sets the enable pin associated with bank 1 (Sensors 1 and 2) to a logic
     * HIGH state, effectively enabling the sensors connected to this bank.
     * /
    void enableBank1();

    
    /* Sets the enable pin associated with bank 1 (Sensors 1 and 2) to a logic
     * LOW state, effectively disabling the sensors connected to this bank.
     * /
    void disableBank1();

    /* Sets the enable pin associated with bank 2 (Sensors 3 and 4) to a logic
     * HIGH state, effectively enabling the sensors connected to this bank.
     * /
    void enableBank2();

    /* Sets the enable pin associated with bank 2 (Sensors 3 and 4) to a logic
     * LOW state, effectively disabling the sensors connected to this bank.
     * /
    void disableBank2();

    /* Function to calculate average sensor reading.
     *
     * Called after every 5 sensor readings taken.
     *
     * This helps mitigate noise and fluctuations in the sensor data. Using 
     * the average value of sensor readings helps to improve the reliability,
     * stability and accuracy of the sensor data.
     *
     * @sensorNumber => Integer representing Sensors 1, 2, 3 or 4.
     *
     * Returns: 0 if the callback is successfully added
     *          -1 if not 
     */
    float getAverageSensorValue(int sensorNumber);

    /* Read 5 consecutive sensor values which are inserted into an array for
     * later calculation of average reading.
     *
     * @sensorNum => Integer representing Sensors 1, 2, 3 or 4.
     */
    void readSensorValues(int sensorNumber);
};

#endif
