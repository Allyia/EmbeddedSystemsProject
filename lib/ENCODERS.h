#ifndef ENCODERS_H
#define ENCODERS_H
#include "mbed.h"

class Encoder{
    private:
        InterruptIn channelA, channelB; // Interrupt input for channel A and B of motor
        int pulses, revolutions, pulses_per_rev, rps_index; // Variables for pulse count, revolutions, pulses per revolution and index of revolutions per second
        float RPS, wheel_diameter, calc_period; // Variables for revolutions per second, wheel diameter, calculation period
        Ticker t; // Ticker for periodic task
        float previous_rps[5]; // Array with size 5 to store previous RPS values for filtering

        /* Function to increase the pulse count.
         *
         * Main loop will be interrupted to execute increment function
         * whenever pulse is read from encoder.
         */
        void increment();

        /* Function to calculate number of revolutions per second.
         *
         * The encoder has 256 pulses per revolution. In accordance to the pulse
         * counts read per second, the function executes algorithm to derive 
         * revolutions per second.
         *
         * Main loop will be interrupted to execute calculateRPS function every
         * second with reference to ticker timer.
         */
        void calculateRPS();

    public:
        Encoder(PinName channel1, PinName channel2, int PPR, float wheel, float period);

        /* Function to get current pulse count.
         *
         * Called every second along with calculateRPS function.
         *
         * Returns: 0 if the callback is successfully added
         *          -1 if not 
         */
        int getPulses();

        /* Function to clear and reset pulse count.
         *
         * Called right after both getPulses function and calculateRPS function
         * are executed beofre next iteration in main loop to get latest speed.
         */ 
        void clearPulses();

        /* Function to clear and reset RPS value.
         *
         * Called along with clearPulses function before next iteration in 
         * main loop to get latest speed.
         */  
        void clearRPS();

        /* Function to get revolutions per second.
         *
         * Called in PID control algorithm to get current speed and then 
         * setting it to a desired speed.
         *
         * Returns: 0 if the callback is successfully added
         *          -1 if not 
         */
        float getRPS();

        /* Function to get distance in meters.
         *
         * Returns: 0 if the callback is successfully added
         *          -1 if not 
         */ 
        float getDistanceM();
};

#endif
