#include <Arduino.h>

/* 
 *  Basado en el codigo "shiftOutCode, Hello World" de Carlyn Maw y 
 *  Tom Igoe como ejemplo en el sitio oficial de Arduino.
*/

int dataPin = 9;    // Serial Data,  MOSI
int clockPin = 10;  // Clock para el serial,  SCK[1]
int dCLK = 11;      //  Clock general,  DCLK[2]
int latchPin = 12;  // Clock para los FF,   LOAD[3]
int clrFF = 13;     // Limpia los FF,  RESET[4]
byte dataArray[4];  // Data Array
byte data;          // Byte holder

void setup() {
    // Indicamos los pines como salida
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clrFF, OUTPUT);
    pinMode(dCLK, OUTPUT);

    // Programa que se enviara al FPGA
    dataArray[0] = 0x00;
    dataArray[1] = 0xff;
    dataArray[2] = 0x1c;
    dataArray[3] = 0x76;

     // Limpiamos los FF (clear)
    digitalWrite(clrFF, HIGH);
    // Enviaremos cuatro bytes
    for (int j = 0; j < 4; j++) {
        // Recuperamos el byte a enviar
        data = dataArray[j];
        // Ponemos en bajo el latch del registro para que no elimine 
        // los datos que apenas esta cargando
        digitalWrite(latchPin, LOW);
        // Enviamos el datos de forma serial comenzando por el bit 
        // mas significativo
        shiftOut(dataPin, clockPin, MSBFIRST, j);
        // Regresamos a alto el latch del registro dado que ya no esta 
        // escuchando
        digitalWrite(latchPin, HIGH);
        // Delay para dar tiempo de respuesta al circuito
        delay(10);
    }
    // Desactivamos la limpieza de los FF
    digitalWrite(clrFF, LOW);
    // Ponemos el reloj en cero
    digitalWrite(dCLK, LOW);
}

void loop() {
    // Switcheamos el bit del reloj cada segundo
    digitalWrite(dCLK, HIGH);
    delay(1000);
    digitalWrite(dCLK, LOW);
    delay(1000);
}
