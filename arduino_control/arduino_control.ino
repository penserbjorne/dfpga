#include <Arduino.h>

/* 
 *  Basado en el codigo "shiftOutCode, Hello World" de Carlyn Maw y 
 *  Tom Igoe como ejemplo en el sitio oficial de Arduino.
*/


int dataPin = 9;    // Serial Data,  MOSI
int clockPin = 10;  // Clock para el serial,  SCK[1]
int latchPin = 11;  // Clock general,  LOAD[2]
int dCLK = 12;      // Clock para la salida paralela de los FF,   DCLK[3]
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
    dataArray[3] = 0xff;  // IC1
    dataArray[2] = 0xff;  // IC9
    dataArray[1] = 0x00;  // IC11
    dataArray[0] = 0x74;  // IC12

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
        // menos significativo
        shiftO(dataPin, clockPin, LSBFIRST, data);
        // Regresamos a alto el latch del registro dado que ya no esta 
        // escuchando
        digitalWrite(latchPin, HIGH);
        // Delay para dar tiempo de respuesta al circuito
        delay(250);
    }
    
    // Indicamos que la carga en fora serial se despliegue en 
    // forma parelara
    digitalWrite(latchPin, HIGH);
    delay(250);
    digitalWrite(latchPin, LOW);
    // Desactivamos la limpieza de los FF
    digitalWrite(clrFF, LOW);
    // Ponemos el reloj en cero
    digitalWrite(dCLK, LOW);
}

void loop() {
    // Switcheamos el bit del reloj
    digitalWrite(dCLK, HIGH);
    delay(250);
    digitalWrite(dCLK, LOW);
    delay(250);
}

void shiftO(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;
    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));
        digitalWrite(clockPin, HIGH);
        delay(250);
        digitalWrite(clockPin, LOW);
        delay(250);
    }
}
