#include <mbed.h>
#include <iostream>
#include <numeric>  // For std::accumulate

class PIDController {
private:
    double propConst;       // Proportional gain
    double intConst;        // Integral gain
    double derivConst;      // Derivative gain
    double speedVal;        // Base speed of the buggy
    double dt;              // Time between sensor polls
    double pastErrors[10];  // Array to store past errors
    size_t index;           // Index for the rolling array

public:
    PIDController(double prop_const, double int_const, double deriv_const, double speed_val, double dt)
        : propConst(prop_const), intConst(int_const), derivConst(deriv_const), speedVal(speed_val), dt(dt), index(0) {
        // Initialize past errors array to 0
        for (int i = 0; i < 10; ++i) {
            pastErrors[i] = 0.0;
        }
    }

    double calculate(double sensor1_val, double sensor2_val) {
        // Calculate error
        double error = sensor1_val - sensor2_val;

        // Update rolling array for past errors
        pastErrors[index] = error;
        index = (index + 1) % 10;  // Update index for rolling array

        // Proportional term
        double proportional_error = propConst * error;

        // Integral term
        double integral_error = intConst * 0.0; // Initialize to zero
        for (int i = 0; i < 10; ++i) {
            integral_error += pastErrors[i]; // After each iteration, sum up past errors
        }
        integral_error *= dt;

        // Derivative term
        double derivative_error = derivConst * (error - pastErrors[(index + 9) % 10]) / dt; 


        // Calculate control output
        double output_speed = speedVal + proportional_error + integral_error + derivative_error;

        return output_speed;
    }
};

int main() {
    PIDController pid(0.1, 0.01, 0.05, 0.0, 0.1);  // Initialize PID controller
    AnalogIn sensor1_pin(A0);  // Analog pin for sensor 1
    AnalogIn sensor2_pin(A1);  // Analog pin for sensor 2

        // Read sensor values
        double sensor1_val = sensor1_pin.read();
        double sensor2_val = sensor2_pin.read();

        // Calculate control output
        double control_output = pid.calculate(sensor1_val, sensor2_val);

    return 0;
}
