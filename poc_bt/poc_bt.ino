/*
 Name:    Bluetooth.ino
 Created: 2016/7/30 13:26:47
 Author:  Fing
HC-06  arduino
VCC---> 5V
GND--->GND
TXD--->D2
RXD--->D3
*/

/*
https://docs.arduino.cc/learn/built-in-libraries/software-serial
https://wds-service-1258344699.file.myqcloud.com/20/12636/pdf/1694067402916eed7c34c55e813358278626d7271051f.pdf
https://docs.qq.com/doc/DUEVrZVhwbWZQdXNm

*/
#include <SoftwareSerial.h>

const byte RX_PIN = 12;//2;
const byte TX_PIN = 13;//3;


// Using software serial port, can speak digital port analog into serial port
SoftwareSerial BT(RX_PIN, TX_PIN);  //New object, receive foot 2, send foot 3
char val;  //Store received variables
 
void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);   //Serial Port Connection with Computer
  Serial.println("BT Module is ready!");
  BT.begin(9600);  //set baud rate
  delay(3000); //delay 5000ms
  BT.print("AT"); //Send AT.
}
 
void loop() {
  //If the serial port receives the data, it outputs it to the Bluetooth serial port.
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  //If the Bluetooth module data is received, it is output to the screen.
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
    
    if (val=='1')
    {
     digitalWrite(LED_BUILTIN, HIGH);
    
    }
    else if (val=='0')
    {
     digitalWrite(LED_BUILTIN, LOW); 
     
    } 
    
  }
}
