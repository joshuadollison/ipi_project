// FROM:
// https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide/all
// https://playground.arduino.cc/Learning/4051/
// https://www.aranacorp.com/en/using-a-multiplexer-with-arduino/
// https://www.youtube.com/watch?v=SfsIOQic6AM&ab_channel=AnasKuzechie

#include "photo.cpp"
#include <SoftwareSerial.h>

const byte RX_PIN = 12;//2;
const byte TX_PIN = 13;//3;

// Using software serial port, can speak digital port analog into serial port
SoftwareSerial BT(RX_PIN, TX_PIN);  //New object, receive foot 2, send foot 3
char val;  //Store received variables

#define S0 2
#define S1 3
#define S2 4

#define Z_IN A5

#define MOTOR_PWN 6
#define MOTOR_PWN_REV 9

const int PHOTO_000 = 0;
const int PHOTO_045 = 1;
const int PHOTO_090 = 2;
const int PHOTO_135 = 3;
const int PHOTO_180 = 4;
const int PHOTO_225 = 5;
const int PHOTO_270 = 6;
const int PHOTO_315 = 7;

const photo PHOT[] = {

  photo(PHOTO_000, 0, 0),
  photo(PHOTO_045, 45, 45),
  photo(PHOTO_090, 90, 90),
  photo(PHOTO_135, 135, 135),
  photo(PHOTO_180, 180, 180),
  photo(PHOTO_225, 225, -135),
  photo(PHOTO_270, 270, -90),
  photo(PHOTO_315, 315, -45)

};


const int PHOTOS[] = {
    PHOTO_000,
    PHOTO_045,
    PHOTO_090,
    PHOTO_135,
    PHOTO_180,
    PHOTO_225,
    PHOTO_270,
    PHOTO_315
};

int PHOTOS_LEN = sizeof(PHOTOS)/sizeof(int);

void print(String text) {
  Serial.print(text);
  BT.print(text);
}

void println(String text) {
  Serial.println(text);
  BT.println(text);
}

void setupMultiplexer() {

  // Set up the select pins as outputs:
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

  pinMode(Z_IN, INPUT); // Set up Z as an input
}

void setupMotorDriver() {

  pinMode(MOTOR_PWN, OUTPUT);
  analogWrite(MOTOR_PWN, 0);

  pinMode(MOTOR_PWN_REV, OUTPUT);
  analogWrite(MOTOR_PWN_REV, 0);
}

void setupBT() {

  BT.begin(9600);  //set baud rate
  delay(3000); //delay 5000ms
  BT.print("AT"); //Send AT.  
}

void setup() 
{

  Serial.begin(9600); // Initialize the serial port
  
  setupMultiplexer();
  setupMotorDriver();
  setupBT();
}

void printAllPinVals() {

  // Print the header:
  println("Y0\tY1\tY2\tY3\tY4\tY5\tY6\tY7");
  println("---\t---\t---\t---\t---\t---\t---\t---");

  int MAX = 7;
  // Loop through all eight pins.
  for (byte pin=0; pin<=MAX; pin++)
  {
    //selectMuxPin(pin); // Select one at a time
    //int inputValue = analogRead(Z_IN); // and read Z
    int inputValue = getMuxVal(pin);
    print(String(inputValue) + "\t");
    //delay(20);
  }
  Serial.println();

  //Serial.println(analogRead(A2));
  //Serial.println(analogRead(A3));

}


int getMuxVal(int pin) {
  selectMuxPinx(pin);
  return analogRead(Z_IN);
}

void selectMuxPinx(int chnl){/* function selectChannel */ 

    //// Select channel of the multiplexer 
    int A = bitRead(chnl,0); //Take first bit from binary value of i channel.
    int B = bitRead(chnl,1); //Take second bit from binary value of i channel.
    int C = bitRead(chnl,2); //Take third bit from value of i channel.

    //int A = chnl & 0x01;      // old version of setting the bits
    //int B = (chnl>>1) & 0x01;      // old version of setting the bits
    //int C = (chnl>>2) & 0x01;      // old version of setting the bits
    
    /*
    Serial.print(chnl);
    Serial.print(", ");
    Serial.print(A);
    Serial.print(", ");
    Serial.print(B);
    Serial.print(", ");
    Serial.println(C);
    */
    digitalWrite(S0, A);
    digitalWrite(S1, B);
    digitalWrite(S2, C);
}


int getBrightest() {

    int analogValue, largest = 0, brightest = -1;
  
    for(int curr = 0; curr < PHOTOS_LEN; curr++) {

        //selectMuxPin(PHOTOS[curr]);
        //analogValue = analogRead(Z_IN);
        analogValue = getMuxVal(PHOTOS[curr]);

        /*
        Serial.print("Pin");
        Serial.print(PHOTOS[curr]);
        Serial.print(" : ");
        Serial.println(analogValue);
        */

        if(analogValue > largest) {
            largest = analogValue;
            brightest = PHOTOS[curr];
        }
    }

    return brightest;
}


int curr_dir = MOTOR_PWN;

void loop()
{
  
  int on = (curr_dir == MOTOR_PWN) ? MOTOR_PWN_REV : MOTOR_PWN;
  int off = (curr_dir == MOTOR_PWN) ? MOTOR_PWN : MOTOR_PWN_REV;
  
  curr_dir = on;
  print("ON: ");
  print(String(on));
  print(" OFF: "); 
  println(String(off));

  digitalWrite(on, HIGH);
  digitalWrite(off, LOW);

  delay(2000);
  
  digitalWrite(on, LOW);
  
  delay(1000);
}

void loopx() 
{
  
  int brightest = getBrightest();
  println(String(brightest));

  // /*
  if (brightest == 0) {
    analogWrite(MOTOR_PWN, 0);
    analogWrite(MOTOR_PWN_REV, 0);
  }
  else if(brightest == 2 || brightest == 6) {
      analogWrite(MOTOR_PWN, 0);
      analogWrite(MOTOR_PWN_REV, 255);
  }
  else {
    analogWrite(MOTOR_PWN, 255);
    analogWrite(MOTOR_PWN_REV, 0);
  }
  
  //printAllPinVals();
  delay(1000); 
}