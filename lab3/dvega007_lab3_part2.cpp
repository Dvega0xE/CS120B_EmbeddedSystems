/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 3  Exercise 2

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/0fcspt45J3U

 */

unsigned long lastRan, lastRan2;
const unsigned long period = 1000;
int a = 2; //B0
int b = 3; //B1
int c = 4; //B2
int d = 5; //B3
int e = 6; //B4
int f = 7; //B5
int g = 8; //B6
int dp = 9; //B7
int sw = 10; //A
//int LEDS[8] = {a,b,c,d,e,f,g,dp};
int LEDS[8] = {dp,g,f,e,d,c,b,a};
int light;
int counter;
static int sw_state, lastSW_state; //A0 or A1 = 0 or 1

int nums[10][8]{//no decimal point
  {0,0,1,1,1,1,1,1}, //0
  {0,0,0,0,0,1,1,0}, //1
  {0,1,0,1,1,0,1,1}, //2
  {0,1,0,0,1,1,1,1}, //3
  {0,1,1,0,0,1,1,0}, //4
  {0,1,1,0,1,1,0,1}, //5
  {0,1,1,1,1,1,0,1}, //6
  {0,0,0,0,0,1,1,1}, //7
  {0,1,1,1,1,1,1,1}, //8
  {0,1,1,0,1,1,1,1}, //9
};

int dnums[10][8]{//with decimal point
  {1,0,1,1,1,1,1,1}, //0
  {1,0,0,0,0,1,1,0}, //1
  {1,1,0,1,1,0,1,1}, //2
  {1,1,0,0,1,1,1,1}, //3
  {1,1,1,0,0,1,1,0}, //4
  {1,1,1,0,1,1,0,1}, //5
  {1,1,1,1,1,1,0,1}, //6
  {1,0,0,0,0,1,1,1}, //7
  {1,1,1,1,1,1,1,1}, //8
  {1,1,1,0,1,1,1,1}, //9
};

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
enum States{INIT, S0, S1, S2} SM1_state = INIT;
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
        state = S0;
        break;
      case S0:
        //Serial.println(counter);
        state = S0;
        if(sw_state == HIGH){
          state = S1;
        }else if(sw_state == LOW){
          state = S2;
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
        break;
      case S1:
        //Serial.println(counter); 
        if(counter >= 0 && counter <= 9){  
          for(int i = 0; i < 8; i++){
            if(nums[counter][i] == 1){
              digitalWrite(LEDS[i],HIGH);
            }else{
              digitalWrite(LEDS[i], LOW);
            }
          }
        }else if(counter > 9){
          for(int i = 0; i < 8; i++){
            if(dnums[counter][i] == 1){
              digitalWrite(dp, HIGH);
              digitalWrite(LEDS[i],HIGH);
            }else{
              digitalWrite(LEDS[i], LOW);
            }
          }
        }else if(counter < 0){
          counter = 9;
          for(int i = 0; i < 8; i++){
            if(dnums[counter][i] == 1){
              digitalWrite(dp, HIGH);
              digitalWrite(LEDS[i],HIGH);
            }else{
              digitalWrite(LEDS[i], LOW);
            }
          }
        }
        counter++;
        break;
      case S2:
        if(counter >= 0 && counter <= 9){  
          for(int i = 0; i < 8; i++){
            if(nums[counter][i] == 1){
              digitalWrite(LEDS[i],HIGH);
            }else{
              digitalWrite(LEDS[i], LOW);
            }
          }
        }else if(counter > 9){
          for(int i = 0; i < 8; i++){
            if(dnums[counter][i] == 1){
              digitalWrite(dp, HIGH);
              digitalWrite(LEDS[i],HIGH);
            }else{
              digitalWrite(LEDS[i], LOW);
            }
          }
        }else if(counter < 0){
          counter = 0x9;
          for(int i = 0; i < 8; i++){
            if(dnums[counter][i] == 1){
              digitalWrite(dp, HIGH);
              digitalWrite(LEDS[i],HIGH);
            }else{
              digitalWrite(LEDS[i], LOW);
            }
          }
        }
        counter--;
        break;
    }
    return state;
}
//the state machine should turn all the leds on the display on then off
void loop(){
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
  if ((millis() - lastRan) > period) {
    sw_state = digitalRead(sw);
    //lastSW_state = millis();
    Serial.println(lastSW_state);//Begins on 1 and pressing switches to 0.
    SM1_state = (States)SM1_Tick(SM1_state);
    lastRan = millis();
  }
}