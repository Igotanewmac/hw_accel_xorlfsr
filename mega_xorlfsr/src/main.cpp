#include <Arduino.h>



#include <tanglib.h>


//seeddata 86
#define SEEDDATA CONTROL_0
//seedset 79
#define SEEDSET CONTROL_1
//streamdata 27
#define STREAMDATA CONTROL_2




uint8_t secretkey[16] = { 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };


#define TEXTLENGTH 7168

uint8_t ciphertext[TEXTLENGTH];



// put function declarations here:


void printhex( uint8_t bytetoprint ) {
  if ( bytetoprint < 0x10 ) { Serial.print("0"); }
  Serial.print( bytetoprint , HEX );
}



long mytimestamp = 0;

void starttimer() {
  Serial.println("Timer Started.");
  mytimestamp = millis();
}

void stoptimer() {
  mytimestamp -= millis();
  Serial.print("Time Elapsed: ");
  Serial.println(abs(mytimestamp));
}




void setup() {
  // put your setup code here, to run once:
  tang_setup();

  Serial.begin(9600);
  Serial.println("Started up!");

  Serial.print( "Text Sample Length: " );
  Serial.println( TEXTLENGTH );

  randomSeed(analogRead(0));

}





void loop() {
  // put your main code here, to run repeatedly:

  // generate a new random key
  starttimer();
  Serial.print("Key: ");
  for ( uint8_t i = 0 ; i < 15 ; i++ ) {
    secretkey[i] = (uint8_t)random(0,256);
    printhex(secretkey[i]);
    Serial.print(":");
  }
  secretkey[15] = (uint8_t)random(0,256);
  printhex(secretkey[15]);
  Serial.println();
  stoptimer();




  starttimer();
  Serial.println("Encrypting.");
  // clock in 128 bits of key
  digitalWrite( SEEDDATA , HIGH );
  for ( uint8_t i = 0 ; i < 16 ; i++ ) {
    tang_clockbytein( secretkey[i] );
  }
  digitalWrite( SEEDDATA , LOW );
  
  // set the seed as active
  digitalWrite( SEEDSET , HIGH );
  tang_clockpulse();
  digitalWrite( SEEDSET , LOW );
  
  // push the first one through
  digitalWrite( STREAMDATA , HIGH );
  tang_clockbytein(0x00);
  digitalWrite( STREAMDATA , LOW );

  // now encode some data
  digitalWrite( STREAMDATA , HIGH );
  for ( uint16_t i = 0 ; i < TEXTLENGTH ; i++ ) {
    ciphertext[i] = tang_clockbytethrough( (uint8_t)i );
  }
  digitalWrite( STREAMDATA , LOW );

  stoptimer();


  starttimer();
  // now go back the other way
  Serial.println("Decrypting.");
  // clock in 128 bits of key
  digitalWrite( SEEDDATA , HIGH );
  for ( uint8_t i = 0 ; i < 16 ; i++ ) {
    tang_clockbytein( secretkey[i] );
  }
  digitalWrite( SEEDDATA , LOW );
  
  // set the seed as active
  digitalWrite( SEEDSET , HIGH );
  tang_clockpulse();
  digitalWrite( SEEDSET , LOW );
  
  // push the first one through
  digitalWrite( STREAMDATA , HIGH );
  tang_clockbytein(0x00);
  digitalWrite( STREAMDATA , LOW );

  // now encode some data
  digitalWrite( STREAMDATA , HIGH );
  for ( uint16_t i = 0 ; i < TEXTLENGTH ; i++ ) {
    if ( tang_clockbytethrough(ciphertext[i]) != (uint8_t)i ) {
      Serial.println(i);
    }
  }
  digitalWrite( STREAMDATA , LOW );

  stoptimer();
  


  
  Serial.println("Done!");
  
  
  



  while(1);
  //delay(10000);


}



// put function definitions here:




