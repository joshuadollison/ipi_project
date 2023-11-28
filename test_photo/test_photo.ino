#define IN A0

void setup() {
    Serial.begin(9600); // Initialize the serial port
}

void loop() {

    int val = analogRead(IN);
    Serial.print("VAL: ");
    Serial.println(val);
    delay(1000);

}