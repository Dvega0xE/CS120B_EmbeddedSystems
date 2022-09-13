/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 2  Exercise 2

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/-Y4y8RGigxw

 */

int btn1 = 8;
int btn2 = 9;
int btn3 = 10;
int btn4 = 11;
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;

//assigning names to the pins that are in use
int leds[4] = {led1, led2, led3, led4};

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

// this is how we initialize our pins in arduino, the LEDS are outputs and the buttons are intputs
  Serial.begin(9600); 
}
enum States{INIT, S0, S1} SM1_state = INIT;

int blink(int x){
  //Serial.println(x);
  if(x > 240){
    delay(1000);
  }
  else if(x >= 200 && x <= 240){
    delay(500);
  }
  else if(x >= 150 && x <= 199){
    delay(250);
  }
  else if(x <= 149){
    delay(50);
  }
}

int SM1_Tick(int state){
    switch(state){ // State transitions
      case INIT:
            state = S0;
        break;
      case S0:
        if(analogRead(A0) >= 240 || analogRead(A0) <= 100){
            state = S0;
        }          
        else{
            state = S1;
        }
        break;
      case S1:
        if(analogRead(A0) >= 240 || analogRead(A0) <= 100){
            state = S0;
        }
        else{
            state = S1;
        }
        break;
    }
    switch(state){ // State Action
      case INIT:
        break;
      case S0:
        for(int i = 0; i < 4; i++){
          digitalWrite(leds[i],HIGH);
        }
        break;
      case S1:
        for(int i = 0; i < 4; i++){
          digitalWrite(leds[i],LOW);
        }
        break;
    }
    //Serial.println(analogRead(A0));
    blink(analogRead(A0));
    return state;
}
void loop() {
  //this state machine reads the photoresistor every second and turns on the leds if it is "dark"
  SM1_state = (States)SM1_Tick(SM1_state);
}