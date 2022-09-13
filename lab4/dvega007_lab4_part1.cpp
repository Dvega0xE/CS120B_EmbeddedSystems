/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 4  Exercise 1

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/2MKYRT8zca0

 */

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
int RECV_PIN = 9; //define input pin for the reciever on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;

int i = 0;
int j = 0;
int IN1 = 10;
int IN2 = 11;
int IN3 = 12;
int IN4 = 13;
int sig[4] = {IN1,IN2,IN3,IN4};
int steps[8][4] { //codes for the motor to turn properly
  {0,0,0,1},
  {0,0,1,1},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0},
  {1,1,0,0},
  {1,0,0,0},
  {1,0,0,1},
};

int a = 2; //B0
int b = 3; //B1
int c = 4; //B2
int d = 5; //B3
int e = 6; //B4
int f = 7; //B5
int g = 8; //B6
int LEDS[7] = {g,f,e,d,c,b,a};

int nums[14][7]{//no decimal point
  {0,1,1,1,1,1,1}, //0
  {0,0,0,0,1,1,0}, //1
  {1,0,1,1,0,1,1}, //2
  {1,0,0,1,1,1,1}, //3
  {1,1,0,0,1,1,0}, //4
  {1,1,0,1,1,0,1}, //5
  {1,1,1,1,1,0,1}, //6
  {0,0,0,0,1,1,1}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,0,1,1,1,1}, //9
  {0,1,1,1,0,0,0}, //left
  {0,1,1,0,0,0,1}, //right
  {1,0,1,1,1,1,0}, //down
  {0,1,1,1,1,1,0}, //up
};

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM1_S1, SM1_S2, SM1_S3, SM1_S4, SM1_S5, SM1_S6, 
                  SM1_S7, SM1_S8, SM1_S9, SM1_S10, SM1_S11, SM1_S12, SM1_S13, SM1_OFF};
int SM1_Tick(int state1){
    switch(state1){ // State transitions
      case SM1_INIT:
        Serial.println(results.value, HEX);
        if(results.value == 0xFF6897){ 
          state1 = SM1_S0;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF30CF){
          state1 = SM1_S1;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF18E7){
          state1 = SM1_S2;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF7A85){
          state1 = SM1_S3;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF10EF){
          state1 = SM1_S4;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF38C7){
          state1 = SM1_S5;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF5AA5){
          state1 = SM1_S6;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF42BD){
          state1 = SM1_S7;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF4AB5){
          state1 = SM1_S8;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF52AD){
          state1 = SM1_S9;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF22DD){
          state1 = SM1_S10;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFFC23D){
          state1 = SM1_S11;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFFE01F){
          state1 = SM1_S12;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFF906F){
          state1 = SM1_S13;
          irrecv.resume(); // Receive the next value
        }else if(results.value == 0xFFA25D){
          state1 = SM1_OFF;
          irrecv.resume(); // Receive the next value
        }
        break;
      default:
        state1 = SM1_INIT;
        break;
    }
    switch(state1){ // State Action
      case SM1_INIT:
        break;
      case SM1_S0:
        for(int x = 0; x < 7; x++){
          if(nums[0][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S1:
        for(int x = 0; x < 7; x++){
          if(nums[1][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S2:
        for(int x = 0; x < 7; x++){
          if(nums[2][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S3:
        for(int x = 0; x < 7; x++){
          if(nums[3][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S4:
        for(int x = 0; x < 7; x++){
          if(nums[4][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S5:
        for(int x = 0; x < 7; x++){
          if(nums[5][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S6:
        for(int x = 0; x < 7; x++){
          if(nums[6][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S7:
        for(int x = 0; x < 7; x++){
          if(nums[7][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S8:
        for(int x = 0; x < 7; x++){
          if(nums[8][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S9:
        for(int x = 0; x < 7; x++){
          if(nums[9][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S10:
        for(int x = 0; x < 7; x++){
          if(nums[10][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S11:
        for(int x = 0; x < 7; x++){
          if(nums[11][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S12:
        for(int x = 0; x < 7; x++){
          if(nums[12][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_S13:
        for(int x = 0; x < 7; x++){
          if(nums[13][x] == 1){
            digitalWrite(LEDS[x],HIGH);
          }else{
            digitalWrite(LEDS[x], LOW);
          }
        }
        break;
      case SM1_OFF:
        for(int x = 0; x < 7; x++){
          if(nums[8][x] == 1){
            digitalWrite(LEDS[x],LOW);
          }else{
            digitalWrite(LEDS[x], HIGH);
          }
        }
        break;
    }

    return state1;
}
/*
enum SM2_States { SM2_INIT, SM2_S0};
int SM2_Tick(int state2){
    switch(state2){ // State transitions
      case SM2_INIT:
        state2 = SM2_S0;
        break;
      case SM2_S0:
        if(j == 4){
          j = 0;
          i++;
        }
        if(i == 8){
          i = 0;
        }
        state2 = SM2_S0;
        break;
    }
    switch(state2){ // State Action
      case SM2_INIT:
        break;
      case SM2_S0:
        for(j; j < 4; j++){
            if(steps[i][j] == 1){
              digitalWrite(sig[j],HIGH);
            }
            else{
              digitalWrite(sig[j],LOW);
            }
        }
        break;
    }

    return state2;
}
*/
enum SM3_States { SM3_INIT, SM3_S0};
int SM3_Tick(int state3){
    switch(state3){ // State transitions
      case SM3_INIT:
         //State Transition
         state3 = SM3_S0;
        break;
      case SM3_S0:
        state3 = SM3_S0;
        break;
    }
    switch(state3){ // State Action
      case SM3_INIT:
        break;
      case SM3_S0:
        if (irrecv.decode(&results)) {
          //Serial.println(results.value, HEX);
          irrecv.resume(); // Receive the next value
        }
        break;
    }

    return state3;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  Serial.begin(9600);
  
  irrecv.enableIRIn();
  
  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
/*  tasks[i].state = SM2_INIT;
  tasks[i].period = 1;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;*/
  tasks[i].state = SM3_INIT;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;

  delay_gcd = 50; // GCD
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
     }
   }
   delay(delay_gcd);
}