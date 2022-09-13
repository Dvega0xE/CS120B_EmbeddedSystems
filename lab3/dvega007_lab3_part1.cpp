/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 3  Exercise 1

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/c9Ic3BuDfq8

 */

unsigned long lastRan;
const unsigned long period = 100;
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int dp = 9;
int sw = 10;
int light;

//analogRead(A3) for photoresistor

void setup(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  lastRan = 0;
}
// This function takes in the state as an argument & returns the current state
enum States{INIT, S0, S1, S2, S3, S4, S5, S6, S7, S8, S9} SM1_state = INIT;
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
        Serial.println(light);
        if(light == 0){      
            state = S0;
        }else if(light == 1){
            state = S1;
        }else if(light == 2){
            state = S2;
        }else if(light == 3){
            state = S3;
        }else if(light == 4){
            state = S4;
        }else if(light == 5){
            state = S5;
        }else if(light == 6){
            state = S6;
        }else if(light == 7){
            state = S7;
        }else if(light == 8){
            state = S8;
        }else if(light == 9){
            state = S9;
        }
        break;
      default:
            state = INIT;
        break;
    }
    switch(state){ // State Action
      case INIT:
        break;
      case S0:
         digitalWrite(a,HIGH);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,HIGH);
         digitalWrite(e,HIGH);
         digitalWrite(f,HIGH);
         digitalWrite(g, LOW);
         digitalWrite(dp,LOW);
        break;
      case S1:
         digitalWrite(a,LOW);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,LOW);
         digitalWrite(e,LOW);
         digitalWrite(f,LOW);
         digitalWrite(g,LOW);
         digitalWrite(dp,LOW);
        break;
      case S2:
         digitalWrite(a,HIGH);
         digitalWrite(b,HIGH);
         digitalWrite(c,LOW);
         digitalWrite(d,HIGH);
         digitalWrite(e,HIGH);
         digitalWrite(f,LOW);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
      case S3:
         digitalWrite(a,HIGH);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,HIGH);
         digitalWrite(e,LOW);
         digitalWrite(f,LOW);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
      case S4:
         digitalWrite(a,LOW);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,LOW);
         digitalWrite(e,LOW);
         digitalWrite(f,HIGH);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
      case S5:
         digitalWrite(a,HIGH);
         digitalWrite(b,LOW);
         digitalWrite(c,HIGH);
         digitalWrite(d,HIGH);
         digitalWrite(e,LOW);
         digitalWrite(f,HIGH);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
      case S6:
         digitalWrite(a,HIGH);
         digitalWrite(b,LOW);
         digitalWrite(c,HIGH);
         digitalWrite(d,HIGH);
         digitalWrite(e,HIGH);
         digitalWrite(f,HIGH);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
      case S7:
         digitalWrite(a,HIGH);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,LOW);
         digitalWrite(e,LOW);
         digitalWrite(f,LOW);
         digitalWrite(g,LOW);
         digitalWrite(dp,LOW);
        break;
      case S8:
         digitalWrite(a,HIGH);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,HIGH);
         digitalWrite(e,HIGH);
         digitalWrite(f,HIGH);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
      case S9:
         digitalWrite(a,HIGH);
         digitalWrite(b,HIGH);
         digitalWrite(c,HIGH);
         digitalWrite(d,HIGH);
         digitalWrite(e,LOW);
         digitalWrite(f,HIGH);
         digitalWrite(g,HIGH);
         digitalWrite(dp,LOW);
        break;
    }
    return state;
}
//the state machine should turn all the leds on the display on then off
void loop(){
    light = analogRead(A3);
    light = map(light, 50, 800, 0, 9);
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
  if ((millis() - lastRan) > period) {
    SM1_state = (States)SM1_Tick(SM1_state);
    lastRan = millis();
  }
}