#ifndef PID_H
#define PID_H

#include <mbed.h>

class PIDController {
private:
    double prop_const;       // Proportional gain constant
    double int_const;        // Integral gain constant
    double deriv_const;      // Derivative gain constant
    double dt;               // Time interval between sensor polls
    double previous_error;   // Error at the previous time step (for derivative term)
    double error;            // Current error
    double integral_sum;     // Accumulated integral of the error

public:
    PIDController(double prop, double integ, double deriv, double dt);

    /* Function to set proportional gain.
     *
     * Used in PID control algorithm. The proportional term is proportional 
     * to the current error signal. It provides an immediate response to 
     * the current error.
     *
     *  @value => Double value assigned to Proportional Gain.
     *
     */
    void setP(double value);  

    /* Function to set the integral gain.
     *
     * Used in PID control algorithm. The integral term is proportional to 
     * both the magnitude and the duration of the error. It accumulates the
     * error over time and acts to eliminate steady-state errors.
     *
     *  @value => Double value assigned to Integral Gain.
     *
     */
    void setI(double value);  

    /* Function to set the derivative gain.
     *
     * Used in PID control algorithm. The derivative term is proportional to 
     * the rate of change of the error. It predicts future behavior of the 
     * error based on its current rate of change. It provides damping or 
     * stabilizing effect by anticipating future trends in the error and 
     * counteracting them.
     *
     *  @value => Double value assigned to Derivative Gain.
     *
     */
    void setD(double value); 

    /* Function to reset and clear integral sum and previous error.
     */
    void reset();

    /* Function to calculate PID control output
     *
     * Takes current speed and desired setpoint as input in accordance to
     * each of the P, I and D terms to compute the control signal that drives
     * the system towards the desired speed without any unwanted fluctuations
     * that may result in inaccurate navigation of the buggy.
     *
     *  @current_val => Double value of current speed.
     *  @desired_val => Double value of desired speed.
     *
     *  Returns: 0 if the callback is successfully removed
     *          -1 if not
     */
    double calculate(double current_val, double desired_val);
};

#endif
