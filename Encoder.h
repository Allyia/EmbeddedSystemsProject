#include "mbed.h"

// Define constants
// Adjust values
#define WHEEL_DIAMETER_MM 50.0     // Wheel diameter in millimeters
#define GEAR_RATIO 10              // Gear ratio
#define CPR 256                    // Counts per revolution of the encoder
#define WHEELBASE_WIDTH_MM 100.0   // Wheelbase width in millimeters

// Define encoder pins
InterruptIn encoderA(D2);  // Encoder channel A
InterruptIn encoderB(D3);  // Encoder channel B

// Define timer for velocity calculation
Timer timer;

// Variables to store previous encoder tick counts
int prevEncoderTicksA = 0;
int prevEncoderTicksB = 0;

// Initialize encoder variables
int encoderTicksA = 0;
int encoderTicksB = 0;

// Initialize variables for velocity calculation
float sampleTimeSeconds = 0.0;
float wheelVelocityRight = 0.0;
float wheelVelocityLeft = 0.0;
float robotTranslationalVelocity = 0.0;
float robotAngularVelocity = 0.0;

// Interrupt service routine for encoder channel A
void encoderISR_A() {
    if (encoderB) {
        encoderTicksA++;
    } else {
        encoderTicksA--;
    }
}

// Interrupt service routine for encoder channel B
void encoderISR_B() {
    if (encoderA) {
        encoderTicksB--;
    } else {
        encoderTicksB++;
    }
}

int main() {
    while(1) {
        
        // Start timer
        timer.start();

        // Attach interrupt handlers to encoder channels
        encoderA.rise(&encoderISR_A);
        encoderA.fall(&encoderISR_A);
        encoderB.rise(&encoderISR_B);
        encoderB.fall(&encoderISR_B);

        // Read ticks and reset timer
        // Calculate encoder tick rates
        int deltaTicksA = encoderTicksA - prevEncoderTicksA;
        int deltaTicksB = encoderTicksB - prevEncoderTicksB;

        sampleTimeSeconds = timer.read();

        // Reset timer
        timer.reset();

        // Update previous encoder tick counts
        prevEncoderTicksA = encoderTicksA;
        prevEncoderTicksB = encoderTicksB;

        // Calculate wheel velocities
        wheelVelocityRight = deltaTicksA / (CPR * sampleTimeSeconds * GEAR_RATIO);
        wheelVelocityLeft = deltaTicksB / (CPR * sampleTimeSeconds * GEAR_RATIO);

        // Calculate translational velocity
        robotTranslationalVelocity = (wheelVelocityRight + wheelVelocityLeft) / 2.0;

        // Calculate angular velocity
        robotAngularVelocity = (wheelVelocityRight - wheelVelocityLeft) / WHEELBASE_WIDTH_MM;

        // Wait for next sample
        wait(0.1);
    }
}
