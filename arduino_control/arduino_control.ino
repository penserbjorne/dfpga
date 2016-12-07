#include <Arduino.h>
//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

////Pin connected to DS of 74HC595
int dataPin = 9;   // Serial Data,  MOSI

//Pin connected to SH_CP of 74HC595
int clockPin = 10;  // Clock para el serial,  SCK[1]

int dCLK = 11;   //  Clock general,  DCLK[2]

//Pin connected to ST_CP of 74HC595
int latchPin = 12;   // Clock para los FF,   LOAD[3]

int clrFF = 13;   // Limpia los FF,  RESET[4]

//Data Array
byte dataArray[4];
//Byte holder
byte data;

void setup() {
    //set pins to output because they are addressed in the main loop
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clrFF, OUTPUT);
    pinMode(dCLK, OUTPUT);

    //Toogler Program
    dataArray[0] = 0x00;
    dataArray[1] = 0xff;
    dataArray[2] = 0x1c;
    dataArray[3] = 0x76;

    digitalWrite(clrFF, HIGH);
    //count up routine
    for (int j = 0; j < 4; j++) {
        //ground latchPin and hold low for as long as you are transmitting
        data = dataArray[j];
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, j);
        //return the latch pin high to signal chip that it
        //no longer needs to listen for information
        digitalWrite(latchPin, HIGH);
        delay(10);
    }
    digitalWrite(clrFF, LOW);
    digitalWrite(dCLK, LOW);
}

void loop() {
    digitalWrite(dCLK, HIGH);
    delay(1000);
    digitalWrite(dCLK, LOW);
    delay(1000);
}
