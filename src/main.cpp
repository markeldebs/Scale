# include <Arduino.h>
# include <Ticker.h>

////////////////////////////////////////////

# define touchpin 2

int tvalue = 0;
int buttonVal = 0;
int buttonLast = 0;
int n = 0;




int checkButton (){
    //int event = 0;
    buttonVal = analogRead(touchpin);
    if (buttonVal < 3500){
        //Serial.println("Released");
        tvalue = 0;
        n = 0;

    }
    else if (buttonVal >= 3500 && n == 0 ){
          tvalue++;
          if (tvalue >= 45 && tvalue <= 60){
          Serial.println("Tap");
          tvalue = 0;
          n =1;
        }
    }
    //delay (100);
     return tvalue;
}

////////////////////////////////////////////

void setup() {

    Serial.begin(9600);

}

////////////////////////////////////////////

void loop() {

    checkButton();


}

