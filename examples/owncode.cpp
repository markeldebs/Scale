# include <Arduino.h>
# include <Ticker.h>

////////////////////////////////////////////

# define touchpin 2

int tvalue = 0;


////////////////////////////////////////////

void setup() {

    Serial.begin(9600);

}

////////////////////////////////////////////

void loop() {

    tvalue = analogRead(touchpin);

    if (tvalue >= 3500 ){
            Serial.println(tvalue);
    }

    delay (200);

}

