#include <iostream>
#include <mbed.h>

class LineSensor {
private:
    AnalogIn sensor1;
    AnalogIn sensor2;
    AnalogIn sensor3;
    AnalogIn sensor4;
    DigitalOut enablePin1; // Pin connected to Darlington array for sensor 1
    DigitalOut enablePin2; // Pin connected to Darlington array for sensor 2
    DigitalOut enablePin3; // Pin connected to Darlington array for sensor 3
    DigitalOut enablePin4; // Pin connected to Darlington array for sensor 4
    Timer timer;
    int pollingInterval; // Interval for polling sensors
    double averageSensorValue1; // Member variable to store average sensor value 1
    double averageSensorValue2; // Member variable to store average sensor value 2
    double averageSensorValue3; // Member variable to store average sensor value 3
    double averageSensorValue4; // Member variable to store average sensor value 4


public:
    // Constructor to initialize sensors and enable pins
    LineSensor(PinName enablePin1, PinName enablePin2, PinName enablePin3, PinName enablePin4,
               PinName pin1, PinName pin2, PinName pin3, PinName pin4, int interval)
        : enablePin1(enablePin1), enablePin2(enablePin2), enablePin3(enablePin3), enablePin4(enablePin4),
          sensor1(pin1), sensor2(pin2), sensor3(pin3), sensor4(pin4), pollingInterval(interval) {}

    // Enable/disable sensor 1
    void enableSensor1() { enablePin1 = 1; }
    void disableSensor1() { enablePin1 = 0; }

    // Enable/disable sensor 2
    void enableSensor2() { enablePin2 = 1; }
    void disableSensor2() { enablePin2 = 0; }

    // Enable/disable sensor 3
    void enableSensor3() { enablePin3 = 1; }
    void disableSensor3() { enablePin3 = 0; }

    // Enable/disable sensor 4
    void enableSensor4() { enablePin4 = 1; }
    void disableSensor4() { enablePin4 = 0; }

    // Read values from sensors with sampling
    void readSensorValues(float samplingDuration) {
    Timer timer;
    timer.start();

    double sumSensorValue1 = 0.0;
    double sumSensorValue2 = 0.0;
    double sumSensorValue3 = 0.0;
    double sumSensorValue4 = 0.0;
    int numSamples = 0;

    // Sample sensor readings over the specified duration
    while (timer.read() < samplingDuration) {
        sumSensorValue1 += static_cast<double>(sensor1.read());
        sumSensorValue2 += static_cast<double>(sensor2.read());
        sumSensorValue3 += static_cast<double>(sensor3.read());
        sumSensorValue4 += static_cast<double>(sensor4.read());
        numSamples++;
    }

    // Calculate the average sensor values
    double averageSensorValue1 = sumSensorValue1 / numSamples;
    double averageSensorValue2 = sumSensorValue2 / numSamples;
    double averageSensorValue3 = sumSensorValue3 / numSamples;
    double averageSensorValue4 = sumSensorValue4 / numSamples;

    // Use average values for further processing  
    }

    // Toggle the enable/disable state of sensors 1/2 and 3/4
    void toggleSensors() {
        // Enable sensors 1 and 2, disable sensors 3 and 4
        enableSensor1();
        enableSensor2();
        disableSensor3();
        disableSensor4();
        wait_ms(pollingInterval);

        // Enable sensors 3 and 4, disable sensors 1 and 2
        enableSensor3();
        enableSensor4();
        disableSensor1();
        disableSensor2();
        wait_ms(pollingInterval);
    }

    // Determine the speed for turning based on sensor values (1st pair)
    void TurningSpeed1() {
    // Read sensor values
    double left1 = averageSensorValue1;
    double right1 = averageSensorValue2;

    // Calculate the difference between sensor readings
    double difference = left1 - right1;

    // Calculate the new motor speeds based on the difference
    // Positive difference means increase left motor speed
    // Negative difference means increase right motor speed
    if (difference > 0) {
    double desired_motor1 = encoder1.getRPS() + (difference * ADJUSTMENT_FACTOR);
    } else {
    double desired_motor2 = encoder2.getRPS() - (difference * ADJUSTMENT_FACTOR);
    }
}

    // Determine the speed for turning based on sensor values (2nd pair)
    void TurningSpeed2() {
    // Read sensor values
    double left2 = averageSensorValue3;
    double right2 = averageSensorValue4;

    // Calculate the difference between sensor readings
    double difference = left2 - right2;

    // Calculate the new motor speeds based on the difference
    // Positive difference means increase left motor speed
    // Negative difference means increase right motor speed
    if (difference > 0) {
    double desired_motor1 = encoder1.getRPS() + (difference * ADJUSTMENT_FACTOR);
    } else {
    double desired_motor2 = encoder2.getRPS() - (difference * ADJUSTMENT_FACTOR);
    }
}

};


int main() {
    // Define pin names for enable pins and each sensor   
    PinName pin1 = A0;
    PinName pin2 = A1;
    PinName pin3 = A2;
    PinName pin4 = A3;
    PinName enablePin1 = D2;
    PinName enablePin2 = D3;
    PinName enablePin3 = D4;
    PinName enablePin4 = D5;
    
    // Create a LineSensor with 4 sensors and enable pins and interval
    LineSensor lineSensor(enablePin1, enablePin2, enablePin3, enablePin4, pin1, pin2, pin3, pin4, 1);

    // Toggle sensor enables continuously while reading value and changing turning speed
    while (true) {
        // Simulate reading sensor values
        lineSensor.readSensorValues(0.1);
        
        if (enablePin1 == 1 && enablePin2 == 1) {
        lineSensor.TurningSpeed1();
        } else if (enablePin3 == 1 && enablePin4 == 1) {
        lineSensor.TurningSpeed2();
        } 
        
        lineSensor.toggleSensors();
    }

    return 0;
}


