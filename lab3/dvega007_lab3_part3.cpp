/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 3  Exercise 3

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/emH5OPqKPiQ

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

int LEDS[8] = {dp,g,f,e,d,c,b,a};
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

const int VRyPin = A0;//LEFT and RIGHT
const int VRxPin = A1;// UP and DOWN
int VRx = 0;
int VRy = 0;

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

// This function takes in the state as an argument & returns the current state
enum States_2{INIT2, T0, T1, T2} SM2_state = INIT2;
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT2:
        state = T0;
        break;
      case T0:
        //Serial.println(counter);
        state = T0;
        if(sw_state == HIGH){
          state = T1;
        }else if(sw_state == LOW){
          state = T2;
        }
        break;
      default:
        state = INIT2;
        break;
    }
    switch(state){ // State Action
      case INIT2:
        break;
      case T0:
        break;
      case T1:
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
      case T2:
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
    light = analogRead(A3);
    light = map(light, 50, 800, 0, 9);
    VRx = analogRead(VRxPin);
    //Serial.println(VRx);
    VRy = analogRead(VRyPin);
    //Serial.println(VRy);
      
    //Default arduino function
    //We have to cast the return value of the tick function to type States
    if ((millis() - lastRan) > period) {
      sw_state = digitalRead(sw);
      if(sw_state == HIGH && VRy > 550){
        SM1_state = (States)SM1_Tick(SM1_state);
      }else if(sw_state == HIGH && VRy < 450){
        SM2_state = (States_2)SM2_Tick(SM2_state);
      }else if(sw_state == LOW){
        for(int i = 0; i < 8; i++){
          if(nums[counter][i] == 1 || nums[counter][i] == 0){
            digitalWrite(LEDS[i],LOW);
          }
        }
      }
      lastRan = millis();
    }
}