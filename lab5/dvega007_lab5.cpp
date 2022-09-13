/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 5

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/lULJHm7XjC8 

 */

// include the library code:
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <LiquidCrystal.h>
#include <DHT.h>

//Temperature Sensor
#define DHTPIN A0     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int temp;
int set_temp = 75;
//float temp = dht.readTemperature(true);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//LED for heater
const int led = 13;

//IR Receiver
int RECV_PIN = 6; //define input pin for the reciever on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;
int remotePress = 0;
//Power 0xFFA25D
//Down 0xFFE01F
//Up 0xFF906F

//DC Motor
const int in_1 = 8;
const int in_2 = 9;

bool on = false;

//Task Struct
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 4;
task tasks[tasksNum];

//IR Remote
enum SM1_States { SM1_INIT, SM1_S0};
int SM1_Tick(int state1){
    switch(state1){ // State transitions
      case SM1_INIT:
         //State Transition
         state1 = SM1_S0;
        break;
      case SM1_S0:
        state1 = SM1_S0;
        break;
    }
    switch(state1){ // State Action
      case SM1_INIT:
        break;
      case SM1_S0:
        if (irrecv.decode(&results)) {
          irrecv.resume(); // Receive the next value
        }
        break;
    }

    return state1;
}

//LCD Screen
enum SM2_States { SM2_INIT, SM2_S0, SM2_S1, SM2_S2};
int SM2_Tick(int state2){
    switch(state2){ 
      case SM2_INIT:
        lcd.noDisplay();
        state2 = SM2_S0;
        break;
      case SM2_S0:
        if(results.value == 0xFFA25D && !on){
          state2 = SM2_S1;
        }else if(results.value == 0xFFA25D && on){
          state2 = SM2_S2;
        }
        break;
      case SM2_S1:
        state2 = SM2_S0;
        break;
      default:
        state2 = SM2_INIT;
        break;
    }
    switch(state2){ // State Action
      case SM2_INIT:
        break;
      case SM2_S0:
        break;
      case SM2_S1:
        lcd.display();
        results.value = 0;
        on = true;
        break;
      case SM2_S2:
        lcd.clear();
        digitalWrite(led, LOW);
        digitalWrite(in_1, LOW);
        digitalWrite(in_2, LOW);
        results.value = 0;
        on = false;
        break;
    }

    return state2;
}

//Temperature
enum SM3_States { SM3_INIT, SM3_S0, SM3_S1, SM3_S2};
int SM3_Tick(int state3){
    switch(state3){ // State transitions
      case SM3_INIT:
        state3 = SM3_S0;
        break;
      case SM3_S0:
        if(results.value == 0xFFE01F){
          state3 = SM3_S1;
        }else if(results.value == 0xFF906F){
          state3 = SM3_S2;
        }
        break;
      case SM3_S1:
        state3 = SM3_S0;
        break;
      case SM3_S2:
        state3 = SM3_S0;
        break;
      default:
        state3 = SM3_INIT;
        break;
    }
    switch(state3){ // State Action
      case SM3_INIT:
        break;
      case SM3_S0:
        break;
      case SM3_S1:
        set_temp = set_temp - 1;
        results.value = 0;
        break;
      case SM3_S2:
        set_temp = set_temp + 1;
        results.value = 0;
        break;
    }

    return state3;
}

//Motor and LED
enum SM4_States { SM4_INIT, SM4_S0, SM4_S1, SM4_S2, SM4_S3};
int SM4_Tick(int state4){
    switch(state4){ // State transitions
      case SM4_INIT:
        state4 = SM4_S0;
        break;
      case SM4_S0:
        if(set_temp == temp && on){
          state4 = SM4_S1;
        }else if(set_temp < temp && on){
          state4 = SM4_S2;
        }else if(set_temp > temp && on){
          state4 = SM4_S3;
        }
        break;
      case SM4_S1:
        state4 = SM4_S0;
        break;
      case SM4_S2:
        state4 = SM4_S0;
        break;
      case SM4_S3:
        state4 = SM4_S0;
        break;
      default:
        state4 = SM4_INIT;
        break;
    }
    switch(state4){ // State Action
      case SM4_INIT:
        break;
      case SM4_S0:
        break;
      case SM4_S1:
        digitalWrite(led, LOW);
        digitalWrite(in_1, LOW);
        digitalWrite(in_2, LOW);
        break;
      case SM4_S2:
        digitalWrite(led, LOW);
        digitalWrite(in_1, HIGH);
        digitalWrite(in_2, LOW);
        delay(1000);
        digitalWrite(in_1, LOW);
        digitalWrite(in_2, LOW);
        delay(100);
        digitalWrite(in_1, HIGH);
        digitalWrite(in_2, LOW);
        delay(1000);
        break;
      case SM4_S3:
        digitalWrite(led, HIGH);
        digitalWrite(in_1, LOW);
        digitalWrite(in_2, LOW);
        break;
    }

    return state4;
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  dht.begin();
  
  pinMode(led, OUTPUT);

  irrecv.enableIRIn();

  pinMode(in_1,OUTPUT);
  pinMode(in_2,OUTPUT);
  
  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;
  i++;
  tasks[i].state = SM4_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM4_Tick;

  delay_gcd = 50; // GCD
}

void loop() {
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.print(temp);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("  Set Temp: ");
  lcd.print(set_temp);

  float f = dht.readTemperature(true);
  temp = f;
  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
   //delay(delay_gcd);
}