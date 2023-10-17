#define IR_USE_AVR_TIMER1

#include <IRremote.hpp> // include the library
#include "PinDefinitionsAndMore.h"

#define DECODE_NEC

const int BTN_IR_MIN = 0x44;
const int BTN_IR_MAX = 0x43;
const int BTN_IR_DWN = 0x7;
const int BTN_IR_UP = 0x9;

const int MOTOR_PWN = 3;

void setupIr() {
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    //IRrecvPCI.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    //IrReceiver.begin(35, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void setup() {

    // Start Serial Monitor                                                 
    Serial.begin(115200);

    pinMode(MOTOR_PWN, OUTPUT);
    digitalWrite(MOTOR_PWN, 0);

    setupIr();

}

const int STEP = 0;
int current_motor = 10;
//#define TESTING = 1


int last_thing = 0;

void loop() {

    #if defined(TESTING)

    current_motor += 50;
    if(current_motor > 255)
        current_motor = 0;

    analogWrite(MOTOR_PWN, current_motor);

    Serial.print("Curr V:");
    Serial.println(current_motor);

    delay(500);
    return;

    #endif

    int button = readInfrared();

    switch(button) {
        case BTN_IR_MIN:
            current_motor = 0;
            last_thing = 0;
            break;

        case BTN_IR_UP:
            current_motor += STEP;
            last_thing = 0;
            break;

        case BTN_IR_DWN:
            current_motor -= STEP;
            last_thing = 0;
            break;
        
        case BTN_IR_MAX:
            current_motor = 255;
            last_thing = 0;
            break;

        default:
            last_thing++;

            Serial.print("NADA: ");
            Serial.println(last_thing);
            
            break;
    }

    if(last_thing >= 20) {
        current_motor = 0;
        last_thing = 0;
        Serial.println("RESETTING FOR LACK OF ACTIVITY");
    }

    if(current_motor < 0)
        current_motor = 0;
    else if(current_motor > 255)
        current_motor = 255;

    //analogWrite(MOTOR_PIN_1, 120);
    analogWrite(MOTOR_PWN, current_motor);
    Serial.print("VAL: ");
    Serial.println(current_motor);
    delay(1000);
    

}

int readInfrared() {

    //while(!(IrReceiver.decode(&results))); //wait until no button is pressed

    //while(IrReceiver.decodedIRData.protocol == UNKNOWN) { delay (50);};

    if (IrReceiver.decode()) {

        //if(IrReceiver.decodedIRData.protocol == UNKNOWN) {
        //    Serial.print("UNK");
        //    return -1;
        //}

        /*
         * Print a short summary of received data
         */
        IrReceiver.printIRResultShort(&Serial);
        //IrReceiver.printIRResultRawFormatted(&Serial, true);
        //IrReceiver.printIRSendUsage(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();

        //Serial.println(IrReceiver.decodedIRData.command);
        //Serial.println(IrReceiver.decodedIRData.extra);
        //Serial.println(IrReceiver.decodedIRData.flags);

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x10) {
            // do something
        } else if (IrReceiver.decodedIRData.command == 0x11) {
            // do something else
        }

        return IrReceiver.decodedIRData.command;    
    }
    
    return -1;
}
