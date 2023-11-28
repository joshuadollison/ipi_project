const int PHOTO_000 = 6;
const int PHOTO_045 = A4;
const int PHOTO_090 = A3;
const int PHOTO_135 = A2;
const int PHOTO_180 = 9;
const int PHOTO_225 = 5;
const int PHOTO_270 = 3;
const int PHOTO_315 = A5;

const int PHOTO_DEGS[] = { 0, 45, 90, 135, 180, 225, 270, 315 };

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

void setup() {
    Serial.begin(9600);
    
    for(int i; i < PHOTOS_LEN; i++)
        pinMode(i, INPUT);
}

int getBrightest() {

    int analogValue, largest = 0, brightest = -1;
  
    for(int curr = 0; curr < PHOTOS_LEN; curr++) {
        analogValue = analogRead(PHOTOS[curr]);
    
        if(analogValue > largest) {
            largest = analogValue;
            brightest = curr;
        }
    }

    return brightest;
}

void loop()
{
    //reads the input on analog pin A0 (value between 0 and 1023)
    //int analogValue = analogRead(A0);

    int brightest = getBrightest();
    //Serial.print("Brightest: ");
    //Serial.println(brightest);
    int analogValue = analogRead(PHOTOS[brightest]);

  
    // scales it to brightness (value between 0 and 255)
    int mapValue = map(analogValue, 0, 310, 0, 255);

    //int x = PHOTO_DEGS[brightest];
    int x = PHOTO_DEGS[brightest];

    Serial.println("IN LOOP");
    Serial.print("Brightest deg: ");
    //Serial.print(brightest);
    Serial.print(PHOTO_DEGS[brightest]);  
    /*
    try {
        Serial.print(PHOTO_DEGS[brightest]);  
    }
    catch(String err)
    {
        Serial.println(err);
    }
    */    

    Serial.print("- analogValue: ");
    Serial.print(analogValue);

    Serial.print("- mapValue: ");
    Serial.println(mapValue);

    delay(500);

}