

#ifndef TANGLIB_C
#define TANGLIB_C


#include <Arduino.h>
#include <tanglib.h>


  


void tang_clockpulse() {
    digitalWrite( DATACLK , HIGH );
    digitalWrite( DATACLK , LOW );
}

 





/// @brief Set up the data bus pins as input and output.
void tang_setup() {
    pinMode( DATAIN_0 , OUTPUT );
    pinMode( DATAIN_1 , OUTPUT );
    pinMode( DATAIN_2 , OUTPUT );
    pinMode( DATAIN_3 , OUTPUT );
    pinMode( DATAIN_4 , OUTPUT );
    pinMode( DATAIN_5 , OUTPUT );
    pinMode( DATAIN_6 , OUTPUT );
    pinMode( DATAIN_7 , OUTPUT );
    pinMode( DATAOUT_0 , INPUT );
    pinMode( DATAOUT_1 , INPUT );
    pinMode( DATAOUT_2 , INPUT );
    pinMode( DATAOUT_3 , INPUT );
    pinMode( DATAOUT_4 , INPUT );
    pinMode( DATAOUT_5 , INPUT );
    pinMode( DATAOUT_6 , INPUT );
    pinMode( DATAOUT_7 , INPUT );
    pinMode( DATACLK , OUTPUT );
    digitalWrite( DATAIN_0 , LOW );
    digitalWrite( DATAIN_1 , LOW );
    digitalWrite( DATAIN_2 , LOW );
    digitalWrite( DATAIN_3 , LOW );
    digitalWrite( DATAIN_4 , LOW );
    digitalWrite( DATAIN_5 , LOW );
    digitalWrite( DATAIN_6 , LOW );
    digitalWrite( DATAIN_7 , LOW );
    digitalWrite( DATACLK , LOW );
    return;
}









/// @brief Send a byte to the tang, ignoring the response.
/// @param bytetosend an 8 bit byte to send.
void tang_clockbytein( uint8_t bytetosend ) {

    // set the byte on the input lines
    digitalWrite( DATAIN_0 , ( bytetosend & 0b00000001 ) ? HIGH : LOW );
    digitalWrite( DATAIN_1 , ( bytetosend & 0b00000010 ) ? HIGH : LOW );
    digitalWrite( DATAIN_2 , ( bytetosend & 0b00000100 ) ? HIGH : LOW );
    digitalWrite( DATAIN_3 , ( bytetosend & 0b00001000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_4 , ( bytetosend & 0b00010000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_5 , ( bytetosend & 0b00100000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_6 , ( bytetosend & 0b01000000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_7 , ( bytetosend & 0b10000000 ) ? HIGH : LOW );

    
    tang_clockpulse();

    return;
}






/// @brief Receive a byte from the tang, without sending.
/// @return an 8 bit byte response.
uint8_t tang_clockbyteout() {

    // pulse the clock
    tang_clockpulse();

    // read back in the data.
    uint8_t responsebyte = 0;

    responsebyte |= digitalRead( DATAOUT_0 );
    responsebyte |= digitalRead( DATAOUT_1 ) << 1;
    responsebyte |= digitalRead( DATAOUT_2 ) << 2;
    responsebyte |= digitalRead( DATAOUT_3 ) << 3;
    responsebyte |= digitalRead( DATAOUT_4 ) << 4;
    responsebyte |= digitalRead( DATAOUT_5 ) << 5;
    responsebyte |= digitalRead( DATAOUT_6 ) << 6;
    responsebyte |= digitalRead( DATAOUT_7 ) << 7;

    // and return it
    return responsebyte;

}









/// @brief send and receive a byte through the tang, on a single cycle.
/// @param bytetosend an 8 bit byte to send.
/// @return an 8 bit byte response.
uint8_t tang_clockbytethrough( uint8_t bytetosend ) {




    // set the byte on the input lines
    digitalWrite( DATAIN_0 , ( bytetosend & 0b00000001 ) ? HIGH : LOW );
    digitalWrite( DATAIN_1 , ( bytetosend & 0b00000010 ) ? HIGH : LOW );
    digitalWrite( DATAIN_2 , ( bytetosend & 0b00000100 ) ? HIGH : LOW );
    digitalWrite( DATAIN_3 , ( bytetosend & 0b00001000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_4 , ( bytetosend & 0b00010000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_5 , ( bytetosend & 0b00100000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_6 , ( bytetosend & 0b01000000 ) ? HIGH : LOW );
    digitalWrite( DATAIN_7 , ( bytetosend & 0b10000000 ) ? HIGH : LOW );

    tang_clockpulse();

    // read back in the data.
    uint8_t responsebyte = 0;

    responsebyte |= digitalRead( DATAOUT_0 );
    responsebyte |= digitalRead( DATAOUT_1 ) << 1;
    responsebyte |= digitalRead( DATAOUT_2 ) << 2;
    responsebyte |= digitalRead( DATAOUT_3 ) << 3;
    responsebyte |= digitalRead( DATAOUT_4 ) << 4;
    responsebyte |= digitalRead( DATAOUT_5 ) << 5;
    responsebyte |= digitalRead( DATAOUT_6 ) << 6;
    responsebyte |= digitalRead( DATAOUT_7 ) << 7;
    
    return responsebyte;

}










































































#endif


