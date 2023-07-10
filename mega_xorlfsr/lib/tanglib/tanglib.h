

#ifndef TANGLIB_H
#define TANGLIB_H


#include <Arduino.h>





// tanglib header

#define DATAIN_0 22
#define DATAIN_1 24
#define DATAIN_2 26
#define DATAIN_3 28
#define DATAIN_4 30
#define DATAIN_5 32
#define DATAIN_6 34
#define DATAIN_7 36
#define DATAOUT_0 23
#define DATAOUT_1 25
#define DATAOUT_2 27
#define DATAOUT_3 29
#define DATAOUT_4 31
#define DATAOUT_5 33
#define DATAOUT_6 35
#define DATAOUT_7 37
// arduino 13 tang 49
#define DATACLK 13
// arduino 12 tang 86
#define CONTROL_0 12
// arduino 11 tang 79
#define CONTROL_1 11
// arduino 10 tang 27
#define CONTROL_2 10
// arduino 9 tang 77
#define CONTROL_3 9




// function declarations.

// setup function



/// @brief Set up the data bus pins as input and output.
void tang_setup();



// communication functions

/// @brief pulse the dataclk line
void tang_clockpulse();

/// @brief Send a byte to the tang, ignoring the response.
/// @param bytetosend an 8 bit byte to send.
void tang_clockbytein( uint8_t bytetosend );

/// @brief Receive a byte from the tang, without sending.
/// @return an 8 bit byte response.
uint8_t tang_clockbyteout();

/// @brief send and receive a byte through the tang, on a single cycle.
/// @param bytetosend an 8 bit byte to send.
/// @return an 8 bit byte response.
uint8_t tang_clockbytethrough( uint8_t bytetosend );
































































#endif

